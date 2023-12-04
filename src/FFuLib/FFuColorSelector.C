// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuFrame.H"
#include "FFuLib/FFuScale.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"

#include "FFuLib/FFuColorSelector.H"

enum colorComponent { RED = 0, GREEN = 1, BLUE = 2 };


/*!
  \class FFuColorSelector FFuColorSelector.H
  \brief Simple color selector

  Color is represented by RGB values, range 0-255.
  In the implementation color is represented as 8 bit integer for each channel.
  Total resolution is 24 bits (millions of colors).

  \warning There is no management of the allocated colors yet.
  The color table will run full!

  \author Jens Lien
*/

FFuColorSelector::FFuColorSelector()
{
  iAmColorInited = false;
  myInitialColor = myColor = {0,0,0};
}


void FFuColorSelector::init()
{
  myRedLabel->setLabel("Red");
  myRedScale->setDragCB(FFaDynCB1M(FFuColorSelector, this, sliderRedValue, int));
  myRedScale->setMinMax(0,255);
  myRedValue->setAcceptedCB(FFaDynCB1M(FFuColorSelector, this, fieldRedValue, int));
  myRedValue->setInputCheckMode(FFuIOField::INTEGERCHECK);
  myRedValue->setValue(0);

  myGreenLabel->setLabel("Green");
  myGreenScale->setDragCB(FFaDynCB1M(FFuColorSelector, this, sliderGreenValue, int));
  myGreenScale->setMinMax(0,255);
  myGreenValue->setAcceptedCB(FFaDynCB1M(FFuColorSelector, this, fieldGreenValue, int));
  myGreenValue->setInputCheckMode(FFuIOField::INTEGERCHECK);

  myBlueLabel->setLabel("Blue");
  myBlueScale->setDragCB(FFaDynCB1M(FFuColorSelector, this, sliderBlueValue, int));
  myBlueScale->setMinMax(0,255);
  myBlueValue->setAcceptedCB(FFaDynCB1M(FFuColorSelector, this, fieldBlueValue, int));
  myBlueValue->setInputCheckMode(FFuIOField::INTEGERCHECK);

  this->updateSlidersAndFields();
  this->updateSampleFrame();
}


void FFuColorSelector::placeWidgets(int width, int height)
{
  // establish sizes:
  int gWidth = this->getFontWidth("Green");
  int valWidth = 3 * this->getFontMaxWidth();

  // grid lines
  // vertical
  int glV1  = FFuMultUIComponent::getGridLinePos(width, 0,          FFuMultUIComponent::FROM_START);
  int glV2  = FFuMultUIComponent::getGridLinePos(width, gWidth,     FFuMultUIComponent::FROM_START);
  int glV3  = FFuMultUIComponent::getGridLinePos(width, glV2 + 10,  FFuMultUIComponent::FROM_START);

  int glV7  = FFuMultUIComponent::getGridLinePos(width, height,            FFuMultUIComponent::FROM_END);
  int glV6  = FFuMultUIComponent::getGridLinePos(width, (glV7 - 10),       FFuMultUIComponent::FROM_START);
  int glV5  = FFuMultUIComponent::getGridLinePos(width, (glV6 - valWidth), FFuMultUIComponent::FROM_START);
  int glV4  = FFuMultUIComponent::getGridLinePos(width, (glV5 - 10),       FFuMultUIComponent::FROM_START);

  int glV8  = FFuMultUIComponent::getGridLinePos(width, 0, FFuMultUIComponent::FROM_END);

  // horizontal:
  int glH1  = FFuMultUIComponent::getGridLinePos(height,    0);
  int glH2  = FFuMultUIComponent::getGridLinePos(height,  250);
  int glH3  = FFuMultUIComponent::getGridLinePos(height,  375);
  int glH4  = FFuMultUIComponent::getGridLinePos(height,  625);
  int glH5  = FFuMultUIComponent::getGridLinePos(height,  750);
  int glH6  = FFuMultUIComponent::getGridLinePos(height, 1000);

  myRedLabel->setEdgeGeometry( glV1, glV2, glH1, glH2);
  myRedScale->setEdgeGeometry( glV3, glV4, glH1, glH2);
  myRedValue->setEdgeGeometry( glV5, glV6, glH1, glH2);

  myGreenLabel->setEdgeGeometry( glV1, glV2, glH3, glH4);
  myGreenScale->setEdgeGeometry( glV3, glV4, glH3, glH4);
  myGreenValue->setEdgeGeometry( glV5, glV6, glH3, glH4);

  myBlueLabel->setEdgeGeometry( glV1, glV2, glH5, glH6);
  myBlueScale->setEdgeGeometry( glV3, glV4, glH5, glH6);
  myBlueValue->setEdgeGeometry( glV5, glV6, glH5, glH6);

  myColorSampleFrame->setEdgeGeometry( glV7, glV8, glH1, glH6);
}


/*!
  Set the initial color for the dialog. The color is reset to
  this if the user presses the cancel button.
  \sa setColor
*/

void FFuColorSelector::setInitialColor(const FFuColor& aColor)
{
  myInitialColor = aColor;
  iAmColorInited = true;
  this->setColor(aColor);
}

/*!
  Set the selected color for the dialog. The first time this
  is called, the color is also used as initial color.
  \param aColor the color to be set
  \param notify if true, the color change callback is called.
  \sa setInitialColor getColor setColorChangeCB
*/

void FFuColorSelector::setColor(const FFuColor& aColor, bool notify)
{
  if (!iAmColorInited)
  {
    myInitialColor = aColor;
    iAmColorInited = true;
  }

  myColor = aColor;

  this->updateSlidersAndFields();
  this->updateSampleFrame();

  if (notify)
    myColorChangedCB.invoke(myColor);
}


/*!
  Set the callback to be called when the color changes
*/
void FFuColorSelector::setColorChangedCB(const FFaDynCB1<FFuColor>& aDynCB)
{
  myColorChangedCB = aDynCB;
}


void FFuColorSelector::updateSlidersAndFields()
{
  myRedScale->  setValue(myColor[RED]);
  myRedValue->  setValue((int)myColor[RED]);
  myGreenScale->setValue(myColor[GREEN]);
  myGreenValue->setValue((int)myColor[GREEN]);
  myBlueScale-> setValue(myColor[BLUE]);
  myBlueValue-> setValue((int)myColor[BLUE]);
}


void FFuColorSelector::fieldRedValue(int red)
{
  if (red < 0)
    red = 0;
  else if (red > 255)
    red = 255;

  myRedScale->setValue(red);
  myRedValue->setValue(red);
  myColor[RED] = red;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}

void FFuColorSelector::fieldGreenValue(int green)
{
  if (green < 0)
    green = 0;
  else if (green > 255)
    green = 255;

  myGreenScale->setValue(green);
  myGreenValue->setValue(green);
  myColor[GREEN] = green;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}

void FFuColorSelector::fieldBlueValue(int blue)
{
  if (blue < 0)
    blue = 0;
  else if (blue > 255)
    blue = 255;

  myBlueScale->setValue(blue);
  myBlueValue->setValue(blue);
  myColor[BLUE] = blue;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}


void FFuColorSelector::sliderRedValue(int val)
{
  myRedValue->setValue(val);
  myColor[RED] = val;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}

void FFuColorSelector::sliderGreenValue(int val)
{
  myGreenValue->setValue(val);
  myColor[GREEN] = val;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}

void FFuColorSelector::sliderBlueValue(int val)
{
  myBlueValue->setValue(val);
  myColor[BLUE] = val;
  myColorChangedCB.invoke(myColor);
  this->updateSampleFrame();
}
