// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiCurveTimeRange.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuIOField.H"


//----------------------------------------------------------------------------

FuiCurveTimeRange::FuiCurveTimeRange()
{
  this->timeField = 0;
  this->maxField = 0;
  this->operMenu = 0;
}
//----------------------------------------------------------------------------

void FuiCurveTimeRange::initWidgets()
{
  this->timeField->setLabel("Time (range)");
  this->timeField->setAcceptedCB(FFaDynCB1M(FuiCurveTimeRange,this,
					   onDoubleChanged,double));
  this->maxField->setAcceptedCB(FFaDynCB1M(FuiCurveTimeRange,this,
					   onDoubleChanged,double));

  this->operMenu->addOption("None");
  this->operMenu->addOption("Min");
  this->operMenu->addOption("Max");
  this->operMenu->addOption("Absolute Max");
  this->operMenu->addOption("Mean");
  this->operMenu->addOption("RMS");
  this->operMenu->setOptionChangedCB(FFaDynCB1M(FuiCurveTimeRange,this,
						onOperSelected,std::string));
}
//----------------------------------------------------------------------------

void FuiCurveTimeRange::setUIValues(double tmin, double tmax, const std::string& selOper)
{
  this->timeField->setValue(tmin);
  this->maxField->setValue(tmax);

  if (!selOper.empty())
    this->operMenu->selectOption(selOper);

  this->maxField->setSensitivity(selOper != "None");

  this->placeWidgets(this->getWidth(),this->getHeight());
}
//-----------------------------------------------------------------------------

void FuiCurveTimeRange::getUIValues(double& tmin, double& tmax, std::string& selOper)
{
  tmin = this->timeField->getValue();
  tmax = this->maxField->getDouble();
  selOper = this->operMenu->getSelectedOptionStr();
}
//-----------------------------------------------------------------------------

void FuiCurveTimeRange::placeWidgets(int width, int height)
{
  int border = 5;
  int tWidth = this->timeField->getLabelWidth();
  int fWidth = (width-tWidth)/3-border;
  this->timeField->setEdgeGeometry(0, tWidth+fWidth, 0, height);
  this->maxField->setEdgeGeometry(tWidth+fWidth+border, tWidth+2*fWidth, 0, height);
  this->operMenu->setEdgeGeometry(tWidth+2*fWidth+border, width, 0, height);
}
//-----------------------------------------------------------------------------

void FuiCurveTimeRange::onDoubleChanged(double)
{
  this->changeCB.invoke();
}
//-----------------------------------------------------------------------------

void FuiCurveTimeRange::onOperSelected(std::string)
{
  this->changeCB.invoke();
}
//-----------------------------------------------------------------------------
