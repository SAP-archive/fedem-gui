// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtTimeInterval.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FuiQtFppOptions.H"

//----------------------------------------------------------------------------

FuiFppOptions* FuiFppOptions::create(int xpos,int ypos,
				     int width, int height,
				     const char* title,
				     const char* name)
{
  return new FuiQtFppOptions(0,xpos,ypos,width,height,title,name);
}
//----------------------------------------------------------------------------

FuiQtFppOptions::FuiQtFppOptions(QWidget* parent,int xpos,int ypos,
				 int width, int height,
				 const char* title,
				 const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->time = new FuiQtTimeInterval(this);

  this->maxElemsLabel = new FFuQtLabel(this);
  this->maxElemsField = new FFuQtIOField(this);

  this->biaxGateLabel = new FFuQtLabel(this);
  this->biaxGateField = new FFuQtIOField(this);

  this->rainflowFrame = new FFuQtLabelFrame(this);
  this->rainflowButton = new FFuQtToggleButton(this);

  this->typeLabel = new FFuQtLabel(this);
  this->typeMenu = new FFuQtOptionMenu(this);

  this->pvxGateLabel = new FFuQtLabel(this);
  this->pvxGateField = new FFuQtIOField(this);

  this->histFrame = new FFuQtLabelFrame(this);

  this->nBinsLabel = new FFuQtLabel(this);
  this->nBinsField = new FFuQtIOField(this);

  this->initRangeLabel = new FFuQtLabel(this);
  this->maxLabel = new FFuQtLabel(this);
  this->maxField = new FFuQtIOField(this);
  this->minLabel = new FFuQtLabel(this);
  this->minField = new FFuQtIOField(this);

  this->dialogButtons = new FFuQtDialogButtons(this);

  this->FuiFppOptions::initWidgets();
}
//----------------------------------------------------------------------------

FuiQtFppOptions::~FuiQtFppOptions()
{
}
//----------------------------------------------------------------------------
