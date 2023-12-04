// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_THRESHOLD_H
#define FUI_THRESHOLD_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include <string>

class FFuToggleButton;
class FFuLabelField;
class FFuLabel;
class FFuOptionMenu;


struct ThresholdValues
{
  bool   active;
  double threshold;
  int    min, skip, severity;
  std::string description;

  ThresholdValues() { active = false; threshold = 0.0; min = skip = severity = 0; }
};


class FuiThreshold : public virtual FFuMultUIComponent
{
public:
  FuiThreshold();
  virtual ~FuiThreshold() {}

  void setToggleCB(const FFaDynCB1<bool>& cb);
  void setValueChangedCB(const FFaDynCB1<char*>& cb);
  void setSelectionChangedCB(const FFaDynCB1<int>& cb);

  void setValues(const ThresholdValues& vals);
  void getValues(ThresholdValues& vals) const;

protected:
  void initWidgets();

  virtual void placeWidgets(int width, int);

  FFuToggleButton* myToggle;
  FFuLabelField*   myDescription;
  FFuLabelField*   myValueField;
  FFuLabelField*   myMinField;
  FFuLabelField*   mySkipField;
  FFuLabel*        mySeverityLabel;
  FFuOptionMenu*   mySeverityMenu;
};

#endif
