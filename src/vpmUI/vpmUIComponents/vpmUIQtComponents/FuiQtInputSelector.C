// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtInputSelector.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"


FuiQtInputSelector::FuiQtInputSelector(QWidget* parent,
				       int xpos, int ypos,
				       int width,int height,
				       const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myLabelFrame = new FFuQtLabelFrame(this);
  myObjectSelector = new FuiQtQueryInputField(this);
  myDofLabel = new FFuQtLabel(this);
  myDofSelector = new FFuQtOptionMenu(this);
  myVariableLabel = new FFuQtLabel(this);
  myVariableSelector = new FFuQtOptionMenu(this);

  this->initWidgets();
}
