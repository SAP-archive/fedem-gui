// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_GAGE_OPTIONS_H
#define FUI_GAGE_OPTIONS_H

#include "vpmUI/vpmUITopLevels/FuiTopLevelDialog.H"
#include "vpmUI/vpmUIComponents/FuiTimeInterval.H"

class FFuLabelField;
class FFuToggleButton;
class FFuPushButton;


class FuiGageOptions : public FuiTopLevelDialog
{
  Fmd_HEADER_INIT();

public:
  FuiGageOptions();
  virtual ~FuiGageOptions() {}

  static FuiGageOptions* create(int xpos = 100, int ypos  = 100,
				int width= 100, int height= 100,
				const char* title= "Strain Rosette Recovery Setup",
				const char* name = "FuiGageOptions");

  void setTimeUIValues(const FuaTimeIntervalValues* timeValues);
  void setResetTimeCB(const FFaDynCB0& dynCB);
  void setImportRosetteFileCB(const FFaDynCB0& dynCB);

  virtual void setSensitivity(bool sens);

protected:
  virtual void initWidgets();

private:
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);
  virtual void placeWidgets(int width, int height);

  void onResetTimeClicked();
  void onAutoDacExportToggled(bool value);
  void onRainflowToggled(bool value);

protected:
  FuiTimeInterval* time;

  FFuToggleButton* autoDacExportToggle;
  FFuLabelField*   dacSampleRateField;
  FFuPushButton*   importRosFileButton;
  FFuToggleButton* rainflowToggle;
  FFuLabelField*   binSizeField;

private:
  FFaDynCB0 resetTimeCB;
  FFaDynCB0 importRosFileCB;
};

/////////////////////////////////////////////////////////////////////////////

class FuaGageOptionsValues : public FFuaUIValues
{
public:
  FuaGageOptionsValues() {
    this->autoDacSwitch = false;
    this->dacSampleRate = 0.0;
    this->rainflowSwitch = false;
    this->binSize = 0.0;
    this->isSensitive = true;
  }
  virtual ~FuaGageOptionsValues() {}

public:
  FuaTimeIntervalValues timeValues;

  bool   autoDacSwitch;
  double dacSampleRate;
  bool   rainflowSwitch;
  double binSize;

  bool isSensitive;
};
/////////////////////////////////////////////////////////////////////////////

#endif
