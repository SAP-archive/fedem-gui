// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtStressOptions.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtTimeInterval.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"

//----------------------------------------------------------------------------

FuiStressOptions* FuiStressOptions::create(int xpos, int ypos,
					   int width, int height,
					   const char* title,
					   const char* name)
{
  return new FuiQtStressOptions(0,xpos,ypos,width,height,title,name);
}
//----------------------------------------------------------------------------

FuiQtStressOptions::FuiQtStressOptions (QWidget* parent, int xpos, int ypos,
					int width, int height,
					const char* title,
				 	const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->time = new FuiQtTimeInterval(this);
  this->outputFrame = new FFuQtLabelFrame(this);
  this->deformationToggle = new FFuQtToggleButton(this);
  this->stressResToggle = new FFuQtToggleButton(this);
  for (int i = 0; i < 5; i++) {
    this->stressToggle[i] = new FFuQtToggleButton(this);
    this->strainToggle[i] = new FFuQtToggleButton(this);
  }
  this->autoVTFToggle  = new FFuQtToggleButton(this);
  this->autoVTFField   = new FFuQtFileBrowseField(this);
  this->fringeLabel    = new FFuQtLabel(this);
  this->minFringeField = new FFuQtLabelField(this);
  this->maxFringeField = new FFuQtLabelField(this);
  this->dialogButtons  = new FFuQtDialogButtons(this);

  this->FuiStressOptions::initWidgets();
}
//----------------------------------------------------------------------------

FuiQtStressOptions::~FuiQtStressOptions()
{
}
//----------------------------------------------------------------------------
