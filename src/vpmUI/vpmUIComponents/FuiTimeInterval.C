// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiTimeInterval.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuToggleButton.H"


void FuiTimeInterval::setSensitivity(bool isSensitive)
{
  this->startField->setSensitivity(isSensitive);
  this->stopField->setSensitivity(isSensitive);
  this->incrField->setSensitivity(isSensitive && !this->allStepsToggle->getValue());

  this->allStepsToggle->setSensitivity(isSensitive);
  this->resetButton->setSensitivity(isSensitive);
}
//----------------------------------------------------------------------------

void FuiTimeInterval::initWidgets()
{
  this->allStepsToggle->setToggleCB(FFaDynCB1M(FuiTimeInterval,this,onAllStepsToggled,bool));
  this->resetButton->setActivateCB(FFaDynCB0M(FuiTimeInterval,this,onResetButtonActivated));

  this->startField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->startField->setDoubleDisplayMode(FFuIOField::AUTO,12,1);
  this->stopField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->stopField->setDoubleDisplayMode(FFuIOField::AUTO,12,1);
  this->incrField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->incrField->setDoubleDisplayMode(FFuIOField::AUTO,12,1);

  this->timeIntervalFrame->setLabel("Time Interval");
  this->startLabel->setLabel("Start");
  this->stopLabel->setLabel("Stop");
  this->incrLabel->setLabel("Increment");

  this->allStepsToggle->setLabel("Use all time steps");
  this->resetButton->setLabel("Reset");
}
//----------------------------------------------------------------------------

void FuiTimeInterval::placeWidgets(int width,int height)
{
  int hBorder = this->sepH = getGridLinePos(height,35);
  int fieldHeight = this->widgetH = getGridLinePos(height,130);
  int vBorder = getGridLinePos(width,20);

  int h1 = fieldHeight;
  int h2 = h1 + fieldHeight;
  int h3 = h2 + hBorder;
  int h4 = h3 + fieldHeight;
  int h5 = h4 + hBorder;
  int h6 = h5 + fieldHeight;
  int h7 = h6 + hBorder;
  int h8 = h7 + fieldHeight;
  int h9 = h8 + hBorder;
  int h10 = h9 + fieldHeight;

  int v1 = vBorder;
  int v11 = vBorder + this->incrLabel->getWidthHint();
  int v12 = v11 + vBorder;
  int v4 = width - vBorder - this->resetButton->getWidthHint();
  int v41 = width - 2*vBorder;
  int v5 = width - vBorder;

  this->timeIntervalFrame->setEdgeGeometry(0,width,0,height);
  this->startLabel->setEdgeGeometry(v1,v11,h1,h2);
  this->startField->setEdgeGeometry(v12,v41,h1,h2);
  this->stopLabel->setEdgeGeometry(v1,v11,h3,h4);
  this->stopField->setEdgeGeometry(v12,v41,h3,h4);
  this->incrLabel->setEdgeGeometry(v1,v11,h5,h6);
  this->incrField->setEdgeGeometry(v12,v41,h5,h6);
  this->allStepsToggle->setEdgeGeometry(v12,v5,h7,h8);
  this->resetButton->setEdgeGeometry(v4,v41,h9,h10);
}
//-----------------------------------------------------------------------------

void FuiTimeInterval::setUIValues(const FuaTimeIntervalValues* timeValues)
{
  this->startField->setValue(timeValues->start);
  this->stopField->setValue(timeValues->stop);
  if (!timeValues->dontTouchIncr)
    this->incrField->setValue(timeValues->incr);
  this->incrField->setSensitivity(!timeValues->allSteps);
  this->allStepsToggle->setValue(timeValues->allSteps);
}
//-----------------------------------------------------------------------------

void FuiTimeInterval::getUIValues(FuaTimeIntervalValues* timeValues)
{
  timeValues->start = this->startField->getDouble();
  timeValues->stop = this->stopField->getDouble();
  timeValues->incr = this->incrField->getDouble();
  timeValues->allSteps = this->allStepsToggle->getValue();
}
//-----------------------------------------------------------------------------

void FuiTimeInterval::onAllStepsToggled(bool toggle)
{
  this->incrField->setSensitivity(!toggle);
}
//-----------------------------------------------------------------------------
