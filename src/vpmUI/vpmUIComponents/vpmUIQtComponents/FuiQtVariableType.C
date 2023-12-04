// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtVariableType.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"


FuiQtVariableType::FuiQtVariableType(QWidget* parent,
				     int xpos, int ypos,
				     int width, int height,
				     const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myFrame    = new FFuQtLabelFrame(this);
  myTypeMenu = new FFuQtOptionMenu(this);

  this->initWidgets();
}
