// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_FEFATIGUE_PROCESS_H
#define FAP_FEFATIGUE_PROCESS_H

#include "FapRecoveryBase.H"


class FapFEFatigueProcess : public FapRecoveryBase
{
public:
  FapFEFatigueProcess(FmPart* aPart);

  virtual int checkDependencies() const;
  virtual int execute();

protected:
  void onActualProcessDeath(int exitValue);

  std::string myNPath;
  mutable std::string myFppFile;
};

#endif
