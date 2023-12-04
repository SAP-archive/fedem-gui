// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiThreshold.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuOptionMenu.H"


FuiThreshold::FuiThreshold()
{
  myToggle = NULL;
  myDescription = myValueField = myMinField = mySkipField = NULL;
  mySeverityLabel = NULL;
  mySeverityMenu = NULL;
}


void FuiThreshold::initWidgets()
{
  myToggle->setLabel("Enable threshold");
  myDescription->setLabel("Description");
  myValueField->setLabel("Threshold value");
  myValueField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myMinField->setLabel("Min interval [<font face='Symbol'>m</font>s]");
  myMinField->myField->setInputCheckMode(FFuIOField::INTEGERCHECK);
  mySkipField->setLabel("Skip interval [<font face='Symbol'>m</font>s]");
  mySkipField->myField->setInputCheckMode(FFuIOField::INTEGERCHECK);
  mySeverityLabel->setLabel("Severity");
  mySeverityMenu->addOption("Low");
  mySeverityMenu->addOption("Medium");
  mySeverityMenu->addOption("High");
}


void FuiThreshold::placeWidgets(int width, int)
{
  int border = 5;
  int fieldHeight = myToggle->getHeightHint();
  int offset = fieldHeight + border;
  int shortw = 260;

  int v1 = border;
  int v2 = width - border;
  int v3 = width > shortw ? width/2 - border : v2;
  int v4 = width > shortw ? v3 + 2*border : v1;
  int v5 = border + mySeverityLabel->getWidthHint();
  int v6 = v5 + border;

  int h = 0;
  myToggle->setEdgeGeometry(v1, v2, h, h+fieldHeight); h += offset;
  myDescription->setEdgeGeometry(v1, v2, h, h+fieldHeight); h += offset;
  myValueField->setEdgeGeometry(v1, v2, h, h+fieldHeight); h += offset;
  myMinField->setEdgeGeometry(v1, v3, h, h+fieldHeight); if (width <= shortw) h += offset;
  mySkipField->setEdgeGeometry(v4, v2, h, h+fieldHeight); h += offset;
  mySeverityLabel->setEdgeGeometry(v1, v5, h, h+fieldHeight);
  mySeverityMenu->setEdgeGeometry(v6, v2, h, h+fieldHeight);
}


void FuiThreshold::setToggleCB(const FFaDynCB1<bool>& cb)
{
  myToggle->setToggleCB(cb);
}


void FuiThreshold::setValueChangedCB(const FFaDynCB1<char*>& cb)
{
  myDescription->myField->setAcceptedCB(cb);
  myValueField->myField->setAcceptedCB(cb);
  myMinField->myField->setAcceptedCB(cb);
  mySkipField->myField->setAcceptedCB(cb);
}


void FuiThreshold::setSelectionChangedCB(const FFaDynCB1<int>& cb)
{
  mySeverityMenu->setOptionSelectedCB(cb);
}


void FuiThreshold::setValues(const ThresholdValues& vals)
{
  myToggle->setValue(vals.active);
  myDescription->setValue(vals.description);
  myDescription->setSensitivity(vals.active);
  myValueField->setValue(vals.threshold);
  myValueField->setSensitivity(vals.active);
  myMinField->myField->setValue(vals.min);
  myMinField->setSensitivity(vals.active);
  mySkipField->myField->setValue(vals.skip);
  mySkipField->setSensitivity(vals.active);
  mySeverityMenu->selectOption(vals.severity);
  mySeverityMenu->setSensitivity(vals.active);
}


void FuiThreshold::getValues(ThresholdValues& vals) const
{
  vals.active = myToggle->getValue();
  vals.description = myDescription->getText();
  vals.threshold = myValueField->getValue();
  vals.min = myMinField->myField->getInt();
  vals.skip = mySkipField->myField->getInt();
  vals.severity = mySeverityMenu->getSelectedOption();
}
