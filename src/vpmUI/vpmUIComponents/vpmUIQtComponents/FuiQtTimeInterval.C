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
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"

//----------------------------------------------------------------------------


FuiQtTimeInterval::FuiQtTimeInterval(QWidget* parent,const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->timeIntervalFrame = new FFuQtLabelFrame(this);
  this->startLabel = new FFuQtLabel(this);
  this->startField = new FFuQtIOField(this);
  //this->startUnits = new FFuQtLabel(this);
  this->stopLabel = new FFuQtLabel(this);
  this->stopField = new FFuQtIOField(this); 
  //this->stopUnits = new FFuQtLabel(this);
  this->incrLabel = new FFuQtLabel(this);
  this->incrField = new FFuQtIOField(this);  
  //this->incrUnits = new FFuQtLabel(this);
  
  this->allStepsToggle = new FFuQtToggleButton(this);
  this->resetButton = new FFuQtPushButton(this);

  //base class component initiation
  this->FuiTimeInterval::initWidgets();
}
//----------------------------------------------------------------------------

FuiQtTimeInterval::~FuiQtTimeInterval()
{
}
//----------------------------------------------------------------------------
