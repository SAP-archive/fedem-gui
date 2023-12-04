// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiFppOptions.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuOptionMenu.H"


enum {
  STRESS,
  STRAIN
};

Fmd_SOURCE_INIT(FUI_FPPOPTIONS,FuiFppOptions,FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiFppOptions::FuiFppOptions()
{
  Fmd_CONSTRUCTOR_INIT(FuiFppOptions);

  this->showNCodeFields = false;
}
//----------------------------------------------------------------------------

void FuiFppOptions::initWidgets()
{
  this->time->setResetCB(FFaDynCB0M(FuiFppOptions,this,onResetTimeClicked));

  this->pvxGateField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->pvxGateField->setDoubleDisplayMode(FFuIOField::AUTO,6,1);
  this->biaxGateField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->biaxGateField->setDoubleDisplayMode(FFuIOField::AUTO,6,1);

  this->maxField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->maxField->setDoubleDisplayMode(FFuIOField::AUTO,6,1);
  this->minField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->minField->setDoubleDisplayMode(FFuIOField::AUTO,6,1);

  this->nBinsField->setInputCheckMode(FFuIOField::INTEGERCHECK);
  this->maxElemsField->setInputCheckMode(FFuIOField::INTEGERCHECK);

  this->typeLabel->setLabel("Analysis type");
  this->typeMenu->addOption("Signed abs max stress (S-N)", STRESS);
  this->typeMenu->addOption("Signed abs max strain (E-N)", STRAIN);
  this->typeMenu->setOptionSelectedCB(FFaDynCB1M(FuiFppOptions,this,
						 onAnalysisTypeChanged,int));

  this->rainflowFrame->setLabel("Rainflow/Fatigue Analysis");
  this->rainflowButton->setValue(true);
  this->rainflowButton->setLabel("Perform rainflow and fatigue analysis");
  this->rainflowButton->setToggleCB(FFaDynCB1M(FuiFppOptions,this,
					       onRainflowButtonToggled,bool));

  this->biaxGateLabel->setLabel("Biaxiality stress threshold");
  this->biaxGateLabel->setToolTip("Principal stresses below this value are ignored"
				  "\nin the biaxiality calculations");

  this->onAnalysisTypeChanged(STRESS);

  this->initRangeLabel->setLabel("Initial range");

  this->histFrame->setLabel("Histogram");
  this->maxLabel->setLabel("Max");
  this->minLabel->setLabel("Min");
  this->nBinsLabel->setLabel("Number of bins");
  this->maxElemsLabel->setLabel("Max number of elements processed together");

  this->FuiTopLevelDialog::initWidgets();
}
//----------------------------------------------------------------------------

void FuiFppOptions::placeWidgets(int width, int height)
{
  int border = this->getBorder();
  int timeTop = border;
  int timeBottom = 315*height/1000;
  this->time->setEdgeGeometry(border, width - border, timeTop, timeBottom);

  int sep = this->time->getSepH();
  int widgetHeight = this->time->getWidgetH();
  int frameFontHeight = this->rainflowFrame->getFontHeigth();

  int fieldLeft = 0;
  int fieldWidth = 0;

  // Widget Y positions
  int maxElemsCenter = timeBottom + border + widgetHeight/2;
  int biaxCenter = maxElemsCenter + widgetHeight + border;
  int rainflowFrameTop = biaxCenter + widgetHeight;
  int rainflowFrameBottom = height - this->getDialogButtonsHeightHint();
  int rainflowCenter = rainflowFrameTop + frameFontHeight + widgetHeight/2;
  int typeCenter = rainflowCenter + widgetHeight;
  int peakValleyCenter = typeCenter + widgetHeight + border;
  int histframeTop = peakValleyCenter + widgetHeight;
  int histframeBottom = rainflowFrameBottom - 3*sep/2;

  int histframeHeight = histframeBottom - histframeTop - border - frameFontHeight;
  int heightForEach = 4*histframeHeight/15;

  int noBinsCenter = histframeTop + frameFontHeight + heightForEach/2;
  int initRangeCenter = noBinsCenter + heightForEach;
  int maxCenter = initRangeCenter + 3*heightForEach/4;
  int minCenter = maxCenter + heightForEach;

  // Frames
  this->rainflowFrame->setEdgeGeometry(border, width - border,
				       rainflowFrameTop, rainflowFrameBottom);
  this->histFrame->setEdgeGeometry(border + 3*sep/2, width - border - 3*sep/2,
				   histframeTop, histframeBottom);

  // Max elements
  this->maxElemsLabel->setCenterYGeometryWidthHint(border, maxElemsCenter, widgetHeight);
  fieldLeft = this->maxElemsLabel->getXRightPos() + border;
  fieldWidth = width - fieldLeft - border;
  this->maxElemsField->setCenterYGeometry(fieldLeft, maxElemsCenter,
					  fieldWidth, widgetHeight);

  // Biaxiality gate
  this->biaxGateLabel->setCenterYGeometryWidthHint(border, biaxCenter, widgetHeight);
  fieldLeft = this->biaxGateLabel->getXRightPos() + 4*border;
  fieldWidth = width - fieldLeft - border;
  this->biaxGateField->setCenterYGeometry(fieldLeft, biaxCenter,
					  fieldWidth, widgetHeight);

  // Rainflow toggle
  this->rainflowButton->setCenterYGeometryWidthHint(2*border, rainflowCenter, widgetHeight);

  // Type and pvx
  this->typeLabel->setCenterYGeometryWidthHint(2*border, typeCenter, widgetHeight);
  this->pvxGateLabel->setCenterYGeometryWidthHint(2*border, peakValleyCenter, widgetHeight);

  fieldWidth = this->typeMenu->getWidthHint();
  fieldLeft = width - sep - 5*border/2 - fieldWidth;

  this->typeMenu->setCenterYGeometry(fieldLeft, typeCenter,
				     fieldWidth, widgetHeight);

  if (fieldLeft < this->pvxGateLabel->getXRightPos() + border) {
    fieldLeft = this->pvxGateLabel->getXRightPos() + border;
    fieldWidth = width - fieldLeft - 5*border/2 - sep;
  }

  this->pvxGateField->setCenterYGeometry(fieldLeft, peakValleyCenter,
					 fieldWidth, widgetHeight);

  // Number of bins
  this->nBinsLabel->setCenterYGeometryWidthHint(2*border + 3*sep/2, noBinsCenter, widgetHeight);
  fieldLeft = this->nBinsLabel->getXRightPos() + 2*border;
  fieldWidth = width - 3*border - fieldLeft;
  this->nBinsField->setCenterYGeometry(fieldLeft, noBinsCenter,
				       fieldWidth, widgetHeight);

  // Initial range label
  this->initRangeLabel->setCenterYGeometryWidthHint(2*border + 3*sep/2, initRangeCenter, widgetHeight);

  // Max/Min
  this->maxLabel->setCenterYGeometryWidthHint(4*border, maxCenter, widgetHeight);
  this->minLabel->setCenterYGeometryWidthHint(4*border, minCenter, widgetHeight);
  this->maxField->setCenterYGeometry(fieldLeft, maxCenter, fieldWidth, widgetHeight);
  this->minField->setCenterYGeometry(fieldLeft, minCenter, fieldWidth, widgetHeight);

  // the histogram fields are relevant for nCode only
  if (this->showNCodeFields) {
    this->histFrame->popUp();
    this->nBinsLabel->popUp();
    this->nBinsField->popUp();
    this->initRangeLabel->popUp();
    this->maxLabel->popUp();
    this->maxField->popUp();
    this->minLabel->popUp();
    this->minField->popUp();
  }
  else {
    this->histFrame->popDown();
    this->nBinsLabel->popDown();
    this->nBinsField->popDown();
    this->initRangeLabel->popDown();
    this->maxLabel->popDown();
    this->maxField->popDown();
    this->minLabel->popDown();
    this->minField->popDown();
  }

  this->FuiTopLevelDialog::placeWidgets(width,height);
}
//-----------------------------------------------------------------------------

void FuiFppOptions::setTimeUIValues(const FuaTimeIntervalValues* timeValues)
{
  this->time->setUIValues(timeValues);
}
//-----------------------------------------------------------------------------

void FuiFppOptions::setResetTimeCB(const FFaDynCB0& dynCB)
{
  this->resetTimeCB = dynCB;
}
//-----------------------------------------------------------------------------

void FuiFppOptions::onResetTimeClicked()
{
  this->resetTimeCB.invoke();
}
//----------------------------------------------------------------------------

void FuiFppOptions::onRainflowButtonToggled(bool toggle)
{
  this->typeMenu->setSensitivity(toggle);
  this->pvxGateField->setSensitivity(toggle);
  this->maxField->setSensitivity(toggle);
  this->minField->setSensitivity(toggle);
  this->nBinsField->setSensitivity(toggle);
}
//----------------------------------------------------------------------------

void FuiFppOptions::onAnalysisTypeChanged(int type)
{
  std::string atype(type == STRESS ? "Stress" : "Strain");
  this->pvxGateLabel->setLabel(atype + " range threshold");
  this->pvxGateLabel->setToolTip((atype + " ranges below this value are ignored"
				  "\nin the rainflow analysis (peak valley extraction)").c_str());
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiFppOptions::createValuesObject()
{
  return new FuaFppOptionsValues();
}
//----------------------------------------------------------------------------

void FuiFppOptions::setUIValues(const FFuaUIValues* values)
{
  FuaFppOptionsValues* fppValues = (FuaFppOptionsValues*) values;

  this->time->setUIValues(&fppValues->timeValues);
  this->maxElemsField->setValue(fppValues->nElemsTogether);
  this->rainflowButton->setValue(fppValues->performRainflow);
  this->pvxGateField->setValue(fppValues->pvxGate);
  this->biaxGateField->setValue(fppValues->biaxGate);

  if ((this->showNCodeFields = fppValues->histType >= 0)) {
    this->typeMenu->selectOption(fppValues->histType);
    this->onAnalysisTypeChanged(fppValues->histType);
    this->maxField->setValue(fppValues->max);
    this->minField->setValue(fppValues->min);
    this->nBinsField->setValue(fppValues->nBins);
  }
  else
    this->typeMenu->selectOption(STRESS);

  this->onRainflowButtonToggled(fppValues->performRainflow);
}
//-----------------------------------------------------------------------------

void FuiFppOptions::getUIValues(FFuaUIValues* values)
{
  FuaFppOptionsValues* fppValues = (FuaFppOptionsValues*) values;

  this->time->getUIValues(&fppValues->timeValues);
  fppValues->nElemsTogether = this->maxElemsField->getInt();
  fppValues->performRainflow = this->rainflowButton->getValue();
  fppValues->pvxGate = this->pvxGateField->getDouble();
  fppValues->biaxGate = this->biaxGateField->getDouble();
  if (this->showNCodeFields) {
    fppValues->histType = this->typeMenu->getSelectedOption();
    fppValues->max = this->maxField->getDouble();
    fppValues->min = this->minField->getDouble();
    fppValues->nBins = this->nBinsField->getInt();
  }
  else
    fppValues->histType = -1;
}
//-----------------------------------------------------------------------------
