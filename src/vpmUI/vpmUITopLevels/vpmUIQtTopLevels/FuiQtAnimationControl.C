// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FuiQtAnimationControl.H"


FuiAnimationControl* FuiAnimationControl::create(int xpos, int ypos,
						 int width,int height,
						 const char* title,
						 const char* name)
{
  return new FuiQtAnimationControl(xpos,ypos,width,height,title,name);
}


FuiQtAnimationControl::FuiQtAnimationControl(int xpos, int ypos,
					     int width,int height,
					     const char* title,
					     const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name,Qt::WindowStaysOnTopHint)
{
  this->cameraFrame       = new FFuQtLabelFrame(this);
  this->cameraLabel       = new FFuQtLabel(this);
  this->cameraMenu        = new FuiQtQueryInputField(this);

  this->motionFrame       = new FFuQtLabelFrame(this);
  this->linkMotionToggle  = new FFuQtToggleButton(this);
  this->triadMotionToggle = new FFuQtToggleButton(this);

  this->defFrame      = new FFuQtLabelFrame(this);
  this->defToggle     = new FFuQtToggleButton(this);
  this->defScaleLabel = new FFuQtLabel(this);
  this->defScaleField = new FFuQtIOField(this);

  this->legendFrame  = new FFuQtLabelFrame(this);
  this->fringeToggle = new FFuQtToggleButton(this);
  this->legendToggle = new FFuQtToggleButton(this);

  this->legendColorsLabel  = new FFuQtLabel(this);
  this->legendColorsMenu   = new FFuQtOptionMenu(this);
  this->legendMappingLabel = new FFuQtLabel(this);
  this->legendMappingMenu  = new FFuQtOptionMenu(this);
  this->legendLookLabel    = new FFuQtLabel(this);
  this->legendLookMenu     = new FFuQtOptionMenu(this);

  this->legendMaxLabel = new FFuQtLabel(this);
  this->legendMaxField = new FFuQtIOField(this);
  this->legendMinLabel = new FFuQtLabel(this);
  this->legendMinField = new FFuQtIOField(this);

  this->tickMarkFrame      = new FFuQtLabelFrame(this);
  this->tickMarkCountRadio = new FFuQtRadioButton(this);
  this->tickMarkCountField = new FFuQtIOField(this);
  this->tickMarkSpaceRadio = new FFuQtRadioButton(this);
  this->tickMarkSpaceField = new FFuQtIOField(this);

  this->dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
