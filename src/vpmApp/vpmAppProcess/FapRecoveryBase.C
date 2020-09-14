// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmPM/FpProcessOptions.H"
#include "vpmDB/FmFileSys.H"
#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmPart.H"
#include "vpmDB/FmDB.H"

#include "vpmApp/vpmAppProcess/FapRecoveryBase.H"
#include "vpmApp/vpmAppProcess/FapLinkReducer.H"
#include "vpmApp/vpmAppProcess/FapDynamicSolver.H"
#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"
#include "vpmApp/FapLicenseManager.H"

#include "FFaLib/FFaCmdLineArg/FFaOptionFileCreator.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaDefinitions/FFaAppInfo.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


FapRecoveryBase::FapRecoveryBase(FmPart* part, FmSimulationEvent* event)
{
  myWorkPart = part;
  myWorkEvent = event ? event : FapSimEventHandler::getActiveEvent();
  amIPreparingForBatch = false;
}


FmResultStatusData* FapRecoveryBase::getTopLevelRSD() const
{
  if (myWorkEvent)
    return myWorkEvent->getResultStatusData();
  else
    return myWorkMech->getResultStatusData();
}


int FapRecoveryBase::checkDependencies() const
{
#ifdef FAP_DEBUG
  std::cout <<"FapRecoveryBase::checkDependencies()"<< std::endl;
#endif

  // Check if we have a solver currently running
  if (FapSolutionProcessManager::instance()->isGroupRunning(FapSolverID::FAP_DYN_SOLVER,myWorkEvent) ||
      FapSolutionProcessManager::instance()->isGroupRunning(FapSolverID::FAP_REDUCER))
  {
#if FAP_DEBUG > 1
    std::cout <<" --> A reducer or solver process is already running, please wait"<< std::endl;
#endif
    return FAP_PENDING_DEPENDENCIES_BUT_WAIT;
  }

  // Check if we have any solver results
  FmResultStatusData* allRSD = this->getTopLevelRSD();
  if (!amIPreparingForBatch && allRSD->isEmpty())
  {
#ifdef FAP_DEBUG
    std::cout <<" --> Could not find any solver results"<< std::endl;
#endif
    // Create a dynamics solver process and push it on the stack
    FapSolutionProcessManager::instance()->pushSolverProcess(new FapDynamicSolver(myWorkEvent));
    return FAP_PENDING_DEPENDENCIES;
  }

  // Check availability of fsi file
  std::string fsifile = FFaFilePath::appendFileNameToPath(allRSD->getCurrentTaskDirName(true),"fedem_solver.fsi");
  if (!FmFileSys::isReadable(fsifile))
  {
#ifdef FAP_DEBUG
    std::cout <<" --> Could not find solver input file "<< fsifile << std::endl;
#endif
    // Create a solver process and push it on the stack
    FapSolutionProcessManager::instance()->pushSolverProcess(new FapDynamicSolver(myWorkEvent,amIPreparingForBatch));
    return FAP_PENDING_DEPENDENCIES;
  }

  if (amIPreparingForBatch) return FAP_READY_TO_RUN;

  // Check if the part has the required reduced matrix files
  FapLinkReducer* red = new FapLinkReducer(myWorkPart,true);
  switch (red->checkDependencies())
  {
    case FAP_RESULTS_OK:
      delete red; // everything is OK - just skip this
      break;

    case FAP_NOT_EXECUTABLE:
      delete red;
      return FAP_NOT_EXECUTABLE;

    case FAP_READY_TO_RUN:
      FapSolutionProcessManager::instance()->pushSolverProcess(red);
      return FAP_PENDING_DEPENDENCIES;
  }

  return FAP_READY_TO_RUN;
}


int FapRecoveryBase::execute()
{
#ifdef FAP_DEBUG
  std::cout <<"\nFapRecoveryBase::execute()"<< std::endl;
#endif

  // Activate model data for current simulation event while creating input files
  FmSimulationEvent* activeEvent = FapSimEventHandler::getActiveEvent();
  FapSimEventHandler::activate(myWorkEvent,false,false);

  FFaMsg::pushStatus("Creating Recovery input");
  FFaMsg::setSubTask(myWorkPart->getTaskName());

  std::string rdbPath;
  int depVal = this->createInput(rdbPath);
  FFaMsg::popStatus();
  FFaMsg::setSubTask("");

  // Restore the active event
  FapSimEventHandler::activate(activeEvent,false,false);

  if (depVal != FAP_READY_TO_RUN)
    return depVal;
  else if (amIPreparingForBatch)
  {
    ListUI <<"===> Input files for batch execution of "
           << mySolverName <<" created in:\n     "<< rdbPath <<"\n";
    FapSolutionProcessManager::instance()->afterBatchPreparation(myGroupID);
    return depVal;
  }

  return this->startProcess(rdbPath);
}


int FapRecoveryBase::startRecovery(const char* task,
				   const std::string& rdbPath,
				   const std::string& addOptions)
{
#ifdef FAP_DEBUG
  std::cout <<"FapRecoveryBase::startRecovery()"<< std::endl;
#endif

  // Create argument string:
  FFaOptionFileCreator processOpts;
  if (FapSolverBase::doRemoteSolve())
    processOpts.add("-cwd", this->findRemotePath(rdbPath));

  processOpts.add("-fco", mySolverName + ".fco");
  processOpts.add("-fop", mySolverName + ".fop");
  if (!addOptions.empty())
    processOpts.add("-fao", mySolverName + ".fao");

  // Enable console output of error messages
  processOpts.add("-consolemsg", true);

  // Retain terminal output only when running batch on one processor
  if (!FFaAppInfo::isConsole()) // Retain terminal output when running batch
    processOpts.add("-terminal",7); // Write terminal output to file in $PWD
  else if (FmDB::getActiveAnalysis()->maxConcurrentProcesses.getValue() > 1)
    if (addOptions.find("-terminal") == std::string::npos)
      processOpts.add("-terminal",-1); // Redirect terminal output to /dev/null

  // Set up the actual process options
  FpProcessOptions options;
  options.name = mySolverName;
  options.args = processOpts.getOptVector();
  if (FapSolverBase::doRemoteSolve())
    options.prefix = FmDB::getActiveAnalysis()->processPrefix.getValue();
  else
    options.workingDir = rdbPath;
  options.deathHandler = FFaDynCB1M(FapRecoveryBase, this, onActualProcessDeath, int);

  if (task)
    ListUI <<"\n===> Recovering "<< task <<" on ";
  else
    ListUI <<"\n===> Solving ";
  ListUI << myWorkPart->getIdString(true) <<" ...\n  -> Results in "
         << FFaFilePath::getRelativeFilename(myWorkMech->getAbsModelFilePath(),rdbPath) <<"\n";

  if (this->run(options) < 0)
    return FAP_NOT_EXECUTABLE;

  if (task)
    FFaMsg::pushStatus(std::string("Recovering ") + task);
  else
    FFaMsg::pushStatus("Solving ");
  FFaMsg::setSubTask(myWorkPart->baseFTLFile.getValue());

  return FAP_STARTED;
}


/*!
  Get the working directory path of this recovery process.
  Optionally create the directory if not existing.
*/

std::string FapRecoveryBase::getRunDir(bool fullPath, bool verifyPath) const
{
  FmResultStatusData* allRSD = this->getTopLevelRSD();
  FmResultStatusData* recRSD = allRSD->addSubTask(mySubTask);
  FmResultStatusData* lnkRSD = recRSD ? recRSD->addSubTask(myWorkPart->getTaskName()) : NULL;
  std::string path = allRSD->getCurrentTaskDirName(fullPath);
  if (fullPath && verifyPath)
    if (!FmFileSys::verifyDirectory(allRSD->getPath()) || !FmFileSys::verifyDirectory(path))
    {
      ListUI <<"===> Could not access directory "<< path <<"\n";
      return "";
    }

  FFaFilePath::appendToPath(path, recRSD ? recRSD->getCurrentTaskDirName() : mySubTask);
  if (fullPath && verifyPath)
    if (!recRSD || !FmFileSys::verifyDirectory(path))
    {
      ListUI <<"===> Could not access directory "<< path <<"\n";
      return "";
    }

  FFaFilePath::appendToPath(path, lnkRSD ? lnkRSD->getCurrentTaskDirName() : myWorkPart->getTaskName());
  if (fullPath && verifyPath)
    if (!lnkRSD || !FmFileSys::verifyDirectory(path))
    {
      ListUI <<"===> Could not access directory "<< path <<"\n";
      return "";
    }

  return path;
}


/*!
  Get pathnames of all directories accessed by this recovery process.
*/

bool FapRecoveryBase::getInputAndRunDirs(std::string& dynPath,
					 std::string* lnkPath,
					 std::string* rcyPath) const
{
  // Get path to the dynamics solver files
  dynPath = this->getTopLevelRSD()->getCurrentTaskDirName(true,true);
  if (dynPath.empty()) return false;
  dynPath += FFaFilePath::getPathSeparator();

  if (lnkPath)
  {
    // Get path to the reduced matrix files
    *lnkPath = myWorkPart->myRSD.getValue().getCurrentTaskDirName(true,true);
    if (lnkPath->empty()) return false;
    *lnkPath += FFaFilePath::getPathSeparator();
  }

  if (rcyPath)
  {
    // Get path for the working directory of this recovery process
    *rcyPath = this->getRunDir(true,true);
    if (rcyPath->empty()) return false;
    *rcyPath += FFaFilePath::getPathSeparator();
  }

  return true;
}


/*!
  Get a comma-separated list of frs-files in the current solver task directory.
*/

std::string FapRecoveryBase::getFRSfiles(const std::string& solveTask) const
{
  FmResultStatusData* recRSD = this->getTopLevelRSD()->getSubTask(solveTask);
  if (!recRSD) return "";

  std::string frsfiles;
  std::string rdbPath = this->getRunDir(true);

  std::set<std::string> fSet;
  recRSD->getAllFileNames(fSet,"frs");
  for (const std::string& fileName : fSet)
  {
    if (frsfiles.empty())
      frsfiles = "\"";
    else
      frsfiles += "\",\"";
    frsfiles += FFaFilePath::getRelativeFilename(rdbPath,fileName);
  }
  frsfiles += "\"";
  return frsfiles;
}


/*!
  Get full path to the FE data file that this recovery process will use.
*/

std::string FapRecoveryBase::getFEDataFile(const std::string& rdbPath) const
{
  const std::string& partFile = myWorkPart->reducedFTLFile.getValue();
  if (!partFile.empty() && myWorkPart->isFELoaded(true))
    if (FmFileSys::isReadable(rdbPath + partFile))
      return rdbPath + partFile; // Use input file from the reducer process

  // Use the FE data file from the FE part repository
  return myWorkPart->getBaseFTLFile();
}


std::string FapRecoveryBase::getProcessSignature() const
{
  if (myProcessSignature.empty())
  {
    myProcessSignature = mySolverName + "@" + this->getRunDir(true);
#if FAP_DEBUG > 3
    std::cout <<"Process sign: "<< myProcessSignature << std::endl;
#endif
  }
  return myProcessSignature;
}


void FapRecoveryBase::onActualProcessDeath(int exitValue)
{
  ListUI <<"===> "<< mySolverName;
  if (IWasKilled)
    ListUI <<" terminated by user";
  else if (exitValue)
    ListUI <<" failed";
  else
    ListUI <<" done";

  ListUI <<" for "<< myWorkPart->getIdString(true) <<"\n";

  if (exitValue && !IWasKilled)
  {
    std::string resFile = FFaFilePath::appendFileNameToPath(this->getRunDir(true),
                                                            mySolverName + ".res");
    if (FmFileSys::isReadable(resFile))
      ListUI <<"     See "<< resFile <<" for further details.\n";
  }

  FFaMsg::list("\n",exitValue);
  FFaMsg::popStatus();
  FFaMsg::setSubTask("");

  std::string sign = this->getProcessSignature();
  FapSolutionProcessManager::instance()->onSolverProcessDeath(sign,exitValue);
}
