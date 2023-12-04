// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_TIME_INTERVAL_H
#define FUI_TIME_INTERVAL_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabel;
class FFuLabelFrame;
class FFuIOField;
class FFuToggleButton;
class FFuPushButton;


struct FuaTimeIntervalValues
{
  FuaTimeIntervalValues() {
    start = stop = incr = 0.0;
    allSteps = dontTouchIncr = false;
  }

  double start, stop, incr;
  bool allSteps, dontTouchIncr;
};


class FuiTimeInterval : virtual public FFuMultUIComponent
{
public:
  FuiTimeInterval() { this->widgetH = this->sepH=0; }
  virtual ~FuiTimeInterval() {}

  void setUIValues(const FuaTimeIntervalValues* timeValues);
  void getUIValues(FuaTimeIntervalValues* timeValues);

  virtual void setSensitivity(bool isSensitive);

  void setResetCB(const FFaDynCB0& dynCB) { this->resetCB = dynCB; }

  int getWidgetH() const { return this->widgetH; }
  int getSepH() const { return this->sepH; }

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width,int height);

  void onAllStepsToggled(bool toggle);
  void onResetButtonActivated() { this->resetCB.invoke(); }

protected:
  FFuLabelFrame* timeIntervalFrame;
  FFuLabel* startLabel;
  FFuIOField* startField;
  FFuLabel* stopLabel;
  FFuIOField* stopField;
  FFuLabel* incrLabel;
  FFuIOField* incrField;

  FFuToggleButton* allStepsToggle;
  FFuPushButton* resetButton;

private:
  FFaDynCB0 resetCB;
  int sepH,widgetH;
};

#endif
