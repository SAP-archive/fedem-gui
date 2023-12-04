// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapWorkSpaceCmds.H"

#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"

#include "vpmUI/Fui.H"
#include "vpmUI/vpmUITopLevels/FuiMainWindow.H"
#include "vpmUI/vpmUIComponents/FuiWorkSpace.H"

//----------------------------------------------------------------------------

void FapWorkSpaceCmds::init()
{
  FFuaCmdItem* cmdItem = 0;

  cmdItem = new FFuaCmdItem("cmdId_workSpace_cascade");
  cmdItem->setSmallIcon(cascade_xpm);
  cmdItem->setText("Cascade");
  cmdItem->setToolTip("Cascade");
  cmdItem->setActivatedCB(FFaDynCB0S(FapWorkSpaceCmds::cascade));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_workSpace_tile");
  cmdItem->setSmallIcon(tile_xpm);
  cmdItem->setText("Tile");
  cmdItem->setToolTip("Tile");
  cmdItem->setActivatedCB(FFaDynCB0S(FapWorkSpaceCmds::tile));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_workSpace_tabs");
  cmdItem->setSmallIcon(tabs_xpm);
  cmdItem->setText("Tabs");
  cmdItem->setToolTip("Tabs");
  cmdItem->setActivatedCB(FFaDynCB0S(FapWorkSpaceCmds::tabs));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive, bool&));

  cmdItem = new FFuaCmdItem("cmdId_workSpace_subWins");
  cmdItem->setSmallIcon(tile_xpm);
  cmdItem->setText("Sub Windows");
  cmdItem->setToolTip("Sub Windows");
  cmdItem->setActivatedCB(FFaDynCB0S(FapWorkSpaceCmds::subWins));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive, bool&));
}
//----------------------------------------------------------------------------

void FapWorkSpaceCmds::cascade()
{
  Fui::getMainWindow()->getWorkSpace()->cascadeWins();
}
//----------------------------------------------------------------------------

void FapWorkSpaceCmds::tile()
{
  Fui::getMainWindow()->getWorkSpace()->tileWins();
}
//----------------------------------------------------------------------------

void FapWorkSpaceCmds::tabs()
{
  Fui::getMainWindow()->getWorkSpace()->tabWins();
}
//----------------------------------------------------------------------------

void FapWorkSpaceCmds::subWins()
{
  Fui::getMainWindow()->getWorkSpace()->subWins();
}
//----------------------------------------------------------------------------



