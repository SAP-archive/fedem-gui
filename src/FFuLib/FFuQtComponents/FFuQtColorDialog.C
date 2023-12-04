// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FFuLib/FFuQtComponents/FFuQtColorSelector.H"
#include "FFuLib/FFuQtComponents/FFuQtColorDialog.H"


FFuQtColorDialog::FFuQtColorDialog(int xpos, int ypos,
				   int width,int height,
				   const char* title, const char *name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height, title, name)
{
  myColorSelector = new FFuQtColorSelector(this);
  myDialogButtons = new FFuQtDialogButtons(this);

  this->init();
}


void FFuQtColorDialog::closeEvent(QCloseEvent*)
{
  myOkButtonClickedCB.invoke(myColorSelector->getColor());
  myOkButtonClickedWPtrCB.invoke(myColorSelector->getColor(),this);
}
