// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_TRIAD_DOF_H
#define FUI_TRIAD_DOF_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSimpleLoad.H"

class FuiTriadDOFValues;
class FuiMotionType;
class FuiVariableType;
class FFuLabelField;
class FFuToggleButton;


class FuiTriadDOF : public virtual FFuMultUIComponent
{
public:
  FuiTriadDOF();
  virtual ~FuiTriadDOF() {}

  void setChangedCB(const FFaDynCB0& aDynCB);

  void getValues(FuiTriadDOFValues& values) const;
  void setValues(const FuiTriadDOFValues& values,
                 bool canSwitchMotionType = true,
                 bool isSensitive = true);

  FuiMotionType*   motionType;
  FuiVariableType* variableType;
  FuiSimpleLoad*   loadField;
  FFuLabelField*   initialVel;
  FFuToggleButton* freqToggle;

  enum {
    FREE = 0,
    FIXED = 1,
    PRESCRIBED = 2,
    FREE_DYNAMICS = 3,
    PRESCRIBED_DISP = 6,
    PRESCRIBED_VEL = 7,
    PRESCRIBED_ACC = 8
  };

protected:
  virtual void placeWidgets(int width, int height);

  void initWidgets();
};


class FuiTriadDOFValues
{
public:
  int myMotionType;
  bool freqDomain;
  double myInitVel;
  FuiSimpleLoadValues myLoadVals;

  FuiTriadDOFValues() {
    myMotionType = -1;
    freqDomain = false;
    myInitVel = 0.0;
  }
};

#endif
