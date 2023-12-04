// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_GAGE_RECOVERY_H
#define FAP_GAGE_RECOVERY_H

#include "FapRecoveryBase.H"


class FapGageRecovery : public FapRecoveryBase
{
public:
  FapGageRecovery(FmPart* aPart, FmSimulationEvent* event = 0,
		  bool preBatch = false);

  virtual int createInput(std::string& rdbPath);

protected:
  virtual int startProcess(const std::string& rdbPath);
};

#endif
