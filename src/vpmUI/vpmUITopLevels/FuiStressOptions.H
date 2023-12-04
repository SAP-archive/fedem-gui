// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_STRESS_OPTIONS_H
#define FUI_STRESS_OPTIONS_H

#include "vpmUI/vpmUITopLevels/FuiTopLevelDialog.H"
#include "vpmUI/vpmUIComponents/FuiTimeInterval.H"

class FFuLabelFrame;
class FFuLabelField;
class FFuLabel;
class FFuToggleButton;
class FFuFileBrowseField;


class FuiStressOptions : public FuiTopLevelDialog
{
  Fmd_HEADER_INIT();

public:
  FuiStressOptions();
  virtual ~FuiStressOptions() {}

  // Static create method to use instead of constructor
  // Implementation in GUIlib-dependent implementation file
  static FuiStressOptions* create(int xpos = 100, int ypos  = 100,
				  int width= 100, int height= 100,
				  const char* title= "Stress Recovery Setup",
				  const char* name = "FuiStressOptions");

  void setTimeUIValues(const FuaTimeIntervalValues* timeValues);
  void setResetTimeCB(const FFaDynCB0& dynCB);

protected:
  virtual void initWidgets();

private:
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);
  virtual void placeWidgets(int width, int height);

  void setVTFLabel(int);
  void onResetTimeClicked();
  void onAutoVTFToggled(bool);
  void onAutoVTFFileChanged(const std::string&, int);

protected:
  FuiTimeInterval* time;

  FFuLabelFrame*   outputFrame;
  FFuToggleButton* deformationToggle;
  FFuToggleButton* stressResToggle;
  FFuToggleButton* stressToggle[5];
  FFuToggleButton* strainToggle[5];

  FFuToggleButton*    autoVTFToggle;
  FFuFileBrowseField* autoVTFField;

  FFuLabel*      fringeLabel;
  FFuLabelField* minFringeField;
  FFuLabelField* maxFringeField;

private:
  FFaDynCB0 resetTimeCB;
  bool      showVTFfield;
};
////////////////////////////////////////////////////////////////////////////////

class FuaStressOptionsValues : public FFuaUIValues
{
public:
  FuaStressOptionsValues() {
    this->deformationOutput = this->stressResOutput = 0;
    for (int i = 0; i < 5; i++)
      this->stressOutput[i] = this->strainOutput[i] = 0;
    this->autoVTFSwitch = false;
    this->autoVTFFileType = 0;
    this->vtfFringeMin = this->vtfFringeMax = 0.0;
    this->isSensitive = true;
  }

  virtual ~FuaStressOptionsValues() {}

public:
  FuaTimeIntervalValues timeValues;

  bool deformationOutput;
  bool stressResOutput;
  bool stressOutput[5];
  bool strainOutput[5];

  char autoVTFSwitch;
  int  autoVTFFileType;

  std::string autoVTFFileName;
  std::string modelFilePath;

  double vtfFringeMin, vtfFringeMax;

  bool isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
