// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef _FAP_DYNAMIC_SOLVER_H_
#define _FAP_DYNAMIC_SOLVER_H_

#include "FapSolverBase.H"


class FmResultStatusData;

class FapDynamicSolver : public FapSolverBase
{
public:
  FapDynamicSolver(FmSimulationEvent* event = 0, bool preBatch = false);

  virtual int checkDependencies() const;
  virtual int createInput(std::string& rdbPath);
  virtual int execute();
  virtual std::string getProcessSignature() const;
  virtual FmSimulationEvent* getEvent() const { return myWorkEvent; }

protected:
  void onActualProcessDeath(int exitValue);

  int createInput(std::vector<std::string>& rdbPath);

  FmResultStatusData* getTopLevelRSD() const;

private:
  FmSimulationEvent* myWorkEvent;
  std::string myCurrentSolve;
  mutable std::string myProcessSignature;
  bool amIPreparingForBatch;
};

#endif
