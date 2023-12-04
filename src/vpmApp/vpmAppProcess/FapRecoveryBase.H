// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_RECOVERY_BASE_H
#define FAP_RECOVERY_BASE_H

#include "vpmApp/vpmAppProcess/FapSolverBase.H"

class FmResultStatusData;


class FapRecoveryBase : public FapSolverBase
{
protected:
  FapRecoveryBase(FmPart* aPart, FmSimulationEvent* event = NULL);

public:
  virtual int checkDependencies() const;
  virtual int execute();
  virtual std::string getProcessSignature() const;
  virtual FmSimulationEvent* getEvent() const { return myWorkEvent; }
  virtual FmPart* getWorkPart() const { return myWorkPart; }

protected:
  virtual int startProcess(const std::string&) { return FAP_NOT_EXECUTABLE; }

  int startRecovery(const char* task, const std::string& rdbPath,
                    const std::string& addOptions);
  void onActualProcessDeath(int exitValue);

  FmResultStatusData* getTopLevelRSD() const;

  std::string getFEDataFile(const std::string& rdbPath) const;
  std::string getFRSfiles(const std::string& solveTask) const;
  bool getInputAndRunDirs(std::string& dPath,
                          std::string* lPath = NULL,
                          std::string* rPath = NULL) const;

public:
  std::string getRunDir(bool fullPath = false, bool verifyPath = false) const;

protected:
  FmSimulationEvent* myWorkEvent;
  FmPart* myWorkPart;
  std::string mySubTask;
  mutable std::string myProcessSignature;
  bool amIPreparingForBatch;
};

#endif
