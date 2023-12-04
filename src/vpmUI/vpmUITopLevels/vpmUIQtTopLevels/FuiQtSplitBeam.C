// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtSplitBeam.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiSplitBeam* FuiSplitBeam::create(int xpos, int ypos,
				   int width, int height,
				   const char* title,
				   const char* name)
{
  return new FuiQtSplitBeam(xpos,ypos,width,height,title,name);
}


FuiQtSplitBeam::FuiQtSplitBeam(int xpos, int ypos,
			       int width, int height,
			       const char* title,
			       const char* name)
  : FFuQtModalDialog(xpos,ypos,width,height,title,name,
                     Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  myNumField = new FFuQtLabelField(this);
  myDialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
