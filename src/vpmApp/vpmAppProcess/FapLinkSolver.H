// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_LINK_SOLVER_H
#define FAP_LINK_SOLVER_H

#include "FapRecoveryBase.H"


class FapLinkSolver : public FapRecoveryBase
{
public:
  FapLinkSolver(FmPart* aPart);

  virtual int checkDependencies() const;
  virtual int createInput(std::string& rdbPath);

protected:
  virtual int startProcess(const std::string& rdbPath);
};

#endif
