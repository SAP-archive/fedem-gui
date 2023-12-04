// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppProcess/FapFEFatigueProcess.H"
#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"
#include "vpmPM/FpProcessOptions.H"
#include "vpmPM/FpFileSys.H"
#include "vpmDB/FmResultStatusData.H"
#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmPart.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


/*!
  FE Fatigue (ncl encapsulation) option
  - run "only" ncl with the current filenames
*/

FapFEFatigueProcess::FapFEFatigueProcess(FmPart* aPart)
  : FapRecoveryBase(aPart)
{
  // get the npath environment variable
  char* fd = getenv("npath");
  if (fd)
  {
    myNPath = std::string(fd);
    FFaFilePath::checkName(myNPath);
  }

  mySubTask = "summary_rcy";
  myGroupID = FapSolverID::FAP_FEFATIGUE;

  if (myNPath.empty())
    mySolverName = "ncl"; // $npath is not set, assuming ncl is in $PATH...
  else
  {
    // Find the file path of the ncl-executable
    std::string binDir = FFaFilePath::appendFileNameToPath(myNPath,"bin"); // R6.0
    if (!FpFileSys::isDirectory(binDir))
    {
      binDir = FFaFilePath::appendFileNameToPath(myNPath,"nsoft"); // R5.3
      if (!FpFileSys::isDirectory(binDir))
	binDir = ""; // the nSoft installation is probably incomplete...
    }
    // Prefix the ncl executable with correct path
    mySolverName = FFaFilePath::appendFileNameToPath(binDir,"ncl");
  }
}


int FapFEFatigueProcess::checkDependencies() const
{
#ifdef FAP_DEBUG
  std::cout <<"FapFEFatigueProcess::checkDependencies()"<< std::endl;
#endif

  // Check if we have a strain coat recovery process running
  if (FapSolutionProcessManager::instance()->isGroupRunning(FapSolverID::FAP_FPP,
							    this->getEvent()))
  {
#if FAP_DEBUG > 1
    std::cout <<" --> A strain coat recovery process is already running, please wait\n";
#endif
    return FAP_PENDING_DEPENDENCIES_BUT_WAIT;
  }

  // Check if we have the needed fpp-file

  FmResultStatusData* lnkRSD;
  if (this->getEvent())
    lnkRSD = this->getEvent()->getResultStatusData();
  else
    lnkRSD = myWorkMech->getResultStatusData();
  lnkRSD = lnkRSD->addSubTask(mySubTask)->addSubTask(myWorkPart->getTaskName());

  // Find the fpp-file from the part RSD with the highest number
  std::set<std::string> files;
  lnkRSD->getAllFileNames(files,"fpp");
#if FAP_DEBUG > 2
  std::cout <<"Files:\n";
  std::copy(files.begin(),files.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
#endif

  if (!files.empty())
    if (FpFileSys::isFile(*files.rbegin()))
      myFppFile = *files.rbegin();

  if (myFppFile.empty())
  {
    ListUI <<"===> "<< myWorkPart->getIdString(true)
	   <<" has no associated damage file (fpp-file).\n";
    FFaMsg::list("     You need to do a Strain Coat Recovery on the part first.\n",true);
    return FAP_NOT_EXECUTABLE;
  }
#if FAP_DEBUG > 2
  else
    std::cout <<"Highest file: "<< myFppFile << std::endl;
#endif

  // Check for existance of the fedem ncl script
  std::string nCodeScript = myNPath + FFaFilePath::getPathSeparator()
    +                 "nsdata" + FFaFilePath::getPathSeparator()
    +                 "fedem_fatfe.ncx";
  if (!FpFileSys::isFile(nCodeScript))
  {
    FFaMsg::list("===> Can not run nCode FE-Fatigue analysis.\n",true);
    if (myNPath.empty())
      ListUI <<"  -> You need to set the \"npath\" environment variable.\n";
    else if (!FpFileSys::isDirectory(myNPath))
      ListUI <<"  -> The \"npath\" environment variable is set,"
	     <<" but points to a non-existing directory.\n"
	     <<"     npath = \""<< myNPath <<"\"\n";
    else
      ListUI <<"  -> Can not find file "<< nCodeScript
	     <<"\n     npath = \""<< myNPath
	     <<"\"\n     You may need to upgrade your nSoft installation.\n";
    ListUI <<"     The \"npath\" environment variable should point to the\n"
	   <<"     installation directory of the nSoft/FE-Fatigue software.\n"
	   <<"     Please ask your system administrator for assistance.\n";
    return FAP_NOT_EXECUTABLE;
  }

  return FAP_READY_TO_RUN;
}


int FapFEFatigueProcess::execute()
{
#ifdef FAP_DEBUG
  std::cout <<"\nFapFEFatigueProcess::execute()"<< std::endl;
#endif

  // Check the dependencies for this part
  int depVal = this->checkDependencies();
  if (depVal != FAP_READY_TO_RUN)
    return depVal;

  // Get path for the working directory of this recovery process
  std::string rdbPath = this->getRunDir(true,true);
  if (rdbPath.empty())
    return FAP_NOT_EXECUTABLE;
  else
    rdbPath += FFaFilePath::getPathSeparator();

  // Set up the actual process options
  FpProcessOptions options;
#ifdef win32
  options.name = mySolverName + " @fedem_fatfe \"" + myFppFile + "\"";
#else
  options.name = mySolverName;
  options.args.push_back("@fedem_fatfe");
#endif
  options.args.push_back("\"" + myFppFile + "\"");
  options.workingDir = rdbPath; // non-absolute paths are relative to this dir
  options.deathHandler = FFaDynCB1M(FapFEFatigueProcess, this, onActualProcessDeath, int);

  ListUI <<"\n===> Running nCode FE-Fatigue on: "
	 << myWorkPart->getIdString(true) <<" ...\n";

  if (this->run(options,"fedem_fatfe") < 0)
    return FAP_NOT_EXECUTABLE;

  FFaMsg::pushStatus("Running nCode FE-Fatigue");
  FFaMsg::setSubTask(myWorkPart->baseFTLFile.getValue());

  return FAP_STARTED;
}


void FapFEFatigueProcess::onActualProcessDeath(int exitValue)
{
  if (exitValue != 0)
    FFaMsg::list("===> nCode FE-Fatigue failed.\n\n",true);
  else
    FFaMsg::list("===> nCode FE-Fatigue done.\n\n");

  FFaMsg::popStatus();
  FFaMsg::setSubTask("");

  FapSolutionProcessManager::instance()->onSolverProcessDeath(this->getProcessSignature(),exitValue);
}
