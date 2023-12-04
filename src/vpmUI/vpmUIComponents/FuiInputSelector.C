// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiInputSelector.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuOptionMenu.H"


FuiInputSelector::FuiInputSelector()
{
  IAmSensitive = true;
  IAmShowingDofList = false;
  IAmShowingVariableList = false;
}


void FuiInputSelector::initWidgets()
{
  myLabelFrame->setLabel("Argument");

  myObjectSelector->setRefSelectedCB(FFaDynCB1M(FuiInputSelector,this,
						onIntChanged,int));
  myObjectSelector->setBehaviour(FuiQueryInputField::REF_NONE);
  myObjectSelector->setButtonMeaning(FuiQueryInputField::SELECT);

  myDofLabel->setLabel("DOF:");
  myDofSelector->setOptionSelectedCB(FFaDynCB1M(FuiInputSelector,this,
                                                onIntChanged,int));
  myVariableLabel->setLabel("Var:");
  myVariableSelector->setOptionSelectedCB(FFaDynCB1M(FuiInputSelector,this,
                                                     onIntChanged,int));
}


void FuiInputSelector::placeWidgets(int width, int height)
{
  int relativeOptMHeight = 333;

  int textHeight   = myDofLabel->getHeightHint();
  int vBorder      = getGridLinePos(height, 15);
  int hBorder      = 5;

  int o1 = getGridLinePos(height - 8*vBorder - textHeight, relativeOptMHeight);
  int o2 = myDofSelector->getHeightHint();
  int optionMenuHeight = o1 < o2 ? o1 : o2;
  int dofTextWidth = myDofLabel->getWidthHint();
  int varTextWidth = myVariableLabel->getWidthHint();
  int maxTextWidth = dofTextWidth > varTextWidth ? dofTextWidth : varTextWidth;

  int v1 = hBorder;
  int v2 = hBorder + maxTextWidth + hBorder;
  int v6 = width - hBorder;

  int h1 = 2*vBorder + textHeight;
  int h2 = h1 + optionMenuHeight;
  int h3 = h2 + 2*vBorder;
  int h4 = h3 + optionMenuHeight;
  int h5 = h4 + 2*vBorder;
  int h6 = h5 + optionMenuHeight;

  myLabelFrame->      setEdgeGeometry( 0,width,  0, height);
  myObjectSelector->  setEdgeGeometry(v1,   v6, h1,     h2);
  myDofLabel->        setEdgeGeometry(v1,   v2, h3,     h4);
  myDofSelector->     setEdgeGeometry(v2,   v6, h3,     h4);
  myVariableLabel->   setEdgeGeometry(v1,   v2, h5,     h6);
  myVariableSelector->setEdgeGeometry(v2,   v6, h5,     h6);
}


void FuiInputSelector::setValuesChangedCB(const FFaDynCB1<FuiInputSelectorValues&>& aDynCB)
{
  myValuesChangedCB = aDynCB;
}

void FuiInputSelector::setSetDBValuesCB(const FFaDynCB1<FuiInputSelectorValues&>& aDynCB)
{
  mySetDBValuesCB = aDynCB;
}

void FuiInputSelector::setPickCB(const FFaDynCB0& aDynCB)
{
  myObjectSelector->setButtonCB(aDynCB);
}


void FuiInputSelector::setValues(const FuiInputSelectorValues& values)
{
  // Sensor selector :

  myObjectSelector->setQuery(values.objectSelectorQuery);
  myObjectSelector->setSelectedRef(values.selectedObject);

  // DOF Selector :

  IAmShowingDofList = values.showDofList;
  myDofSelector->setOptions(values.dofList);
  myDofSelector->selectOption(values.selectedDofIdx);

  // Variable Selector :

  IAmShowingVariableList = values.showVariableList;
  myVariableSelector->setOptions(values.variableList);
  myVariableSelector->selectOption(values.selectedVariableIdx);

  this->setDBValues();
  this->updateSensitivity();
}

void FuiInputSelector::getValues(FuiInputSelectorValues& values)
{
  values.selectedObject = myObjectSelector->getSelectedRef();

  if (IAmShowingDofList)
    values.selectedDofIdx = myDofSelector->getSelectedOption();
  else
    values.selectedDofIdx = -1;

  if (IAmShowingVariableList)
    values.selectedVariableIdx = myVariableSelector->getSelectedOption();
  else
    values.selectedVariableIdx = -1;
}


void FuiInputSelector::setLabel(const std::string& label)
{
  myLabelFrame->setLabel(label.c_str());
}


void FuiInputSelector::onIntChanged(int)
{
  this->onValuesChanged();
}

void FuiInputSelector::onValuesChanged()
{
  FuiInputSelectorValues values;
  this->getValues(values);
  myValuesChangedCB.invoke(values);
}


void FuiInputSelector::setDBValues()
{
  FuiInputSelectorValues values;
  this->getValues(values);
  mySetDBValuesCB.invoke(values);
}


void FuiInputSelector::setSensitivity(bool isSensitive)
{
  IAmSensitive = isSensitive;
  this->updateSensitivity();
}

void FuiInputSelector::updateSensitivity()
{
  myObjectSelector->  setSensitivity(IAmSensitive);
  myDofSelector->     setSensitivity(IAmSensitive && IAmShowingDofList);
  myVariableSelector->setSensitivity(IAmSensitive && IAmShowingVariableList);
}
