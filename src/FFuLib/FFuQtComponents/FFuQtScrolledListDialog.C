// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FFuLib/FFuQtComponents/FFuQtScrolledList.H"
#include "FFuLib/FFuQtComponents/FFuQtScrolledListDialog.H"


FFuQtScrolledListDialog::FFuQtScrolledListDialog(QWidget*,
						 int xpos, int ypos,
						 int width,int height,
						 const char* title,
						 const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name)
{
  myItemSelector = new FFuQtScrolledList(this);
  myDialogButtons = new FFuQtDialogButtons(this);
  labNotesImage = new FFuQtLabel(this);
  labNotesLabel = new FFuQtLabel(this);
  labNotesText = new FFuQtLabel(this);

  this->FFuScrolledListDialog::init();
}


void FFuQtScrolledListDialog::closeEvent(QCloseEvent*)
{
  this->callOkButtonClickedCB();
}
