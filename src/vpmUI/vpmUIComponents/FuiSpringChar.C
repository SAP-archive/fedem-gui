// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiSpringChar.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuRadioButton.H"
#include "FFuLib/FFuLabelFrame.H"
#include "vpmDB/FmMathFuncBase.H"


void FuiSpringChar::initWidgets()
{
  mySpringFunctionFrame->setLabel("Spring function");

  mySpringFunctionField->setBehaviour(FuiQueryInputField::REF_NUMBER);
  mySpringFunctionField->setChangedCB(FFaDynCB1M(FuiSpringChar,this,
						 onQIFieldChanged,
						 FuiQueryInputField*));

  myFailureFrame->setLabel("Failure criterions");

  myDeflectionMaxToggle->setLabel("Max Deflection");
  myDeflectionMaxToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
						onBoolChanged,bool));
  myDeflectionMaxField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myDeflectionMaxField->setDoubleDisplayMode(FFuIOField::AUTO,8,1);
  myDeflectionMaxField->setAcceptedCB(FFaDynCB1M(FuiSpringChar,this,
						 onDoubleChanged,double));

  myDeflectionMinToggle->setLabel("Min Deflection");
  myDeflectionMinToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
						onBoolChanged,bool));
  myDeflectionMinField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myDeflectionMinField->setDoubleDisplayMode(FFuIOField::AUTO,8,1);
  myDeflectionMinField->setAcceptedCB(FFaDynCB1M(FuiSpringChar,this,
						 onDoubleChanged,double));

  myForceMaxToggle->setLabel("Max Force");
  myForceMaxToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
					   onBoolChanged,bool));
  myForceMaxField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myForceMaxField->setDoubleDisplayMode(FFuIOField::AUTO,8,1);
  myForceMaxField->setAcceptedCB(FFaDynCB1M(FuiSpringChar,this,
					    onDoubleChanged,double));

  myForceMinToggle->setLabel("Min Force");
  myForceMinToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
					   onBoolChanged,bool));
  myForceMinField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myForceMinField->setDoubleDisplayMode(FFuIOField::AUTO,8,1);
  myForceMinField->setAcceptedCB(FFaDynCB1M(FuiSpringChar,this,
					    onDoubleChanged,double));

  myYieldForceMaxToggle->setLabel("Max Yield Force");
  myYieldForceMaxToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
						onBoolChanged,bool));
  myYieldForceMaxEngineField->setBehaviour(FuiQueryInputField::REF_NUMBER);
  myYieldForceMaxEngineField->setChangedCB(FFaDynCB1M(FuiSpringChar,this,
						      onQIFieldChanged,
						      FuiQueryInputField*));

  myYieldFrame->setLabel("Yield criterion");

  myYieldForceMinToggle->setLabel("Min Yield Force");
  myYieldForceMinToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
						onBoolChanged,bool));
  myYieldForceMinEngineField->setBehaviour(FuiQueryInputField::REF_NUMBER);
  myYieldForceMinEngineField->setChangedCB(FFaDynCB1M(FuiSpringChar,this,
						      onQIFieldChanged,
						      FuiQueryInputField*));

  myYieldDeflectionMaxToggle->setLabel("Max Yield Deflection");
  myYieldDeflectionMaxToggle->setToggleCB(FFaDynCB1M(FuiSpringChar,this,
						     onBoolChanged,bool));
  myYieldDeflectionMaxField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myYieldDeflectionMaxField->setDoubleDisplayMode(FFuIOField::AUTO,8,1);
  myYieldDeflectionMaxField->setAcceptedCB(FFaDynCB1M(FuiSpringChar,this,
						      onDoubleChanged,double));
}


void FuiSpringChar::placeWidgets(int width, int height)
{
  int frameLeft = 0;
  int frameRight = width;

  int border = 6;
  int fieldHeight = 20;
  int fieldSpace = 10;

  if ( 17*fieldHeight/2 + 8*border > height ) {
    fieldSpace  = 0;
    fieldHeight = 2*(height - 8*border)/17;
  }
  else if ( 17*fieldHeight/2 + 7*fieldSpace + 8*border > height ) {
    fieldSpace  = (height - 8*border - 17*fieldHeight/2)/7;
  }

  int frame1Top = 0;
  int lineR1    = frame1Top + fieldSpace + fieldHeight   + border;
  int lineR2    = lineR1    + fieldSpace + fieldHeight;
  int frame1Btm = lineR2                 + fieldHeight/2 + border;
  int frame2Top = frame1Btm +                            + border;
  int line2     = frame2Top + fieldSpace + fieldHeight   + border;
  int line3     = line2     + fieldSpace + fieldHeight;
  int frame2Btm = line3                  + fieldHeight/2 + border;
  int frame3Top = frame2Btm +                            + border;
  int line4     = frame3Top + fieldSpace + fieldHeight   + border;
  int line5     = line4     + fieldSpace + fieldHeight;
  int line6     = line5     + fieldSpace + fieldHeight;
  int frame3Btm = line6                  + fieldHeight/2 + border;

  int v1 = border;
  int v2 = v1 + myDeflectionMaxToggle->getWidthHint();
  int v3 = width/2-border;
  int v4 = width/2+border;
  int v5 = v4 + myForceMaxToggle->getWidthHint();
  int v6 = width-border;
  int v7 = v1 + myYieldDeflectionMaxToggle->getWidthHint();

  mySpringFunctionFrame->setEdgeGeometry(frameLeft, frameRight, frame1Top, frame1Btm);
  myFailureFrame->setEdgeGeometry       (frameLeft, frameRight, frame2Top, frame2Btm);
  myYieldFrame->setEdgeGeometry         (frameLeft, frameRight, frame3Top, frame3Btm);

  mySpringFunctionField->setCenterYGeometry      (v1, lineR1, v6-v1, fieldHeight);
  mySpringFunctionDescription->setCenterYGeometry(v1, lineR2, v6-v1, fieldHeight);

  myDeflectionMaxToggle->setCenterYGeometry(v1, line2, v2-v1, fieldHeight);
  myDeflectionMinToggle->setCenterYGeometry(v1, line3, v2-v1, fieldHeight);
  myForceMaxToggle->setCenterYGeometry     (v4, line2, v5-v4, fieldHeight);
  myForceMinToggle->setCenterYGeometry     (v4, line3, v5-v4, fieldHeight);

  myDeflectionMaxField->setCenterYGeometry(v2, line2, v3-v2, fieldHeight);
  myDeflectionMinField->setCenterYGeometry(v2, line3, v3-v2, fieldHeight);
  myForceMaxField->setCenterYGeometry     (v5, line2, v6-v5, fieldHeight);
  myForceMinField->setCenterYGeometry     (v5, line3, v6-v5, fieldHeight);

  myYieldForceMaxToggle->     setCenterYGeometry(v1, line4, v7-v1, fieldHeight);
  myYieldForceMinToggle->     setCenterYGeometry(v1, line5, v7-v1, fieldHeight);
  myYieldDeflectionMaxToggle->setCenterYGeometry(v1, line6, v7-v1, fieldHeight);
  myYieldForceMaxEngineField->setCenterYGeometry(v7, line4, v6-v7, fieldHeight);
  myYieldForceMinEngineField->setCenterYGeometry(v7, line5, v6-v7, fieldHeight);
  myYieldDeflectionMaxField-> setCenterYGeometry(v7, line6, v6-v7-fieldHeight, fieldHeight);
}


void FuiSpringChar::setChangedCB(const FFaDynCB0& aDynCB)
{
  myChangedCB = aDynCB;
}


void FuiSpringChar::setValuesChangedCB(const FFaDynCB1<FuiSpringCharValues&>& aDynCB)
{
  myValuesChangedCB = aDynCB;
}


//
// Setting and getting :
//
//////////////////////////////////

void FuiSpringChar::setCBs(const FuiSpringCharValues& values)
{
  mySpringFunctionField->setButtonCB(values.springFunctionFieldButtonCB);
  myYieldForceMaxEngineField->setButtonCB(values.yieldForceFieldMaxButtonCB);
  myYieldForceMinEngineField->setButtonCB(values.yieldForceFieldMinButtonCB);
}


void FuiSpringChar::setValues(const FuiSpringCharValues& values)
{
  myDeflectionMaxToggle->setValue(values.useDeflectionMax);
  myDeflectionMinToggle->setValue(values.useDeflectionMin);
  myForceMaxToggle->setValue(values.useForceMax);
  myForceMinToggle->setValue(values.useForceMin);
  myYieldForceMaxToggle->setValue(values.useYieldForceMax);
  myYieldForceMinToggle->setValue(values.useYieldForceMin);
  myYieldDeflectionMaxToggle->setValue(values.useYieldDeflectionMax);

  if (IAmSensitive) {
    myDeflectionMaxField->setSensitivity(values.useDeflectionMax);
    myDeflectionMinField->setSensitivity(values.useDeflectionMin);
    myForceMaxField->setSensitivity(values.useForceMax);
    myForceMinField->setSensitivity(values.useForceMin);
    myYieldForceMaxEngineField->setSensitivity(values.useYieldForceMax);
    myYieldForceMinEngineField->setSensitivity(values.useYieldForceMin);
    myYieldDeflectionMaxField->setSensitivity(values.useYieldDeflectionMax);
  }

  myDeflectionMaxField->setValue(values.deflectionMax);
  myDeflectionMinField->setValue(values.deflectionMin);
  myForceMaxField->setValue(values.forceMax);
  myForceMinField->setValue(values.forceMin);
  myYieldDeflectionMaxField->setValue(values.yieldDeflectionMax);
  mySpringFunctionField->setValue(values.constantStiffness);
  mySpringFunctionField->setQuery(values.springFunctionQuery);
  mySpringFunctionField->setSelectedRef(values.springFunction);
  myYieldForceMaxEngineField->setValue(values.constantYieldForceMax);
  myYieldForceMaxEngineField->setQuery(values.yieldForceEngineQuery);
  myYieldForceMaxEngineField->setSelectedRef(values.yieldForceMaxEngine);
  myYieldForceMinEngineField->setValue(values.constantYieldForceMin);
  myYieldForceMinEngineField->setQuery(values.yieldForceEngineQuery);
  myYieldForceMinEngineField->setSelectedRef(values.yieldForceMinEngine);

  if (values.springFunction)
    switch (((FmMathFuncBase*)values.springFunction)->getFunctionUse()) {
    case FmMathFuncBase::SPR_TRA_STIFF:
      mySpringFunctionDescription->setLabel("Translational spring, Stiffness - deflection");
      break;
    case FmMathFuncBase::SPR_TRA_FORCE:
      mySpringFunctionDescription->setLabel("Translational spring, Force - deflection");
      break;
    case FmMathFuncBase::SPR_ROT_STIFF:
      mySpringFunctionDescription->setLabel("Rotational spring, Stiffness - rotation");
      break;
    case FmMathFuncBase::SPR_ROT_TORQUE:
      mySpringFunctionDescription->setLabel("Rotational spring, Torque - rotation");
      break;
    default:
      break;
    }
  else if (values.isTranslationalSpring)
    mySpringFunctionDescription->setLabel("Translation spring, Constant stiffness");
  else
    mySpringFunctionDescription->setLabel("Rotational spring, Constant stiffness");
}


void FuiSpringChar::getValues(FuiSpringCharValues& values)
{
  values.useDeflectionMax = myDeflectionMaxToggle->getValue();
  values.useDeflectionMin = myDeflectionMinToggle->getValue();
  values.useForceMax = myForceMaxToggle->getValue();
  values.useForceMin = myForceMinToggle->getValue();
  values.useYieldDeflectionMax = myYieldDeflectionMaxToggle->getValue();
  values.useYieldForceMax = myYieldForceMaxToggle->getValue();
  values.useYieldForceMin = myYieldForceMinToggle->getValue();

  values.deflectionMax = myDeflectionMaxField->getDouble();
  values.deflectionMin = myDeflectionMinField->getDouble();
  values.forceMax = myForceMaxField->getDouble();
  values.forceMin = myForceMinField->getDouble();
  values.yieldDeflectionMax = myYieldDeflectionMaxField->getDouble();
  values.constantStiffness = mySpringFunctionField->getValue();
  values.springFunction = mySpringFunctionField->getSelectedRef();
  values.constantYieldForceMax = myYieldForceMaxEngineField->getValue();
  values.yieldForceMaxEngine = myYieldForceMaxEngineField->getSelectedRef();
  values.constantYieldForceMin = myYieldForceMinEngineField->getValue();
  values.yieldForceMinEngine = myYieldForceMinEngineField->getSelectedRef();
}


//
// Internal callback forwarding :
//
//////////////////////////////////

void FuiSpringChar::onDoubleChanged(double)
{
  this->onValuesChanged();
}

void FuiSpringChar::onBoolChanged(bool)
{
  this->onValuesChanged();
}

void FuiSpringChar::onBoolChanged(int, bool)
{
  this->onValuesChanged();
}

void FuiSpringChar::onQIFieldChanged(FuiQueryInputField*)
{
  this->onValuesChanged();
}


void FuiSpringChar::onValuesChanged()
{
  FuiSpringCharValues values;
  this->getValues(values);
  myValuesChangedCB.invoke(values);
  myChangedCB.invoke();
}


//
// Setting up :
//
//////////////////////////////////

void FuiSpringChar::setSensitivity(bool isSensitive)
{
  mySpringFunctionField->setSensitivity(isSensitive);

  myDeflectionMaxToggle->setSensitivity(isSensitive);
  myDeflectionMaxField->setSensitivity(isSensitive && myDeflectionMaxToggle->getValue());

  myDeflectionMinToggle->setSensitivity(isSensitive);
  myDeflectionMinField->setSensitivity(isSensitive && myDeflectionMaxToggle->getValue());

  myForceMaxToggle->setSensitivity(isSensitive);
  myForceMaxField->setSensitivity(isSensitive && myDeflectionMaxToggle->getValue());

  myForceMinToggle->setSensitivity(isSensitive);
  myForceMinField->setSensitivity(isSensitive && myDeflectionMaxToggle->getValue());

  myYieldForceMaxToggle->setSensitivity(isSensitive);
  myYieldForceMaxEngineField->setSensitivity(isSensitive && myYieldForceMaxToggle->getValue());

  myYieldForceMinToggle->setSensitivity(isSensitive);
  myYieldForceMinEngineField->setSensitivity(isSensitive && myYieldForceMinToggle->getValue());

  myYieldDeflectionMaxToggle->setSensitivity(isSensitive);
  myYieldDeflectionMaxField->setSensitivity(isSensitive && myYieldDeflectionMaxToggle->getValue());

  IAmSensitive = isSensitive;
}
