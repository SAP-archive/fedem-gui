// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_COLOR_SELECTOR_H
#define FFU_COLOR_SELECTOR_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuColor.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuFrame;
class FFuScale;
class FFuLabel;
class FFuIOField;


class FFuColorSelector : virtual public FFuMultUIComponent
{
public:
  FFuColorSelector();
  virtual ~FFuColorSelector() {}

  const FFuColor& getInitialColor() const { return myInitialColor; }
  const FFuColor& getColor() const { return myColor; }
  void setInitialColor(const FFuColor& aColor);
  void setColor(const FFuColor& aColor, bool notify = true);
  void setColorChangedCB(const FFaDynCB1<FFuColor>& aDynCB);

protected:
  // widget placement - from MuitiUIComponent
  virtual void placeWidgets(int width, int height);

  // Initialisation to be called by UILib dep. subclass
  void init();

  virtual void updateSampleFrame() = 0;

protected:
  // components:
  FFuFrame*      myColorSampleFrame;
  FFuScale*      myRedScale;
  FFuScale*      myGreenScale;
  FFuScale*      myBlueScale;
  FFuLabel*      myRedLabel;
  FFuLabel*      myGreenLabel;
  FFuLabel*      myBlueLabel;
  FFuIOField*    myRedValue;
  FFuIOField*    myGreenValue;
  FFuIOField*    myBlueValue;

  FFaDynCB1<FFuColor> myColorChangedCB;

  FFuColor myColor;
  FFuColor myInitialColor;
  bool iAmColorInited;

private:
  void updateSlidersAndFields();

  void fieldRedValue(int red);
  void fieldGreenValue(int green);
  void fieldBlueValue(int blue);

  void sliderRedValue(int red);
  void sliderGreenValue(int green);
  void sliderBlueValue(int blue);
};

#endif
