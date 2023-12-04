// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FP_PROCESS_OPTIONS_H
#define FP_PROCESS_OPTIONS_H

#include <string>
#include <vector>

#include "FFaLib/FFaDynCalls/FFaDynCB.H"


struct FpProcessOptions
{
  std::string workingDir;
  std::string prefix;
  std::string name;
  std::vector<std::string> args;
  FFaDynCB1<int> deathHandler; //!< Invoked with the exit status of the process
};

#endif
