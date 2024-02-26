// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "vpmUI/vpmUIComponents/FuiSNCurveSelector.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFpLib/FFpFatigue/FFpSNCurveLib.H"


void FuiSNCurveSelector::initWidgets()
{
  this->stdLabel->setLabel("Standard");
  this->curveLabel->setLabel("S-N curve");

  this->stdTypeMenu->setOptionSelectedCB(FFaDynCB1M(FuiSNCurveSelector,this,
						    onStdValueChanged,int));
  this->curveTypeMenu->setOptionSelectedCB(FFaDynCB1M(FuiSNCurveSelector,this,
						      onCurveValueChanged,int));
}


void FuiSNCurveSelector::placeWidgets(int width, int height)
{
  int border = this->getBorder();

  int stdLeft = 0;
  int stdRight = stdLeft + this->stdLabel->getWidthHint();
  int stdTypeLeft = stdRight + border;
  int stdTypeWidth = width/2 - stdTypeLeft;

  int curveLeft = width/2 + border;
  int curveRight = curveLeft + this->curveLabel->getWidthHint();
  int curveTypeLeft = curveRight + border;
  int curveTypeWidth = width - curveTypeLeft;

  this->stdLabel->setEdgeGeometry(stdLeft, stdRight, 0, height);
  this->stdTypeMenu->setCenterYGeometry(stdTypeLeft, height/2, stdTypeWidth, height);
  this->curveLabel->setEdgeGeometry(curveLeft, curveRight, 0, height);
  this->curveTypeMenu->setCenterYGeometry(curveTypeLeft, height/2, curveTypeWidth, height);
}


void FuiSNCurveSelector::setSensitivity(bool isSensitive)
{
  stdTypeMenu->setSensitivity(isSensitive);
  curveTypeMenu->setSensitivity(isSensitive);
}


void FuiSNCurveSelector::onStdValueChanged(int)
{
  std::string selectedCurve = this->curveTypeMenu->getSelectedOptionStr();
  this->populateCurveMenu(this->stdTypeMenu->getSelectedOptionStr());

  if (!this->curveTypeMenu->selectOption(selectedCurve))
    this->curveTypeMenu->selectOption(0);

  this->dataChangedCB.invoke();
}


void FuiSNCurveSelector::onCurveValueChanged(int)
{
  this->dataChangedCB.invoke();
}


std::string FuiSNCurveSelector::getSelectedStd() const
{
  return this->stdTypeMenu->getSelectedOptionStr();
}


std::string FuiSNCurveSelector::getSelectedCurve() const
{
  return this->curveTypeMenu->getSelectedOptionStr();
}


void FuiSNCurveSelector::getValues(int& stdIdx, int& curveIdx)
{
  stdIdx   = this->stdTypeMenu->getSelectedOption();
  curveIdx = this->curveTypeMenu->getSelectedOption();
}


void FuiSNCurveSelector::setValues(int stdIdx, int curveIdx)
{
  int numStd = this->stdTypeMenu->getOptionCount();
  if (numStd < 1) return; // The S-N standard menu has not been populated yet

  if (stdIdx < 0 || stdIdx >= numStd)
  {
    if (FFpSNCurveLib::allocated())
      std::cout <<"Warning: SN-curve library has changed since you last saved your model"
                <<"\n         stdIdx = "<< stdIdx << std::endl;
    this->stdTypeMenu->selectOption(0);
  }
  else
    this->stdTypeMenu->selectOption(stdIdx);

  this->populateCurveMenu(this->stdTypeMenu->getSelectedOptionStr());

  if (curveIdx < 0 || curveIdx >= this->curveTypeMenu->getOptionCount())
  {
    if (FFpSNCurveLib::allocated())
      std::cout <<"Warning: SN-curve library has changed since you last saved your model"
                <<"\n         curveIdx = "<< curveIdx << std::endl;
    this->curveTypeMenu->selectOption(0);
  }
  else
    this->curveTypeMenu->selectOption(curveIdx);
}


void FuiSNCurveSelector::onPoppedUpFromMem()
{
  if (!FFpSNCurveLib::allocated()) return;

  std::vector<std::string> curveStds;
  FFpSNCurveLib::instance()->getCurveStds(curveStds);
  this->stdTypeMenu->setOptions(curveStds);

  this->populateCurveMenu(this->stdTypeMenu->getSelectedOptionStr());
}


void FuiSNCurveSelector::populateCurveMenu(const std::string& stdName)
{
  if (!FFpSNCurveLib::allocated()) return;

  std::vector<std::string> curves;
  FFpSNCurveLib::instance()->getCurveNames(curves,stdName);
  this->curveTypeMenu->setOptions(curves);
}
