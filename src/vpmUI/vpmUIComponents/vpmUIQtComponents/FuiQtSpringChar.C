// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSpringChar.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"


FuiQtSpringChar::FuiQtSpringChar(QWidget* parent, int xpos, int ypos,
				 int width, int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  mySpringFunctionFrame       = new FFuQtLabelFrame(this);
  myFailureFrame              = new FFuQtLabelFrame(this);
  myYieldFrame                = new FFuQtLabelFrame(this);

  mySpringFunctionDescription = new FFuQtLabel(this);

  mySpringFunctionField       = new FuiQtQueryInputField(this);
  myYieldForceMaxEngineField  = new FuiQtQueryInputField(this);
  myYieldForceMinEngineField  = new FuiQtQueryInputField(this);

  myDeflectionMaxToggle = new FFuQtToggleButton (this);
  myDeflectionMinToggle = new FFuQtToggleButton (this);
  myForceMaxToggle      = new FFuQtToggleButton (this);
  myForceMinToggle      = new FFuQtToggleButton (this);
  myYieldForceMaxToggle = new FFuQtToggleButton (this);
  myYieldForceMinToggle = new FFuQtToggleButton (this);
  myYieldDeflectionMaxToggle = new FFuQtToggleButton (this);

  myDeflectionMaxField = new FFuQtIOField (this);
  myDeflectionMinField = new FFuQtIOField (this);
  myForceMaxField      = new FFuQtIOField (this);
  myForceMinField      = new FFuQtIOField (this);
  myYieldDeflectionMaxField = new FFuQtIOField (this);

  this->initWidgets();
}

FuiQtSpringChar::~FuiQtSpringChar()
{
}
