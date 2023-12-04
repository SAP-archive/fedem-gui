// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_INPUT_SELECTOR_H
#define FUI_INPUT_SELECTOR_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <vector>
#include <string>

class FuiQueryInputField;
class FuiInputSelectorValues;
class FFuLabelFrame;
class FFuLabel;
class FFuOptionMenu;
class FFuaQueryBase;
class FmModelMemberBase;


class FuiInputSelector : public virtual FFuMultUIComponent
{
public:
  FuiInputSelector();
  virtual ~FuiInputSelector() {}

  // Callbacks:

  void setValuesChangedCB(const FFaDynCB1<FuiInputSelectorValues&>& aDynCB);
  void setSetDBValuesCB(const FFaDynCB1<FuiInputSelectorValues&>& aDynCB);
  void setPickCB(const FFaDynCB0& aDynCB);

  // Setting values:

  void setValues(const FuiInputSelectorValues& values);

  // Getting values:

  void getValues(FuiInputSelectorValues& values);

  // Look

  void setLabel(const std::string& label);
  virtual void setSensitivity(bool isSensitive);

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  // Shadow pointers from subclass.
  // Subclass is responsible to set them up:

  FFuLabelFrame     * myLabelFrame;
  FuiQueryInputField* myObjectSelector;
  FFuLabel          * myDofLabel;
  FFuOptionMenu     * myDofSelector;
  FFuLabel          * myVariableLabel;
  FFuOptionMenu     * myVariableSelector;

private:
  void updateSensitivity();

  // Internal methods for rerouting of Callbacks

  void onIntChanged(int idx);
  void onValuesChanged();
  void setDBValues();

  // Callback Objects

  FFaDynCB1<FuiInputSelectorValues&> myValuesChangedCB;
  FFaDynCB1<FuiInputSelectorValues&> mySetDBValuesCB;

  // Internal Vars

  bool IAmSensitive;
  bool IAmShowingDofList;
  bool IAmShowingVariableList;
};


class FuiInputSelectorValues
{
public:
  FuiInputSelectorValues()
  {
    objectSelectorQuery = 0;
    selectedObject = 0;
    showDofList = showVariableList = false;
    selectedDofIdx = selectedVariableIdx = -1;
  }

  FFuaQueryBase*     objectSelectorQuery;
  FmModelMemberBase* selectedObject;

  bool           showDofList;
  std::vector<std::string> dofList;
  int            selectedDofIdx;

  bool           showVariableList;
  std::vector<std::string> variableList;
  int            selectedVariableIdx;
};

#endif
