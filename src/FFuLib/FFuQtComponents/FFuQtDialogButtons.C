// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <cstring>

#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FFuQtDialogButtons::FFuQtDialogButtons(QWidget* parent, bool sep,
				       const char* leftButtonLabel,
				       const char* midButtonLabel,
				       const char* rightButtonLabel,
				       const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  leftButtonUp  = strcmp(leftButtonLabel ,"") != 0;
  midButtonUp   = strcmp(midButtonLabel  ,"") != 0;
  rightButtonUp = strcmp(rightButtonLabel,"") != 0;

  this->leftButton = new FFuQtPushButton(this);
  this->midButton = new FFuQtPushButton(this);
  this->rightButton = new FFuQtPushButton(this);

  if (sep) {
    FFuQtFrame* mySeparator;
    this->separator = mySeparator = new FFuQtFrame(this);
    mySeparator->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  }
  else
    this->separator = NULL;

  this->initWidgets(leftButtonLabel,midButtonLabel,rightButtonLabel);
}
