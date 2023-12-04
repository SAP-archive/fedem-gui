// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtModelPreferences.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtMemo.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiModelPreferences* FuiModelPreferences::create(int xpos, int ypos,
						 int width, int height,
						 const char* title,
						 const char* name)
{
  return new FuiQtModelPreferences(NULL,xpos,ypos,width,height,title,name);
}


FuiQtModelPreferences::FuiQtModelPreferences(QWidget* parent,
					     int xpos, int ypos,
					     int width, int height,
					     const char* title,
					     const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->descriptionFrame = new FFuQtLabelFrame(this);
  this->descriptionMemo  = new FFuQtMemo(this);

  this->repositoryFrame = new FFuQtLabelFrame(this);
  this->repositoryField = new FFuQtIOField(this);
  this->changeButton    = new FFuQtPushButton(this);
  this->switchButton    = new FFuQtPushButton(this);
  this->overwriteButton = new FFuQtToggleButton(this);

  this->unitsFrame = new FFuQtLabelFrame(this);
  this->unitsLabel = new FFuQtLabel(this);
  this->unitsMenu  = new FFuQtOptionMenu(this);

  this->modelingTolFrame = new FFuQtLabelFrame(this);
  this->modelingTolLabel = new FFuQtLabel(this);
  this->modelingTolField = new FFuQtIOField(this);

  this->gravitationFrame  = new FFuQtLabelFrame(this);
  this->gravitationVector = new FuiQt3DPoint(this,0,0,0,0,"g",false);

  this->initialVelFrame  = new FFuQtLabelFrame(this);
  this->initialVelVector = new FuiQt3DPoint(this,0,0,0,0,"v0",false);

  this->extFuncFileFrame  = new FFuQtLabelFrame(this);
  this->extFuncFileButton = new FFuQtToggleButton(this);
  this->extFuncFileField  = new FFuQtFileBrowseField(this);

  this->dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
