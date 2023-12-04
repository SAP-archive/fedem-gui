// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtPreferences.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"

//----------------------------------------------------------------------------

// Qt implementation of static create method in FuiPreferences
FuiPreferences* FuiPreferences::create(int xpos, int ypos,
				       int width, int height,
				       const char* title,
				       const char* name)
{
  return new FuiQtPreferences(0,xpos,ypos,width,height,title,name);
}
//----------------------------------------------------------------------------

FuiQtPreferences::FuiQtPreferences(QWidget* parent, int xpos, int ypos,
				   int width,int height,
				   const char* title,
				   const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  for (int iField = 0; iField < NFIELDS; iField++) {
    this->optFields[iField] = new FFuQtIOField(this);
    this->labels[iField] = new FFuQtLabel(this);
  }
  this->reducerFrame = new FFuQtLabelFrame(this);
  this->eqSolverToggle = new FFuQtToggleButton(this);
  this->eqSolverAutomatic = new FFuQtRadioButton(this);
  this->eqSolverManual = new FFuQtRadioButton(this);
  this->recMatrixToggle = new FFuQtToggleButton(this);
  this->recMatrixAutomatic = new FFuQtRadioButton(this);
  this->recMatrixManual = new FFuQtRadioButton(this);
  this->remoteSolveFrame = new FFuQtLabelFrame(this);
  this->solverPrefixToggle = new FFuQtToggleButton(this);
  this->solverPathToggle = new FFuQtToggleButton(this);
  this->dialogButtons = new FFuQtDialogButtons(this);
  this->eqSolverCacheLabel = new FFuQtLabel(this);
  this->recMatrixCacheLabel = new FFuQtLabel(this);

  this->FuiPreferences::initWidgets();
}
//----------------------------------------------------------------------------

FuiQtPreferences::~FuiQtPreferences()
{
}
//----------------------------------------------------------------------------
