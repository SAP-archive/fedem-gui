// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppProcess/FapSolverBase.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppDisplay/FapVTFFile.H"
#include "vpmApp/FapLicenseManager.H"
#include "vpmPM/FpProcessOptions.H"
#include "vpmDB/FmFileSys.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmDB.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


FapSolverBase::FapSolverBase()
{
  myWorkMech = FmDB::getMechanismObject();
  myGroupID  = -1;
}


int FapSolverBase::run(const FpProcessOptions& options, const char* name)
{
  int pid = this->start(name ? name : mySolverName.c_str(), myGroupID, options);
  if (pid == -1)
  {
    ListUI <<"  -> Error: Could not spawn process:\n     "<< mySolverName;
    for (const std::string& arg : options.args) ListUI <<" "<< arg;
    ListUI <<"\n";
  }
#if FAP_DEBUG > 1
  else
  {
    std::cout <<"Process started: "<< mySolverName <<" PID = "<< pid << std::endl;
#if FAP_DEBUG > 2
    std::cout <<"   with options:";
    for (const std::string& arg : options.args) std::cout <<" "<< arg;
    std::cout << std::endl;
#endif
  }
#endif
  return pid;
}


/*!
  Convenience function checking whether solver processes should be
  executed on a remote computer or not (pro edition only).
*/

bool FapSolverBase::doRemoteSolve()
{
  bool remoteFlag = FmDB::getActiveAnalysis()->useProcessPrefix.getValue();
  if (FapLicenseManager::isProEdition()) return remoteFlag;

  if (remoteFlag)
    ListUI <<" ==> Ignoring the remote solve settings from the model file.\n"
	   <<"     That feature is not available in this edition.\n";

  return false;
}


/*!
  Modify the \a localPath such that the beginning of the pathname matches
  that of the absolute model file path on the remote computer.
*/

std::string FapSolverBase::findRemotePath(const std::string& localPath) const
{
  std::string remoteModelFilePath = FmDB::getActiveAnalysis()->getProcessPath();
  if (remoteModelFilePath.empty()) return FFaFilePath::unixStyle(localPath);

#define isSlash(c) (c == '/' || c == '\\')

  // Find the length of the local- and remote model file paths
  // (excluding the trailing slash, if any)
  std::string localModelFilePath = myWorkMech->getAbsModelFilePath();
  int ir = remoteModelFilePath.size()-1;
  int il = localModelFilePath.size()-1;
  if (isSlash(remoteModelFilePath[ir])) ir--;
  if (isSlash(localModelFilePath[il])) il--;
  int lastSlashPos = ir+1;

  // Traverse both pathnames backwards, to find the last '/' in
  // remoteModelFilePath before the sub-directory names are equal
  for (; ir >= 0 && il >= 0; ir--, il--)
    if (isSlash(remoteModelFilePath[ir]) && isSlash(localModelFilePath[il]))
      lastSlashPos = ir;
    else if (remoteModelFilePath[ir] != localModelFilePath[il])
      break;

  // The portion of the model file path that is distinct for the remote computer
  std::string newPath = remoteModelFilePath.substr(0,lastSlashPos);

  // Check that the localPath and localModelFilePath match
  int lStart = lastSlashPos + il-ir;
  for (int i = 0; i < lStart; i++)
    if (localPath[i] != localModelFilePath[i])
      if (!(isSlash(localPath[i]) && isSlash(localModelFilePath[i])))
      {
	ListUI <<"  -> Error: Local pathname "<< localPath
	       <<"\n            does not match current model file path "
	       << localModelFilePath
	       <<"\n            Unable to create pathname for remote process\n";
	newPath = localPath;
	lStart = 0;
      }

  // Create the new remote pathname as the concatenation of
  // the proper parts of remoteModelFilePath and localPath
  if (lStart > 0) newPath += localPath.substr(lStart);

  // Ensure that UNIX-style path separators are used, to avoid that
  // they are treated as escape-characters by the login shell.
  return FFaFilePath::unixStyle(newPath);
}


/*!
  Modify given \a fileName to account for current simulation event.
  Ensure it has an absolute path, assuming it is relative to the model file.
*/

std::string FapSolverBase::eventName(const std::string& fileName) const
{
  FmSimulationEvent* event = this->getEvent();
  if (event) return event->eventName(fileName);

  std::string newName(fileName);
  return FFaFilePath::makeItAbsolute(newName,myWorkMech->getAbsModelFilePath());
}


/*!
  Create a VTF file named \a fname, of the given \a type, and write geometry
  control blocks to it. The actual link geometry may optionally be written too.
  If \a type is VTF_EXPRESS, visualization properties may be written as well.
*/

bool FapSolverBase::writeVTFHeader(std::vector<FmLink*>& links,
				   const std::string& fName, int type)
{
  return writeVTFHeader(links,std::vector<std::string>(1,fName),type,FapExpProp());
}


bool FapSolverBase::writeVTFHeader(std::vector<FmLink*>& links,
				   const std::string& fName, int type,
				   const FapExpProp& prop)
{
  return writeVTFHeader(links,std::vector<std::string>(1,fName),type,prop,false);
}


bool FapSolverBase::writeVTFHeader(std::vector<FmLink*>& links,
				   const std::vector<std::string>& fNames, int type,
				   const FapExpProp& prop, bool writeFEdata)
{
  if (links.empty() || fNames.empty())
    return false;

  if (!FapLicenseManager::hasVTFExportLicense(FapLicenseManager::LIST_MSG))
    return true;

  if (links.size() > 1 && !writeFEdata)
    if (FmDB::getActiveAnalysis()->maxConcurrentProcesses.getValue() > 1)
    {
      FFaMsg::dialog("Concurrent recovery of multiple FE parts with export to"
		     " VTF is not possible.\nPlease set the \"Max. concurrent"
		     " processes\" to 1, or toggle off the VTF export.",
		     FFaMsg::WARNING);
      FapSolutionProcessManager::instance()->killAll(false,false);
      return false;
    }

  // Check if the file(s) already exist on disk
  size_t nExist = 0;
  std::string existingFiles;
  for (const std::string& fName : fNames)
    if (FmFileSys::isFile(fName))
    {
      if (++nExist > 1) existingFiles += "\t";
      existingFiles += fName + "\n";
   }

  if (nExist > 0)
  {
    std::string msg(nExist == 1 ? "The VTF file " : "The VTF files ");
    msg += existingFiles + (nExist == 1 ? "already exists " : "already exist ");
    msg += "and will be overwritten if this solver is started.\n";
    msg += "Do you want proceed?";
    if (!FFaMsg::dialog(msg,FFaMsg::OK_CANCEL))
    {
      // Cancelled - empty the process stack and return
      FapSolutionProcessManager::instance()->killAll(false,false);
      return false;
    }
  }

  FFaMsg::pushStatus("Writing FE geometry to VTF");

  // Write VTF geometry definition, assuming one element block for each link
  FapVTFFile file(fNames.front(),(VTFFileType)type);
  bool retVal = file.writeGeometry(links,writeFEdata);

  // Write visualization properties
  if (!file.writeProperties(prop))
    retVal = false;

  // We're done so far, the main part of the VTF-file (results)
  // will be appended by the solver process(es)
  if (!file.close())
    retVal = false;

  // Make copies, if more than one file is requested (typically for mode shapes)
  const std::string& fName = fNames.front();
  for (size_t i = 1; i < fNames.size() && retVal; i++)
    if (!(retVal = FmFileSys::copyFile(fName,fNames[i])))
      ListUI <<" *** Failed to copy "<< fName <<" into "<< fNames[i] <<"\n";

  FFaMsg::popStatus();
  return retVal;
}
