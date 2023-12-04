// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtRepeatCurve.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiRepeatCurve* FuiRepeatCurve::create(int xpos, int ypos,
				       int width, int height,
				       const char* title,
				       const char* name)
{
  return new FuiQtRepeatCurve(xpos,ypos,width,height,title,name);
}


FuiQtRepeatCurve::FuiQtRepeatCurve(int xpos, int ypos,
				   int width, int height,
				   const char* title,
				   const char* name)
  : FFuQtModalDialog(xpos,ypos,width,height,title,name,
                     Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  myLabel = new FFuQtLabel(this);
  myFromField = new FFuQtLabelField(this);
  myToField = new FFuQtLabelField(this);
  myDialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
