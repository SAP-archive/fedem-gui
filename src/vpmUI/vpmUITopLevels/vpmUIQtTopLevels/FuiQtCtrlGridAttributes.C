// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtCtrlGridAttributes.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"


FuiQtCtrlGridAttributes::FuiQtCtrlGridAttributes(QWidget* parent)
  : FFuQtTopLevelShell(parent,100,100,250,300,"Grid and Snap")
{
  myGridToggleButton = new FFuQtToggleButton(this);
  myGridSizeLabel = new FFuQtLabel(this);
  myGXLabel = new FFuQtLabel(this);
  myGYLabel = new FFuQtLabel(this);
  myGXField = new FFuQtIOField(this);
  myGYField = new FFuQtIOField(this);

  FFuQtFrame* qtFrame;
  myGridSnapSeparator = qtFrame = new FFuQtFrame(this);
  qtFrame->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  qtFrame->setLineWidth(2);

  mySnapDistLabel = new FFuQtLabel(this);
  mySnapToggleButton = new FFuQtToggleButton(this);
  mySXLabel = new FFuQtLabel(this);
  mySYLabel = new FFuQtLabel(this);
  mySXField = new FFuQtIOField(this);
  mySYField = new FFuQtIOField(this);

  myCloseSeparator = qtFrame = new FFuQtFrame(this);
  qtFrame->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  qtFrame->setLineWidth(2);

  myCloseButton = new FFuQtPushButton(this);

  this->initWidgets();
}
