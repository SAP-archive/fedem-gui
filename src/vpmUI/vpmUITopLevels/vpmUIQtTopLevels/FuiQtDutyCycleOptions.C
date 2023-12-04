// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtDutyCycleOptions.H"

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtTable.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiDutyCycleOptions* FuiDutyCycleOptions::create(int xpos, int ypos, int width, int height,
						 const char* title, const char* name)
{
  return new FuiQtDutyCycleOptions(0, xpos, ypos, width, height, title, name);
}

FuiQtDutyCycleOptions::FuiQtDutyCycleOptions(QWidget* parent, int xpos, int ypos, int width, int height,
					     const char* title, const char* name)
  : FFuQtTopLevelShell(parent, xpos, ypos, width, height, title, name)
{
  this->eventFrame = new FFuQtLabelFrame(this);
  this->linkFrame = new FFuQtLabelFrame(this);
  this->eventTable = new FFuQtTable(this);
  this->linkTable  = new FFuQtTable(this);
  this->addEventButton = new FFuQtPushButton(this);
  this->delEventButton = new FFuQtPushButton(this);
  this->checkAllButton = new FFuQtPushButton(this);
  this->checkNoneButton = new FFuQtPushButton(this);
  this->equivUnitScaleField = new FFuQtIOField(this);
  this->equivUnitField = new FFuQtIOField(this);
  this->equivUnitLabel = new FFuQtLabel(this);
  this->equivUnitScaleLabel = new FFuQtLabel(this);
  this->dialogButtons = new FFuQtDialogButtons(this);

  this->FuiDutyCycleOptions::initWidgets();
}

void
FuiQtDutyCycleOptions::setSensitivity(bool isSensitive)
{
  this->FuiDutyCycleOptions::setSensitivity(isSensitive);
}
