// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmApp/vpmAppProcess/FapSolverBase.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"
#include "vpmApp/vpmAppCmds/FapFileCmds.H"
#include "vpmApp/vpmAppCmds/FapExportCmds.H"
#include "vpmPM/FpModelRDBHandler.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmSimulationEvent.H"
#include "vpmUI/Fui.H"
#include "FFaLib/FFaCmdLineArg/FFaCmdLineArg.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaAppInfo.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"

#include <algorithm>


typedef std::map<std::string,FapSolverBase*> ProcessMap;


struct ProcFinder
{
  FmSimulationEvent* myEvent;
  FmPart*            myPart;
  int                myGroup;
  ProcFinder(FapSolverBase* p) : myEvent(p->getEvent()), myPart(p->getWorkPart()), myGroup(p->getGroupID()) {}
  bool operator() (FapSolverBase* proc) const
  {
    return (proc->getEvent() == myEvent &&
            proc->getWorkPart() == myPart &&
            proc->getGroupID() == myGroup);
  }
};


void FapSolutionProcessManager::pushSolverProcess(FapSolverBase* aProc)
{
#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::pushSolverProcess() "
            << mySolversStack.size() << std::endl;
#endif
  if (!aProc) return;

  // Check if this process already is on the stack
  ProcFinder NewProcEquals(aProc);
  std::stack<FapSolverBase*> tmpStack(mySolversStack);
  for (; !tmpStack.empty(); tmpStack.pop())
    if (NewProcEquals(tmpStack.top()))
    {
      // New process has been added before - delete it
      delete aProc;
      return;
    }

#if FAP_DEBUG > 1
  std::cout <<"\t"<< aProc->getProcessSignature() << std::endl;
#endif
  mySolversStack.push(aProc);
}


void FapSolutionProcessManager::appendProcs(const std::vector<FapSolverBase*>& procs)
{
#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::appendProcs()";
#endif

  // Empty the stack into a vector such that we can search for identical processes
  std::vector<FapSolverBase*> allProcs;
  allProcs.reserve(mySolversStack.size() + procs.size());
  for (; !mySolversStack.empty(); mySolversStack.pop())
    allProcs.push_back(mySolversStack.top());

  // Check if the new processes are already running or in the solver stack
  for (FapSolverBase* proc : procs)
    if (!this->isEventRunning(proc->getEvent()) &&
        std::find_if(allProcs.begin(),allProcs.end(),ProcFinder(proc)) == allProcs.end())
    {
      // This process not yet in the stack - push it
      allProcs.push_back(proc);
#if FAP_DEBUG > 1
      std::cout <<"\n\t"<< proc->getProcessSignature();
#endif
    }
    else
      delete proc;

#if FAP_DEBUG > 1
  std::cout << std::endl;
#endif

  // Put back onto the stack in the reverse order
  std::vector<FapSolverBase*>::reverse_iterator rit;
  for (rit = allProcs.rbegin(); rit != allProcs.rend(); ++rit)
    mySolversStack.push(*rit);
}


bool FapSolutionProcessManager::empty() const
{
  return (mySolversStack.empty() &&
	  myPendingProcs.empty() &&
	  myRunningProcs.empty());
}


/*!
  Returns whether any process for a specified event is running.
*/

bool FapSolutionProcessManager::isEventRunning(const FmSimulationEvent* event) const
{
  for (const ProcessMap::value_type& p : myRunningProcs)
    if (p.second->getEvent() == event)
      return true;

  return false;
}


/*!
  Returns true if at least one process in \a groupID is running.
  If \a event is != 0 it returns whether a process for that event is running.
  If \a part is != 0 it returns whether a process is running on that part.
*/

bool FapSolutionProcessManager::isGroupRunning(int groupID,
					       const FmSimulationEvent* event,
					       const FmPart* part) const
{
  for (const ProcessMap::value_type& p : myRunningProcs)
    if (p.second->getGroupID() == groupID)
      if (event == NULL || p.second->getEvent() == event)
        if (part == NULL || p.second->getWorkPart() == part)
          return true;

  return false;
}


/*!
  Returns a vector of the running processes with \a groupID
  and if applicable, the \a workPart for the process.
  If \a event is non-zero, only the processes of that event
  and the master event (like reduction processes) are returned.
*/

void FapSolutionProcessManager::getRunningGroups(const FmSimulationEvent* event,
						 std::vector<FapProcID>& procs) const
{
  procs.clear();
  for (const ProcessMap::value_type& p : myRunningProcs)
    if (p.second->getEvent() == event || p.second->getEvent() == NULL)
      procs.push_back(std::make_pair(p.second->getGroupID(),
                                     p.second->getWorkPart()));
}


bool FapSolutionProcessManager::run()
{
  if (mySolversStack.empty() && myPendingProcs.empty())
    return this->batchExit(true);

  int maxProc = FmDB::getActiveAnalysis()->maxConcurrentProcesses.getValue();
  if ((int)myRunningProcs.size() >= maxProc)
    return true; // enough processes are running

#if FAP_DEBUG > 1
  static int callStack = 0;
  std::cout <<"\nFapSolutionProcessManager::run("
            << callStack+1 <<") "<< mySolversStack.size();
  if (!myPendingProcs.empty()) std::cout <<"+"<< myPendingProcs.size();
  if (!myRunningProcs.empty()) std::cout <<"+"<< myRunningProcs.size();
  std::cout << std::endl;
#endif

  // Try to execute the first queued pending process,
  // or the top stacked one if none are currently in the queue
  bool pending = false;
  FapSolverBase* topProc;
  if (myPendingProcs.empty())
    topProc = mySolversStack.top();
  else
  {
    // We have queued processes that are waiting for results they depend on
    pending = true;
    topProc = myPendingProcs.front();
    myPendingProcs.pop();
  }

  int topGID = topProc->getGroupID();
  std::string topSign = topProc->getProcessSignature();
  if (myRunningProcs.find(topSign) != myRunningProcs.end())
  {
    // We have a process running this task already - delete and pop stack
    std::cout <<" ** Duplicated process "<< topSign << std::endl;
    delete topProc;
    if (!pending) mySolversStack.pop();
    return this->run();
  }

  Fui::noUserInputPlease();
#if FAP_DEBUG > 1
  std::cout <<"Executing "<< topSign << (pending ? " [queue]":" [stack]") << std::endl;
  ++callStack;
#endif

  switch (topProc->execute())
    {
    case FapSolverBase::FAP_RESULTS_OK:
#if FAP_DEBUG > 1
      std::cout <<"--> RESULTS OK"<< std::endl;
#endif
      // Pop the stack - start over
      delete topProc;
      if (!pending) mySolversStack.pop();
      this->run();
      break;

    case FapSolverBase::FAP_NOT_EXECUTABLE:
#if FAP_DEBUG > 1
      std::cout <<"--> RESULTS FAILED"<< std::endl;
#endif
      // Pop the stack - all dependent results should also go away
      delete topProc;
      if (!pending) mySolversStack.pop();

      if (FFaAppInfo::isConsole())
      {
	// Kill all child processes and exit
	this->killAll(true);
	this->batchExit(false,1);
      }
      else if (!mySolversStack.empty() || !myPendingProcs.empty())
      {
	if (this->top()->getGroupID() == topGID)
	  this->run(); // try to run the next process of same kind, if any
	else
	  this->killAll(false); // kill pending processes
      }
      break;

    case FapSolverBase::FAP_PENDING_DEPENDENCIES:
#if FAP_DEBUG > 1
      std::cout <<"--> DEPENDENCIES"<< std::endl;
#endif
      // Do not touch the stack - start over
      this->run();

      // Put this process back on the queue of waiting processes if pending.
      // They will be first in line for execution, before the stacked ones.
      if (pending) myPendingProcs.push(topProc);
      break;

    case FapSolverBase::FAP_PENDING_DEPENDENCIES_BUT_WAIT:
#if FAP_DEBUG > 1
      std::cout <<"--> PENDING"<< std::endl;
#endif
      // Pop the stack - start over
      if (!pending) mySolversStack.pop();
      this->run();

      // Put this process on the queue of waiting processes instead.
      // They will be first in line for execution, before the stacked ones.
      myPendingProcs.push(topProc);
      break;

    case FapSolverBase::FAP_STARTED:
#if FAP_DEBUG > 1
      std::cout <<"--> STARTED"<< std::endl;
#endif
      // Pop the stack - put process on the list of running processes instead
      if (!pending) mySolversStack.pop();
      myRunningProcs[topSign] = topProc;
      if (maxProc > 1)
	ListUI <<"  -> Started concurrent process "<< (int)myRunningProcs.size()
	       <<" of maximum "<< maxProc <<"\n";
      // Start over, until we have maxProc concurrently running tasks
      if (maxProc > (int)myRunningProcs.size()) this->run();
      break;
    }

  Fui::okToGetUserInput();
#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::run("<< callStack--
            <<") returned."<< std::endl;
#endif
  return true;
}


void FapSolutionProcessManager::syncRunningProcesses()
{
  for (ProcessMap::value_type& p : myRunningProcs)
    p.second->syncRDB();
}


void FapSolutionProcessManager::onSolverProcessDeath(const std::string& processSign,
						     int exitCode)
{
  // Find the running process
  ProcessMap::iterator pit = myRunningProcs.find(processSign);
  if (pit == myRunningProcs.end())
  {
    std::cerr <<"FapSolutionProcessManager::onSolverProcessDeath() "
	      << processSign <<" NOT FOUND!\n";
    this->batchExit(false,2);
    return;
  }

  // Get some info on the process that just finished
  FmSimulationEvent* event = pit->second->getEvent();
  int groupID = pit->second->getGroupID();
  int eventID = event ? event->getID() : 0;

  // Remove process from the running processes map
  delete pit->second;
  myRunningProcs.erase(pit);

  if (groupID != FapSolverID::FAP_REDUCER)
  {
    // Syncronize the RSD with contents on disk,
    // but the update extractor for current event only
    FmResultStatusData* rsd;
    if (event)
      rsd = event->getResultStatusData();
    else
      rsd = FmDB::getMechanismObject()->getResultStatusData();
    FpModelRDBHandler::RDBSync(rsd, FmDB::getMechanismObject(),
			       event == FapSimEventHandler::getActiveEvent());
    if (event && groupID == FapSolverID::FAP_DYN_SOLVER)
      event->onChanged(); // for updating list view pixmap
  }
  myProcessDeathCB.invoke(groupID,eventID,processSign);

#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::onSolverProcessDeath()\n\t"
	    << processSign <<" ---> "<< exitCode <<" Grp: "<< groupID << std::endl;
#endif

  if (mySolversStack.empty() && myPendingProcs.empty())
    this->batchExit(!exitCode,exitCode); // No more pending processes, exit
  else if (exitCode == 0 || this->top()->getGroupID() == groupID)
    this->run(); // Run next pending process
  else
  {
    // Current process failed, kill all pending processes and exit
    this->killAll(false);
    this->batchExit(false,exitCode);
  }
}


void FapSolutionProcessManager::afterBatchPreparation(int groupID)
{
  mySolversStack.pop();

  if (groupID != FapSolverID::FAP_REDUCER)
    FpModelRDBHandler::RDBSync(FapSimEventHandler::getActiveRSD(),
			       FmDB::getMechanismObject());

  this->run();
}


void FapSolutionProcessManager::killAll(bool runningProcessesAlso,
					bool deleteTopProcessAlso)
{
  if (runningProcessesAlso && !myRunningProcs.empty())
  {
#if FAP_DEBUG > 1
    std::cout <<"FapSolutionProcessManager::killAll() "
	      << myRunningProcs.size() <<" running processes killed\n";
#endif
    for (ProcessMap::value_type& p : myRunningProcs)
      p.second->kill();
  }

#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::killAll() "
	    << mySolversStack.size() + myPendingProcs.size()
	    <<" pending processes killed\n";
#endif
  if (!mySolversStack.empty())
  {
    if (deleteTopProcessAlso)
      delete mySolversStack.top();
    mySolversStack.pop();

    while (!mySolversStack.empty())
    {
      delete mySolversStack.top();
      mySolversStack.pop();
    }
  }

  while (!myPendingProcs.empty())
  {
    delete myPendingProcs.front();
    myPendingProcs.pop();
  }
}


bool FapSolutionProcessManager::batchExit(bool saveResults, int status)
{
  if (!this->empty() || !FFaAppInfo::isConsole())
    return true; // Solvers are still running or this is not a batch execution

#if FAP_DEBUG > 1
  std::cout <<"FapSolutionProcessManager::batchExit()"<< std::endl;
#endif

  // All solvers have terminated the batch execution.
  // Now check for automatic curve- and animation export.

  const std::string& aPath = FmDB::getMechanismObject()->getAbsModelFilePath();

  std::string exportDir, exportedGraph;
  FFaCmdLineArg::instance()->getValue("exportCurves",exportDir);
  if (!exportDir.empty() && status == 0)
  {
    // Export all curves that are toggled for auto-export.
    std::string solveCmd;
    FFaCmdLineArg::instance()->getValue("solve",solveCmd);
    if (FFaLowerCaseString(solveCmd.substr(0,5)) == "event")
      FapExportCmds::autoExportCurves(exportDir,10);
    else if (FFaLowerCaseString(solveCmd.substr(0,4)) == "none")
      exportedGraph = FapExportCmds::autoExportCurves(exportDir,100);
    else
      exportedGraph = FapExportCmds::autoExportCurves(exportDir);
  }

  bool exportAnims = false;
  FFaCmdLineArg::instance()->getValue("exportAnimations",exportAnims);
  if (exportAnims && status == 0)
    // Export all animations that are toggled for auto-export
    FapExportCmds::autoExportToVTF(aPath);

  if (!saveResults || status != 0)
    ListUI <<"\n===> Exiting without save.";
  ListUI <<"\n";
  FapFileCmds::exit(saveResults,false,status);

  return false;
}


FapSolverBase* FapSolutionProcessManager::top() const
{
  if (!myPendingProcs.empty())
    return myPendingProcs.front();
  else if (!mySolversStack.empty())
    return mySolversStack.top();
  else
    return NULL;
}
