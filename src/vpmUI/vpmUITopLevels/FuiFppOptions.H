// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_FPP_OPTIONS_H
#define FUI_FPP_OPTIONS_H

#include "vpmUI/vpmUITopLevels/FuiTopLevelDialog.H"
#include "vpmUI/vpmUIComponents/FuiTimeInterval.H"

class FFuLabel;
class FFuLabelFrame;
class FFuToggleButton;
class FFuIOField;
class FFuOptionMenu;


class FuiFppOptions : public FuiTopLevelDialog
{
  Fmd_HEADER_INIT();

public:
  FuiFppOptions();
  virtual ~FuiFppOptions() {}

  // Static create method to use instead of constructor
  // Implementation in GUIlib-dependent implementation file
  static FuiFppOptions* create(int xpos = 100, int ypos  = 100,
			       int width= 100, int height= 100,
			       const char* title= "Strain Coat Recovery Summary Setup",
			       const char* name = "FuiFppOptions");

  void setTimeUIValues(const FuaTimeIntervalValues* timeValues);
  void setResetTimeCB(const FFaDynCB0& dynCB);

protected:
  virtual void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // CB's from widgets
  void onResetTimeClicked();
  void onAnalysisTypeChanged(int type);
  void onRainflowButtonToggled(bool toggle);

  // From datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FuiTimeInterval* time;

  FFuLabelFrame* rainflowFrame;
  FFuToggleButton* rainflowButton;
  FFuLabel* pvxGateLabel;
  FFuIOField* pvxGateField;
  FFuLabel* biaxGateLabel;
  FFuIOField* biaxGateField;

  FFuLabel* typeLabel;
  FFuOptionMenu* typeMenu;

  FFuLabelFrame* histFrame;
  FFuLabel* maxLabel;
  FFuIOField* maxField;
  FFuLabel* minLabel;
  FFuIOField* minField;
  FFuLabel* initRangeLabel;
  FFuLabel* nBinsLabel;
  FFuIOField* nBinsField;
  FFuLabel* maxElemsLabel;
  FFuIOField* maxElemsField;

private:
  FFaDynCB0 resetTimeCB;
  bool showNCodeFields;
};
/////////////////////////////////////////////////////////////////////////////

class FuaFppOptionsValues : public FFuaUIValues
{
public:
  FuaFppOptionsValues() {
    this->nElemsTogether = 0;
    this->performRainflow = true;
    this->histType = this->nBins = 0;
    this->pvxGate = this->biaxGate = 0.0;
    this->max = this->min = 0.0;
  }
  virtual ~FuaFppOptionsValues() {}

public:
  FuaTimeIntervalValues timeValues;

  int nElemsTogether;
  bool performRainflow;
  int histType;
  double pvxGate, biaxGate;
  double max, min;
  int nBins;
};
/////////////////////////////////////////////////////////////////////////////

#endif
