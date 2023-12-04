// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiMooringLine.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuDialogButtons.H"


Fmd_SOURCE_INIT(FUI_MOORINGLINE, FuiMooringLine, FFuModalDialog);


FuiMooringLine::FuiMooringLine()
{
  Fmd_CONSTRUCTOR_INIT(FuiMooringLine);
}


void FuiMooringLine::initWidgets()
{
  myNumField->setLabel("Number of elements in mooring line");
  myNumField->myField->setInputCheckMode(FFuIOField::INTEGERCHECK);

  myTypeLabel->setLabel("Element type");

  myLengthField->setLabel("Total length of mooring line");
  myLengthField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);

  myDialogButtons->setButtonLabel(FFuDialogButtons::LEFTBUTTON,"OK");
  myDialogButtons->setButtonLabel(FFuDialogButtons::RIGHTBUTTON,"Cancel");
}


void FuiMooringLine::placeWidgets(int width, int height)
{
  int rowHeight = 25;
  int border = this->getBorder();
  int yPos = height - myDialogButtons->getHeightHint();
  int xPos = myTypeLabel->getWidthHint() + 2*border;
  myDialogButtons->setEdgeGeometry(0, width, yPos, height);

  yPos = border;
  myNumField->setEdgeGeometry(border, width-border, yPos, yPos+rowHeight);

  yPos += rowHeight+border;
  myTypeLabel->setEdgeGeometry(border, xPos, yPos, yPos+rowHeight);
  myTypeMenu->setEdgeGeometry(xPos, width-border, yPos, yPos+rowHeight);

  yPos += rowHeight+border;
  myLengthField->setEdgeGeometry(border, width-border, yPos, yPos+rowHeight);
}


void FuiMooringLine::addElmType(const std::string& etype, bool clear)
{
  if (clear) myTypeMenu->clearOptions();
  myTypeMenu->addOption(etype.c_str());
}


int FuiMooringLine::getElmType()
{
  return myTypeMenu->getSelectedOption();
}


int FuiMooringLine::getNumSeg()
{
  return myNumField->myField->getInt();
}


double FuiMooringLine::getLength()
{
  return myLengthField->getValue();
}
