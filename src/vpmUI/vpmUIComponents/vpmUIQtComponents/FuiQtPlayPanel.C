// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtScale.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtPlayPanel.H"


FuiQtPlayPanel::FuiQtPlayPanel(QWidget* parent,
                               int xpos, int ypos,
                               int width, int height,
                               const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  FFuQtFrame* qtMainFrame;
  FFuQtLabel* qtFastLabel;
  FFuQtScale* qtSpeedScale;

  // Construct the QtWidgets :

  this->myMainFrame  = qtMainFrame  = new FFuQtFrame(this);

  this->myContinousToggleButton     = new FFuQtToggleButton(this);
  this->myAllFramesToggle           = new FFuQtToggleButton(this);
  this->myPingPongToggleButton      = new FFuQtToggleButton(this);

  this->myFastLabel  = qtFastLabel  = new FFuQtLabel(this);
  this->mySlowLabel                 = new FFuQtLabel(this);
  this->mySpeedScale = qtSpeedScale = new FFuQtScale(this);

  this->myRealTimeButton    = new   FFuQtPushButton(this);

  this->myStopPushButton    = new   FFuQtPushButton(this);
  this->myToLastPushButton  = new   FFuQtPushButton(this);
  this->myStepFwdPushButton = new   FFuQtPushButton(this);
  this->myStepRwdPushButton = new   FFuQtPushButton(this);
  this->myToFirstPushButton = new   FFuQtPushButton(this);
  this->myPlayPushButton    = new   FFuQtPushButton(this);
  this->myPausePushButton   = new   FFuQtPushButton(this);
  this->myPlayRwdPushButton = new   FFuQtPushButton(this);
  this->myCloseAnimPushButton = new FFuQtPushButton(this);

  // Initialise Qt spesific things:

  qtMainFrame->setFrameStyle(QFrame::Panel | QFrame::Raised);
  qtMainFrame->setLineWidth(1);
  qtFastLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  qtSpeedScale->setOrientation(Qt::Horizontal);
  qtSpeedScale->setMinimumSize(5,10);

  this->FuiPlayPanel::init();
}
