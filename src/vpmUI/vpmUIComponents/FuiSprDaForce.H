// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_SPR_DA_FORCE_H
#define FUI_SPR_DA_FORCE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <string>

class FFuLabel;
class FFuLabelFrame;
class FFuToggleButton;
class FFuaQueryBase;
class FuiQueryInputField;
class FuiQueryInputFieldValues;
class FuiSprDaForceValues;
class FmModelMemberBase;


class FuiSprDaForce : public virtual FFuMultUIComponent
{
public:
  FuiSprDaForce() { IAmSensitive = IAmSpringUI = true; }
  virtual ~FuiSprDaForce() {}

  // Setting Up :

  void setAsSpring(bool yesOrNo);
  virtual void setSensitivity(bool isSensitive);

  // Callbacks :

  void setChangedCB(const FFaDynCB0& aDynCB);
  void setValuesChangedCB(const FFaDynCB1<FuiSprDaForceValues&>& aDynCB);

  // Setting and getting values:

  void buildDynamicWidgets(const FuiSprDaForceValues& values);
  void setCBs(const FuiSprDaForceValues& values);
  void setValues(const FuiSprDaForceValues& values);
  void getValues(FuiSprDaForceValues& values);

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  // Shadow pointers from subclass.
  // Subclass is responsible to set them up:

  FFuLabelFrame*      myFrame;
  FFuLabel*           myFunctionLabel;
  FuiQueryInputField* myFunctionField;
  FFuLabel*           myScaleLabel;
  FuiQueryInputField* myScaleField;
  FFuToggleButton*    myIsDefDamperToggle;

private:

  // Internal methods for rerouting of Callbacks

  void onQIFieldChanged(FuiQueryInputField*);
  void onBoolChanged(bool);

  // Callback Objects

  FFaDynCB1<FuiSprDaForceValues&> myValuesChangedCB;
  FFaDynCB0                       myChangedCB;

  // Internal Vars/methods

  void updateSprDaLabels();

  bool IAmSensitive;
  bool IAmSpringUI;
};


class FuiSprDaForceValues
{
public:
  FuiSprDaForceValues()
    {
      isDefDamper = false;
      showDefDamper = false;
      isConstant = true;
      constFunction = constScale = 0.0;
      functionQuery = engineQuery = 0;
      selectedFunction = selectedScaleEngine = 0;
    }

  bool isDefDamper;
  char showDefDamper; // -1: visible but insensitive, 0: invisible, 1: sensitive

  FFuaQueryBase     * functionQuery;
  bool                isConstant;
  FmModelMemberBase * selectedFunction;
  std::string              functionUIString;
  double              constFunction;
  FFaDynCB1<FuiQueryInputFieldValues&> myFunctionQIFieldButtonCB;

  FFuaQueryBase     * engineQuery;
  FmModelMemberBase * selectedScaleEngine;
  std::string              scaleEngUIString;
  double              constScale;
  FFaDynCB1<FuiQueryInputFieldValues&> myEngineQIFieldButtonCB;
};

#endif
