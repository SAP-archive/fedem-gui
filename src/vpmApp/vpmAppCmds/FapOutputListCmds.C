// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapOutputListCmds.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFuLib/FFuAuxClasses/FFuaIdentifiers.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "vpmUI/vpmUITopLevels/FuiOutputList.H"


void FapOutputListCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_outputList_copy");
  cmdItem->setText("Copy");
  cmdItem->setToolTip("Copy");
  cmdItem->setAccelKey(FFuaKeyCode::CtrlAccel+FFuaKeyCode::C);
  cmdItem->setActivatedCB(FFaDynCB0S(FapOutputListCmds::copy));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapOutputListCmds::getCopySensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_outputList_selectAll");
  cmdItem->setText("Select &All");
  cmdItem->setToolTip("Select All");
  cmdItem->setAccelKey(FFuaKeyCode::CtrlAccel+FFuaKeyCode::A);
  cmdItem->setActivatedCB(FFaDynCB0S(FapOutputListCmds::selectAll));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapOutputListCmds::getSelectAllSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_outputList_clear");
  cmdItem->setText("Clear");
  cmdItem->setToolTip("Clear");
  // there is no "standard" accel sequence for clear. should we "make" one up?
  cmdItem->setActivatedCB(FFaDynCB0S(FapOutputListCmds::clear));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapOutputListCmds::getClearSensitivity,bool&));
}

//! Returns pointer to FuiOutputList. Might be 0
FuiOutputList* FapOutputListCmds::list()
{
  return dynamic_cast<FuiOutputList*>(FFuTopLevelShell::getInstanceByType(FuiOutputList::getClassTypeID()));
}


void FapOutputListCmds::clear()
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    ui->clearList();
}

void FapOutputListCmds::copy()
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    ui->copySelected();
}

void FapOutputListCmds::selectAll()
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    ui->selectAll();
}

void FapOutputListCmds::getClearSensitivity(bool& sensitivity)
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    sensitivity = ui->hasText();
  else
    sensitivity = false;
}

void FapOutputListCmds::getCopySensitivity(bool& sensitivity)
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    sensitivity = ui->hasSelectedText();
  else
    sensitivity = false;
}

void FapOutputListCmds::getSelectAllSensitivity(bool& sensitivity)
{
  FuiOutputList* ui = FapOutputListCmds::list();
  if (ui)
    sensitivity = ui->hasText();
  else
    sensitivity = false;
}
