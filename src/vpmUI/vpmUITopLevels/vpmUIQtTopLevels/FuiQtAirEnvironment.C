// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtAirEnvironment.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiAirEnvironment* FuiAirEnvironment::create(int xpos, int ypos,
					     int width, int height,
					     const char* title,
					     const char* name)
{
  return new FuiQtAirEnvironment(0,xpos,ypos,width,height,title,name);
}


FuiQtAirEnvironment::FuiQtAirEnvironment(QWidget* parent,
					 int xpos, int ypos,
					 int width, int height,
					 const char* title,
					 const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->stallModLabel  = new FFuQtLabel(this);
  this->stallModMenu   = new FFuQtOptionMenu(this);

  this->useCMToggle    = new FFuQtToggleButton(this);

  this->infModLabel    = new FFuQtLabel(this);
  this->infModMenu     = new FFuQtOptionMenu(this);

  this->indModLabel    = new FFuQtLabel(this);
  this->indModMenu     = new FFuQtOptionMenu(this);

  this->aTolerField    = new FFuQtLabelField(this);

  this->tipLossLabel   = new FFuQtLabel(this);
  this->tipLossMenu    = new FFuQtOptionMenu(this);

  this->hubLossLabel   = new FFuQtLabel(this);
  this->hubLossMenu    = new FFuQtOptionMenu(this);

  this->windFrame      = new FFuQtLabelFrame(this);
  this->windToggle     = new FFuQtToggleButton(this);
  this->windTurbButton = new FFuQtPushButton(this);
  this->windSpeedField = new FFuQtLabelField(this);
  this->windDirField   = new FFuQtLabelField(this);
  this->windField      = new FFuQtFileBrowseField(this);

  this->towerFrame     = new FFuQtLabelFrame(this);
  this->towerPotToggle = new FFuQtToggleButton(this);
  this->towerShdToggle = new FFuQtToggleButton(this);
  this->towerField     = new FFuQtFileBrowseField(this);

  this->airDensField   = new FFuQtLabelField(this);
  this->kinViscField   = new FFuQtLabelField(this);
  this->dtAeroField    = new FFuQtLabelField(this);
  this->dtAeroToggle   = new FFuQtToggleButton(this);

  this->dialogButtons  = new FFuQtDialogButtons(this);

  this->initWidgets();
}
