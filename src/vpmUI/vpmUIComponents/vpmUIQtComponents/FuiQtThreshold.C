// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtThreshold.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"


FuiQtThreshold::FuiQtThreshold(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  myToggle = new FFuQtToggleButton(this);
  myDescription = new FFuQtLabelField(this);
  myValueField = new FFuQtLabelField(this);
  myMinField = new FFuQtLabelField(this);
  mySkipField = new FFuQtLabelField(this);
  mySeverityLabel = new FFuQtLabel(this);
  mySeverityMenu = new FFuQtOptionMenu(this);

  this->initWidgets();
}
