// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtListView.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FuiQtEigenOptions.H"

//----------------------------------------------------------------------------

FuiEigenOptions* FuiEigenOptions::create(int xpos, int ypos,
					 int width, int height,
					 const char* title,
					 const char* name)
{
  return new FuiQtEigenOptions(xpos,ypos,width,height,title,name);
}
//----------------------------------------------------------------------------

FuiQtEigenOptions::FuiQtEigenOptions(int xpos, int ypos,
				     int width, int height,
				     const char* title,
				     const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name)
{
  this->selectLabel = new FFuQtLabel(this);
  this->modeLabel = new FFuQtLabel(this);
  this->timeLabel = new FFuQtLabel(this);
  this->selectedModesLabel = new FFuQtLabel(this);

  this->modeMenu = new FFuQtOptionMenu(this);
  this->timeMenu = new FFuQtOptionMenu(this);

  this->addButton = new FFuQtPushButton(this);
  this->deleteButton = new FFuQtPushButton(this);

  FFuQtFrame* sep = new FFuQtFrame(this);
  this->separator = sep;
  sep->setFrameStyle(QFrame::HLine | QFrame::Sunken);

  this->selectedModesView = new FFuQtListView(this);

  this->autoVTFToggle = new FFuQtToggleButton(this);
  this->autoVTFField  = new FFuQtFileBrowseField(this);

  this->dialogButtons = new FFuQtDialogButtons(this);

  this->FuiEigenOptions::initWidgets();
}
