// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiSimpleLoad.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "FFuLib/FFuLabelFrame.H"


void FuiSimpleLoad::initWidgets()
{
  myFrame->setLabel("Load magnitude");
  myEngineField->setToolTip("Sets the magnitude as a constant value, or\n"
    "as a function (with the constant value added).");
  myEngineField->useAddedConstValue = true; // shows const value as added to function
  myEngineField->setBehaviour(FuiQueryInputField::REF_NUMBER);
  myEngineField->setChangedCB(FFaDynCB1M(FuiSimpleLoad,this,onQIFieldChanged,
					 FuiQueryInputField*));
}


void FuiSimpleLoad::setLabel(const char* text)
{
  myFrame->setLabel(text);
}


void FuiSimpleLoad::placeWidgets(int width, int height)
{
  int border      = 6;
  int frameLeft   = 0;
  int frameRight  = width;
  int frameTop    = 0;
  int frameBtm    = height;

  int fieldHeight = 20;
  int fieldSpace  = 10;

  while (3*(fieldHeight + fieldSpace)/2 > (height-border)) {
    if (3*fieldHeight/2 > (height-border)) {
      fieldHeight = 2*(height-border)/3;
      fieldSpace = 0;
      break;
    }
    else
      fieldSpace--;
  }

  int line1 = frameTop + fieldSpace + fieldHeight + border/2;
  int v1 = frameLeft  + border;
  int v2 = frameRight - border;

  myFrame->setEdgeGeometry(frameLeft,frameRight,frameTop,frameBtm);

  myEngineField->setCenterYGeometry(v1, line1, v2-v1, fieldHeight);
}


void FuiSimpleLoad::setChangedCB(const FFaDynCB0& aDynCB)
{
  myChangedCB = aDynCB;
}


void FuiSimpleLoad::setValuesChangedCB(const FFaDynCB1<FuiSimpleLoadValues&>& aDynCB)
{
  myValuesChangedCB = aDynCB;
}


void FuiSimpleLoad::setCBs(const FuiSimpleLoadValues& values)
{
  myEngineField->setButtonCB(values.myEngineQIFieldButtonCB);
}


void FuiSimpleLoad::setValues(const FuiSimpleLoadValues& values)
{
  myEngineField->setValue(values.constValue);
  myEngineField->setQuery(values.engineQuery);
  myEngineField->setSelectedRef(values.selectedEngine);
}


void FuiSimpleLoad::getValues(FuiSimpleLoadValues& values)
{
  values.isConstant = myEngineField->isAConstant();
  values.constValue = myEngineField->getValue();
  values.selectedEngine = myEngineField->getSelectedRef();
}


void FuiSimpleLoad::onQIFieldChanged(FuiQueryInputField*)
{
  this->onValuesChanged();
}


void FuiSimpleLoad::onValuesChanged()
{
  FuiSimpleLoadValues values;
  this->getValues(values);
  myValuesChangedCB.invoke(values);
  myChangedCB.invoke();
}


void FuiSimpleLoad::setSensitivity(bool isSensitive)
{
  myEngineField->setSensitivity(isSensitive);
}
