// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_SPRING_CHAR_H
#define FUI_SPRING_CHAR_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabel;
class FFuLabelFrame;
class FFuIOField;
class FFuToggleButton;
class FFuRadioButton;
class FFuaQueryBase;
class FuiQueryInputField;
class FuiQueryInputFieldValues;
class FuiSpringCharValues;
class FmModelMemberBase;


class FuiSpringChar : public virtual FFuMultUIComponent
{
public:
  FuiSpringChar() { IAmSensitive = true; }
  virtual ~FuiSpringChar() {}

  virtual void setSensitivity(bool isSensitive);

  // Callbacks :

  void setChangedCB(const FFaDynCB0& aDynCB);
  void setValuesChangedCB(const FFaDynCB1<FuiSpringCharValues&>& aDynCB);

  // Setting values:

  void setValues(const FuiSpringCharValues& values);
  void setCBs(const FuiSpringCharValues& values);

  // Getting values:

  void getValues(FuiSpringCharValues& values);

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  // Shadow pointers from subclass.
  // Subclass is responsible to set them up:

  FFuLabelFrame       *mySpringFunctionFrame;
  FFuLabelFrame       *myFailureFrame;
  FFuLabelFrame       *myYieldFrame;

  FuiQueryInputField  *mySpringFunctionField;
  FFuLabel            *mySpringFunctionDescription;

  FFuIOField          *myDeflectionMaxField;
  FFuIOField          *myDeflectionMinField;
  FFuIOField          *myForceMaxField;
  FFuIOField          *myForceMinField;

  FFuToggleButton     *myDeflectionMaxToggle;
  FFuToggleButton     *myDeflectionMinToggle;
  FFuToggleButton     *myForceMaxToggle;
  FFuToggleButton     *myForceMinToggle;

  FuiQueryInputField  *myYieldForceMaxEngineField;
  FuiQueryInputField  *myYieldForceMinEngineField;
  FFuToggleButton     *myYieldForceMaxToggle;
  FFuToggleButton     *myYieldForceMinToggle;

  FFuToggleButton     *myYieldDeflectionMaxToggle;
  FFuIOField          *myYieldDeflectionMaxField;

private:

  // Internal methods for rerouting of Callbacks

  void onDoubleChanged(double);
  void onBoolChanged(bool);
  void onBoolChanged(int, bool);
  void onQIFieldChanged(FuiQueryInputField*);
  void onValuesChanged();

  // Callback Objects

  FFaDynCB1<FuiSpringCharValues&> myValuesChangedCB;
  FFaDynCB0                       myChangedCB;

  // Internal Vars

  bool IAmSensitive;
};


class FuiSpringCharValues
{
public:
  FuiSpringCharValues()
    {
      isTranslationalSpring = true;
      isConstantStiffness = true;
      constantStiffness = 0.0;
      springFunction = NULL;

      deflectionMax = 0.0;
      deflectionMin = 0.0;
      forceMax = 0.0;
      forceMin = 0.0;

      useDeflectionMax = false;
      useDeflectionMin = false;
      useForceMax = false;
      useForceMin = false;

      useYieldForceMax = false;
      useYieldForceMin = false;
      isConstantYieldForceMax = true;
      isConstantYieldForceMin = true;
      constantYieldForceMax = 0.0;
      constantYieldForceMin = 0.0;

      useYieldDeflectionMax = false;
      yieldDeflectionMax = 0.0;
    }

  FmModelMemberBase *springFunction;
  FFuaQueryBase     *springFunctionQuery;

  bool               isTranslationalSpring;
  bool               isConstantStiffness;
  double             constantStiffness;
  FFaDynCB1<FuiQueryInputFieldValues&> springFunctionFieldButtonCB;

  double deflectionMax;
  double deflectionMin;
  double forceMax;
  double forceMin;

  bool useDeflectionMax;
  bool useDeflectionMin;
  bool useForceMax;
  bool useForceMin;

  bool useYieldForceMax;
  bool useYieldForceMin;
  bool isConstantYieldForceMax;
  bool isConstantYieldForceMin;
  FmModelMemberBase *yieldForceMaxEngine;
  FmModelMemberBase *yieldForceMinEngine;
  FFuaQueryBase     *yieldForceEngineQuery;
  FFaDynCB1<FuiQueryInputFieldValues&> yieldForceFieldMaxButtonCB;
  FFaDynCB1<FuiQueryInputFieldValues&> yieldForceFieldMinButtonCB;
  double             constantYieldForceMax;
  double             constantYieldForceMin;

  bool   useYieldDeflectionMax;
  double yieldDeflectionMax;
};

#endif
