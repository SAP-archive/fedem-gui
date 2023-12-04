// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSprDaForce.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"


FuiQtSprDaForce::FuiQtSprDaForce(QWidget* parent, int xpos, int ypos,
				 int width, int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myFrame = new FFuQtLabelFrame(this);
  myFunctionLabel = new FFuQtLabel(this);
  myFunctionField = new FuiQtQueryInputField(this);
  myScaleLabel = new FFuQtLabel(this);
  myScaleField = new FuiQtQueryInputField(this);
  myIsDefDamperToggle = new FFuQtToggleButton(this);

  this->initWidgets();
}
