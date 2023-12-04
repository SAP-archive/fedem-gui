// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_LINK_REDUCER_H
#define FAP_LINK_REDUCER_H

#include <string>

#include "vpmApp/vpmAppProcess/FapSolverBase.H"


class FapLinkReducer : public FapSolverBase
{
public:
  FapLinkReducer(FmPart* part, bool chkRecovery = false, bool preBatch = false);

  virtual int checkDependencies() const { return this->checkDependency(false); }
  virtual int createInput(std::string& rdbPath);
  virtual int execute();
  virtual void syncRDB();
  virtual std::string getProcessSignature() const;
  virtual FmPart* getWorkPart() const { return myWorkPart; }

  static bool isReduced(FmPart* part, bool silence = false);

protected:
  void onActualProcessDeath(int exitValue);

  int checkDependency(bool silence) const;

  void WEmessage(int severity, const std::string& theMessage) const;

private:
  FmPart* myWorkPart;
  mutable unsigned long myWantedCS;
  mutable std::string myProcessSignature;

  bool amICheckingRecovery;
  bool amIPreparingForBatch;
};

#endif
