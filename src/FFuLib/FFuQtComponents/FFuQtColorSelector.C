// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QColor>

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtScale.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtColorSelector.H"


FFuQtColorSelector::FFuQtColorSelector(QWidget* parent,
                                       int xpos, int ypos,
                                       int width, int height,
                                       const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  FFuQtScale* qtRedScale;
  FFuQtScale* qtBlueScale;
  FFuQtScale* qtGreenScale;

  myColorSampleFrame = qtColorSampleFrame = new FFuQtFrame(this);
  myRedScale         = qtRedScale         = new FFuQtScale(this);
  myGreenScale       = qtGreenScale       = new FFuQtScale(this);
  myBlueScale        = qtBlueScale        = new FFuQtScale(this);
  myRedLabel         = new FFuQtLabel(this);
  myGreenLabel       = new FFuQtLabel(this);
  myBlueLabel        = new FFuQtLabel(this);

  myRedValue         = new FFuQtIOField(this);
  myGreenValue       = new FFuQtIOField(this);
  myBlueValue        = new FFuQtIOField(this);

  qtColorSampleFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  qtColorSampleFrame->setLineWidth(2);

  qtRedScale->setOrientation(Qt::Horizontal);
  qtBlueScale->setOrientation(Qt::Horizontal);
  qtGreenScale->setOrientation(Qt::Horizontal);

  this->FFuColorSelector::init();
}


void FFuQtColorSelector::updateSampleFrame()
{
  char background[64];
  sprintf(background, "background-color: rgb(%d,%d,%d)", myColor[0], myColor[1], myColor[2]);
  qtColorSampleFrame->setStyleSheet(background);
}
