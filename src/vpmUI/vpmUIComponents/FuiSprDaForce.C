// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiSprDaForce.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuToggleButton.H"


void FuiSprDaForce::initWidgets()
{
  myScaleLabel->setLabel("Scale");
  myIsDefDamperToggle->setLabel("Use deformational velocity");
  this->updateSprDaLabels();

  myFunctionField->setBehaviour(FuiQueryInputField::REF_NUMBER);
  myFunctionField->setChangedCB(FFaDynCB1M(FuiSprDaForce,this,onQIFieldChanged,
					   FuiQueryInputField*));

  myScaleField->setBehaviour(FuiQueryInputField::REF_NONE);
  myScaleField->setChangedCB(FFaDynCB1M(FuiSprDaForce,this,onQIFieldChanged,
					 FuiQueryInputField*));

  myIsDefDamperToggle->setToggleCB(FFaDynCB1M(FuiSprDaForce,this,
					      onBoolChanged,bool));
  myFrame->toBack();
}


void FuiSprDaForce::setAsSpring(bool yesOrNo)
{
  if (yesOrNo == IAmSpringUI) return;

  IAmSpringUI = yesOrNo;

  this->updateSprDaLabels();
}


void FuiSprDaForce::updateSprDaLabels()
{
  if (IAmSpringUI) {
    myFrame->setLabel("Spring properties");
    myFunctionLabel->setLabel("Stiffness");
    myFunctionField->setToolTip("Specify a constant spring stiffness,\n"
				"or select a stiffness/force-deflection function\n"
				"or an Advanced spring characteristics property");
    myScaleField->setToolTip("Optional scaling function for the spring stiffness and force.\n"
			     "Note: This should not be a function of the spring deflection or length");
    myIsDefDamperToggle->popDown();
  }
  else {
    myFrame->setLabel("Damper properties");
    myFunctionLabel->setLabel("Damping coefficient");
    myFunctionField->setToolTip("Specify a constant damping coefficient,\n"
				"or select a coefficient/force-velocity function");
    myScaleField->setToolTip("Optional scaling function for the damping coefficient and force.\n"
			     "Note: This should not be a function of the damper velocity or length");
    myIsDefDamperToggle->popUp();
  }
}


void FuiSprDaForce::placeWidgets(int width, int height)
{
  int border      = 6;
  int fieldHeight = 20;
  int fieldSpace  = 10;

  int n2 = IAmSpringUI ? 5 : 7;
  while (n2*(fieldHeight + fieldSpace)/2 > height-border)
    if (n2*fieldHeight/2 > height-border) {
      fieldHeight = 2*(height-border)/n2;
      fieldSpace = 0;
      break;
    }
    else
      fieldSpace--;

  int line1 = fieldSpace + fieldHeight + border/2;
  int line2 = line1 + fieldSpace + fieldHeight;
  int line3 = line2 + fieldSpace + fieldHeight;

  int v1 = border;
  int v2 = v1 + myFunctionLabel->getWidthHint() + border;
  int v3 = v1 + myScaleLabel->getWidthHint() + border;
  int v4 = width - border;

  myFrame->setEdgeGeometry(0, width, 0, height);

  myFunctionLabel->setCenterYGeometry(v1, line1, v2-v1, fieldHeight);
  myFunctionField->setCenterYGeometry(v2, line1, v4-v2, fieldHeight);

  myScaleLabel->setCenterYGeometry(v1, line2, v3-v1, fieldHeight);
  myScaleField->setCenterYGeometry(v3, line2, v4-v3, fieldHeight);

  myIsDefDamperToggle->setCenterYGeometry(v1, line3, v4-v1, fieldHeight);
}


void FuiSprDaForce::setChangedCB(const FFaDynCB0& aDynCB)
{
  myChangedCB = aDynCB;
}


void FuiSprDaForce::setValuesChangedCB(const FFaDynCB1<FuiSprDaForceValues&>& aDynCB)
{
  myValuesChangedCB = aDynCB;
}


//
// Setting and Getting :
//
//////////////////////////////////

void FuiSprDaForce::setCBs(const FuiSprDaForceValues& values)
{
  myFunctionField->setButtonCB(values.myFunctionQIFieldButtonCB);
  myScaleField->setButtonCB(values.myEngineQIFieldButtonCB);
}


void FuiSprDaForce::buildDynamicWidgets(const FuiSprDaForceValues& values)
{
  if (IAmSpringUI) return;

  if (values.showDefDamper) {
    myIsDefDamperToggle->popUp();
    myIsDefDamperToggle->setSensitivity(IAmSensitive && values.showDefDamper > 0);
  }
  else
    myIsDefDamperToggle->popDown();
}


void FuiSprDaForce::setValues(const FuiSprDaForceValues& values)
{
  myFunctionField->setValue(values.constFunction);
  myFunctionField->setQuery(values.functionQuery);
  myFunctionField->setSelectedRef(values.selectedFunction);

  myScaleField->setQuery(values.engineQuery);
  myScaleField->setSelectedRef(values.selectedScaleEngine);

  myIsDefDamperToggle->setValue(values.isDefDamper);

  buildDynamicWidgets(values);
}


void FuiSprDaForce::getValues(FuiSprDaForceValues& values)
{
  values.isConstant = myFunctionField->isAConstant();
  values.constFunction = myFunctionField->getValue();
  values.selectedFunction = myFunctionField->getSelectedRef();

  values.selectedScaleEngine = myScaleField->getSelectedRef();

  values.isDefDamper = myIsDefDamperToggle->getValue();
}


//
// Internal Callback Forwarding :
//
//////////////////////////////////

void FuiSprDaForce::onQIFieldChanged(FuiQueryInputField*)
{
  this->onBoolChanged(true);
}


void FuiSprDaForce::onBoolChanged(bool)
{
  FuiSprDaForceValues values;
  this->getValues(values);
  myValuesChangedCB.invoke(values);

  myChangedCB.invoke();
}


//
// Setting Up :
//
//////////////////////////////////

void FuiSprDaForce::setSensitivity(bool isSensitive)
{
  myFunctionField->setSensitivity(isSensitive);
  myScaleField->setSensitivity(isSensitive);
  myIsDefDamperToggle->setSensitivity(isSensitive);

  IAmSensitive = isSensitive;
}
