// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSNCurveSelector.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"


FuiQtSNCurveSelector::FuiQtSNCurveSelector(QWidget* parent,
					   int xpos, int ypos,
					   int width, int height,
					   const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  stdLabel      = new FFuQtLabel(this);
  curveLabel    = new FFuQtLabel(this);
  stdTypeMenu   = new FFuQtOptionMenu(this);
  curveTypeMenu = new FFuQtOptionMenu(this);

  this->initWidgets();
}
