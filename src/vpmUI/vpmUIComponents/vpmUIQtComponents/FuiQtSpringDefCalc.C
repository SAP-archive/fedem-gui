// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSpringDefCalc.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"


FuiQtSpringDefCalc::FuiQtSpringDefCalc(QWidget* parent, int xpos, int ypos,
				       int width, int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myFrame             = new FFuQtLabelFrame(this);

  myVariableLabel     = new FFuQtLabel(this);
  myVariableField     = new FFuQtIOField(this);

  myILengthField      = new FFuQtIOField(this);
  myIDeflField        = new FFuQtIOField(this);

  myILToggle          = new FFuQtRadioButton(this);
  myIDToggle          = new FFuQtRadioButton(this);

  myLengthChangeLabel = new FFuQtLabel(this);
  myLengthEngineField = new FuiQtQueryInputField(this);

  this->initWidgets();
}
