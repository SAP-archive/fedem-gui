// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapSelectRefCSCmds.H"
#include "vpmUI/FuiModes.H"
#include "vpmUI/vpmUIComponents/FuiPositionData.H"
#include "vpmUI/Fui.H"

int FapSelectRefCSCmds::myState = 0;
FuiPositionData * FapSelectRefCSCmds::ourActiveUI = 0;

void FapSelectRefCSCmds::init()
{
}

void FapSelectRefCSCmds::selectRefCS(FuiPositionData * posUI)
{
  ourActiveUI = posUI;
  
  FuiModes::setMode(FuiModes::SELECTREFCS_MODE);
}

void FapSelectRefCSCmds::enterMode()
{
  FapSelectRefCSCmds::setState(START); // To get the tip set right.
}

void FapSelectRefCSCmds::cancelMode()
{
  if (ourActiveUI)
    ourActiveUI->finishRefCSSelection();
  ourActiveUI = 0;
}

void FapSelectRefCSCmds::setState(int newState)
{
  FapSelectRefCSCmds::myState = newState;
  Fui::tip("Select reference CS by picking in the 3D view or selecting from the objects browser. ");
}

void FapSelectRefCSCmds::done()
{
  FuiModes::cancel();
}
