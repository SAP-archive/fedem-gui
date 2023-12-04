// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtGageOptions.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtTimeInterval.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"

//----------------------------------------------------------------------------

FuiGageOptions* FuiGageOptions::create(int xpos, int ypos,
				       int width, int height, 
				       const char* title,
				       const char* name)
{
  return new FuiQtGageOptions(0,xpos,ypos,width,height,title,name);
}
//----------------------------------------------------------------------------

FuiQtGageOptions::FuiQtGageOptions(QWidget* parent, int xpos, int ypos,
				   int width, int height,
				   const char* title,
				   const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->time = new FuiQtTimeInterval(this); 
  this->autoDacExportToggle = new FFuQtToggleButton(this);
  this->dacSampleRateField = new FFuQtLabelField(this);
  this->rainflowToggle = new FFuQtToggleButton(this);
  this->binSizeField = new FFuQtLabelField(this);
  this->importRosFileButton = new FFuQtPushButton(this);
  this->dialogButtons = new FFuQtDialogButtons(this);

  this->FuiGageOptions::initWidgets();
}
//----------------------------------------------------------------------------

FuiQtGageOptions::~FuiQtGageOptions()
{
}
//----------------------------------------------------------------------------
