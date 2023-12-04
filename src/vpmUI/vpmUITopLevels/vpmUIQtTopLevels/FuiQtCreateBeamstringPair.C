// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtCreateBeamstringPair.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiCreateBeamstringPair* FuiCreateBeamstringPair::create(int xpos, int ypos,
							 int width, int height,
							 const char* title,
							 const char* name)
{
  return new FuiQtCreateBeamstringPair(0,xpos,ypos,width,height,title,name);
}


FuiQtCreateBeamstringPair::FuiQtCreateBeamstringPair(QWidget* parent,
						     int xpos, int ypos,
						     int width, int height,
						     const char* title,
						     const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name,Qt::MSWindowsFixedSizeDialogHint)
{
  this->headerImage         = new FFuQtLabel(this);
  this->beamstringLabel1    = new FFuQtLabel(this);
  this->beamstringMenu1     = new FuiQtQueryInputField(this);
  this->beamstringLabel2    = new FFuQtLabel(this);
  this->beamstringMenu2     = new FuiQtQueryInputField(this);
  this->stiffnessFunctionLabel = new FFuQtLabel(this);
  this->stiffnessFunctionMenu  = new FuiQtQueryInputField(this);
  this->useRadialSpringsToggle = new FFuQtToggleButton(this);
  this->notesImage          = new FFuQtLabel(this);
  this->notesLabel          = new FFuQtLabel(this);
  this->notesSeparator      = new FFuQtLabelFrame(this);
  this->notesText           = new FFuQtLabel(this);
  this->buttonSeparator     = new FFuQtLabelFrame(this);
  this->createButton        = new FFuQtPushButton(this);
  this->eraseButton         = new FFuQtPushButton(this);
  this->closeButton         = new FFuQtPushButton(this);
  this->helpButton          = new FFuQtPushButton(this);

  this->initWidgets();
}
