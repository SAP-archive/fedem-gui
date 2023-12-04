// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtMotionType.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"


FuiQtMotionType::FuiQtMotionType(QWidget* parent, int nB,
				 int xpos, int ypos,
				 int width, int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name), FuiMotionType(nB)
{
  myFrame = new FFuQtLabelFrame(this);

  for (unsigned int i = 0; i < myMotionTypeLabels.size(); i++)
    myMotionTypeButtons.push_back(new FFuQtRadioButton(this));

  myAddButton = new FFuQtToggleButton(this);

  this->initWidgets();
}
