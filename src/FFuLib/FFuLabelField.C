// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"


FFuLabelField::FFuLabelField()
{
  myLabelWidth = 60;
  myRelativeLabelWidth = 300;
  myLabelMargin = 3;
  myResizePolicy = FFU_AUTO;
}

/*!
 * \TODO Refactor and change the name of variable string to something else.
 */
void FFuLabelField::setLabel(const char* str)
{
  myLabel->setLabel(str);
  this->placeWidgets(this->getWidth(), this->getHeight());
}

void FFuLabelField::setValue(double value)
{
  myField->setValue(value);
}

void FFuLabelField::setValue(const std::string& value)
{
  myField->setValue(value.c_str());
}

double FFuLabelField::getValue()
{
  return myField->getDouble();
}

std::string FFuLabelField::getText()
{
  return std::string(myField->getValue());
}


// Field Accept :

void FFuLabelField::setAcceptedCB(const FFaDynCB1<double>& aDynCB)
{
  myField->setAcceptedCB(aDynCB);
}


// Label geometry :

int FFuLabelField::getLabelWidth()
{
  return myLabel->getWidth();
}

void FFuLabelField::setLabelWidth(int width)
{
  myLabelWidth = width;
  myLabel->setWidth(width);
  myResizePolicy = FFU_FIXED;
  this->placeWidgets(this->getWidth(), this->getHeight());
}

void FFuLabelField::setRelativeLabelWidth(int percent)
{
  myRelativeLabelWidth = 10*percent;
  myResizePolicy = FFU_RELATIVE;
  this->placeWidgets(this->getWidth(), this->getHeight());
}

void FFuLabelField::setLabelMargin(int margin)
{
  myLabelMargin = margin;
  this->placeWidgets(this->getWidth(), this->getHeight());
}


// To prevent editing :

void FFuLabelField::setSensitivity(bool makeSensitive)
{
  myField->setSensitivity(makeSensitive);
}

bool FFuLabelField::getSensitivity()
{
  return myField->getSensitivity();
}


// Manage geometry :

void FFuLabelField::placeWidgets(int width, int height)
{
  int hintLabelWidth = this->myLabel->getWidthHint();
  int relLabelWidth = getGridLinePos(width,myRelativeLabelWidth);

  switch (myResizePolicy)
    {
    case FFuLabelField::FFU_AUTO:
      myLabel->setEdgeGeometry(0,hintLabelWidth + 2*myLabelMargin, 0, height);
      myField->setEdgeGeometry(hintLabelWidth + 3*myLabelMargin, width, 0, height);
      break;
    case FFuLabelField::FFU_FIXED:
      myLabel->setEdgeGeometry(0,myLabelWidth+2*myLabelMargin,0,height);
      myField->setEdgeGeometry(myLabelWidth+3*myLabelMargin,width,0,height);
      break;
    case FFuLabelField::FFU_RELATIVE:
      myLabel->setEdgeGeometry(0,relLabelWidth + 2*myLabelMargin,0,height);
      myField->setEdgeGeometry(relLabelWidth + 3*myLabelMargin,width,0,height);
      break;
    }
}


/*!
  Sets same tool tip to both label and field.
*/

void FFuLabelField::setToolTip(const char* tip)
{
  myLabel->setToolTip(tip);
  myField->setToolTip(tip);
}
