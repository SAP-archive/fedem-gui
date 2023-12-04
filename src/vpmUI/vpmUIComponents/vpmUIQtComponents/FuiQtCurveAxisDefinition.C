// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtCurveAxisDefinition.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"


FuiQtCurveAxisDefinition::FuiQtCurveAxisDefinition(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->resultLabel = new FFuQtLabel(this);
  this->editButton = new FFuQtPushButton(this);
  this->operMenu = new FFuQtOptionMenu(this);

  this->FuiCurveAxisDefinition::initWidgets();
}


FuiQtCurveTimeRange::FuiQtCurveTimeRange(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->timeField = new FFuQtLabelField(this);
  this->maxField = new FFuQtIOField(this);
  this->operMenu = new FFuQtOptionMenu(this);

  this->FuiCurveTimeRange::initWidgets();
}
