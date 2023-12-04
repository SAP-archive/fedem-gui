// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_SOLUTION_PROCESS_MGR_H
#define FAP_SOLUTION_PROCESS_MGR_H

#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>


class FapSolverBase;
class FmSimulationEvent;
class FmPart;

typedef std::pair<int,FmPart*> FapProcID;


class FapSolutionProcessManager : public FFaSingelton<FapSolutionProcessManager>
{
public:
  FapSolutionProcessManager() {}

  // Pushes a solver process on the stack.
  // Used by dependency checks from each target process.
  void pushSolverProcess(FapSolverBase* aProc);

  // Appends a list of processes to the end of the stack.
  // Used when solving multiple events.
  void appendProcs(const std::vector<FapSolverBase*>& procs);

  // Returns true if there is at least one process running for specified event.
  bool isEventRunning(const FmSimulationEvent* event) const;
  // Returns true if there is at least one process with the groupID running.
  bool isGroupRunning(int groupID, const FmSimulationEvent* event = NULL,
		      const FmPart* part = NULL) const;

  // Returns a vector with groupID and workPart for the running processes.
  void getRunningGroups(const FmSimulationEvent* event,
			std::vector<FapProcID>& procs) const;

  // Pops processes from the stack until max limit on concurrent processes
  // is met, or the next process blocks due to unfinished dependencies.
  bool run();

  // Syncronizes the RDB for all processes currently running.
  void syncRunningProcesses();

  // Returns true if there are no pending processes on the stack.
  // There might be running processes that have been popped already...
  bool empty() const;

  // Tries to pop the stack again - same as run() if status is OK.
  void onSolverProcessDeath(const std::string& processSign, int exitCode);
  void afterBatchPreparation(int groupID);

  // Call-back when solver has died. Carries groupID and eventID of the process.
  void setProcessDeathCB(const FFaDynCB3<int,int,const std::string&>& aDynCB)
  { myProcessDeathCB = aDynCB; }

  void clearProcessDeathCB() { myProcessDeathCB.erase(); }

  void killAll(bool runningProcessesAlso = true,
	       bool deleteTopProcessAlso = true);

  // Exits after all solvers have been run if we are in batch mode.
  bool batchExit(bool saveResults = false, int status = 0);

protected:
  // Returns the next process to execute.
  FapSolverBase* top() const;

private:
  std::stack<FapSolverBase*>            mySolversStack;
  std::queue<FapSolverBase*>            myPendingProcs;
  std::map<std::string,FapSolverBase*>  myRunningProcs;
  FFaDynCB3<int,int,const std::string&> myProcessDeathCB;
};

#endif
