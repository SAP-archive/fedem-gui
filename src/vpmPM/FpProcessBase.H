// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FP_PROCESS_BASE_H
#define FP_PROCESS_BASE_H

#include <cstddef>

struct FpProcessOptions;
class  FpProcess;


class FpProcessBase
{
public:
  FpProcessBase() : myActualProcess(NULL), IWasKilled(false) {}
  virtual ~FpProcessBase();

  void kill();

protected:
  int start(const char* name, int gID, const FpProcessOptions& opts);

private:
  FpProcess* myActualProcess;

protected:
  bool IWasKilled;
};

#endif
