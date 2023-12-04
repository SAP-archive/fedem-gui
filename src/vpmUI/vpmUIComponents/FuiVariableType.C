// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiVariableType.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuOptionMenu.H"


void FuiVariableType::initWidgets()
{
  myFrame->setLabel("Prescribed quantity");
  myTypeMenu->addOption("Deflection");
  myTypeMenu->addOption("Velocity");
  myTypeMenu->addOption("Acceleration");
  myTypeMenu->setOptionSelectedCB(FFaDynCB1M(FuiVariableType,this,onMenuSelected,int));
}


void FuiVariableType::placeWidgets(int width, int height)
{
  int border      = 6;
  int frameLeft   = 0;
  int frameRight  = width;
  int frameTop    = 0;
  int frameBtm    = height;

  int fieldHeight = 20;
  int fieldSpace  = 10;

  while (3*(fieldHeight + fieldSpace)/2 > (height-border)) {
    if (3*fieldHeight/2 > (height-border)) {
      fieldHeight = 2*(height-border)/3;
      fieldSpace = 0;
      break;
    }
    else
      fieldSpace--;
  }

  int line1 = frameTop + fieldSpace + fieldHeight + border/2;
  int v1 = frameLeft  + border;
  int v2 = frameRight - border;

  myFrame->setEdgeGeometry(frameLeft,frameRight,frameTop,frameBtm);
  myTypeMenu->setCenterYGeometry(v1, line1, v2-v1, fieldHeight);
}


void FuiVariableType::setChangedCB(const FFaDynCB0& aDynCB)
{
  myChangedCB = aDynCB;
}


void FuiVariableType::onMenuSelected(int)
{
  myChangedCB.invoke();
}


void FuiVariableType::setValue(int selection)
{
  myTypeMenu->selectOption(selection);
}


int FuiVariableType::getValue() const
{
  return myTypeMenu->getSelectedOption();
}


void FuiVariableType::setSensitivity(bool isSensitive)
{
  myTypeMenu->setSensitivity(isSensitive);
}
