// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtResultTabs.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"


FuiQtTriadResults::FuiQtTriadResults(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  myGlobalFrame = new FFuQtLabelFrame(this);
  myLocalFrame  = new FFuQtLabelFrame(this);

  for (FFuToggleButton*& toggle : myToggles)
    toggle = new FFuQtToggleButton(this);

  this->initWidgets();
}


FuiQtJointResults::FuiQtJointResults(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  myJointFrame  = new FFuQtLabelFrame(this);
  mySpringFrame = new FFuQtLabelFrame(this);
  myDamperFrame = new FFuQtLabelFrame(this);

  for (FFuToggleButton*& toggle : myToggles)
    toggle = new FFuQtToggleButton(this);

  this->initWidgets();
}
