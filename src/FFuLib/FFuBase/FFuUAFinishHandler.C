// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuUAFinishHandler.H"


bool FFuUAFinishHandler::invokeFinishedCB()
{
  if (this->finishedCB.empty())
    return false;

  this->finishedCB.invoke();
  return true;
}
