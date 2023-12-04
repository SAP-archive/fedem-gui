// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUISIMPLELOAD_H
#define FUISIMPLELOAD_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabelFrame;
class FFuaQueryBase;
class FuiQueryInputField;
class FuiQueryInputFieldValues;
class FuiSimpleLoadValues;
class FmModelMemberBase;


class FuiSimpleLoad : public virtual FFuMultUIComponent
{
public:
  FuiSimpleLoad() {}
  virtual ~FuiSimpleLoad() {}

  // Setting Up :

  void setLabel(const char* text);
  virtual void setSensitivity(bool isSensitive);

  // Callbacks :

  void setChangedCB(const FFaDynCB0& aDynCB);
  void setValuesChangedCB(const FFaDynCB1<FuiSimpleLoadValues&>& aDynCB);

  // Setting values:

  void setValues(const FuiSimpleLoadValues& values);
  void setCBs(const FuiSimpleLoadValues& values);

  // Getting values:

  void getValues(FuiSimpleLoadValues& values);

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  // Shadow pointers from subclass.
  // Subclass is responsible to set them up:

  FFuLabelFrame*      myFrame;
  FuiQueryInputField* myEngineField;

private:

  // Internal methods for rerouting of Callbacks

  void onQIFieldChanged(FuiQueryInputField* changedField);
  void onValuesChanged();

  FFaDynCB1<FuiSimpleLoadValues&> myValuesChangedCB;
  FFaDynCB0                       myChangedCB;
};


class FuiSimpleLoadValues
{
public:
  FuiSimpleLoadValues()
  {
    isConstant = true;
    constValue = 0.0;
    engineQuery = 0;
    selectedEngine = 0;
  }

  bool   isConstant;
  double constValue;

  FFuaQueryBase*     engineQuery;
  FmModelMemberBase* selectedEngine;

  FFaDynCB1<FuiQueryInputFieldValues&> myEngineQIFieldButtonCB;
};

#endif
