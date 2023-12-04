// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmPM/FpProcessBase.H"
#include "vpmPM/FpProcess.H"


FpProcessBase::~FpProcessBase()
{
  if (myActualProcess)
    if (!myActualProcess->kill(true))
      delete myActualProcess;
}


int FpProcessBase::start(const char* name, int gID, const FpProcessOptions& opts)
{
  myActualProcess = new FpProcess(name,gID);
  return myActualProcess->run(opts);
}


void FpProcessBase::kill()
{
  IWasKilled = true;
  if (myActualProcess)
    myActualProcess->kill();
}
