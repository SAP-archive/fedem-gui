// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUICTRLELEMPROPERTIES_H
#define FUICTRLELEMPROPERTIES_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include <string>
#include <vector>

class FFuLabel;
class FFuLabelField;
class FFuLabelFrame;
class FFuTableView;


class FuiCtrlElemProperties : virtual public FFuMultUIComponent,
			      public FFuUAExistenceHandler,
			      public FFuUADataHandler
{
public:
  FuiCtrlElemProperties() {}
  virtual ~FuiCtrlElemProperties() {}

  // Virtual override of the Data dialog methods :
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void buildDynamicWidgets(const FFuaUIValues* values);
  virtual void eraseDynamicWidgets();

  // Lock from user input :
  virtual void setSensitivity(bool isSensitive);

protected:
  // Callback called by all fields. Collects all the data from
  // the ui and calls invokeNewValuesCB with the new data.
  void onValueChanged(char* dummy);

  // Init method to be called by UILibDep sub class after it
  // has initialized all the shado widget pointers.
  void initWidgets();

  // Overridden method that does the geometry management :
  virtual void placeWidgets(int width, int height);

  // A method to be reimplemented in ui-lib dependent subclass
  // that must make a FFuLabelField and return it.
  virtual FFuLabelField* makeALabelField() = 0;

  FFuLabel*      myElemPixmap;
  FFuLabelFrame* myParameterFrame;
  FFuTableView*  myParameterView;
};


class FuaCtrlElemPropertiesValues : public FFuaUIValues
{
public:
  FuaCtrlElemPropertiesValues() { pixmap = 0; }
  virtual ~FuaCtrlElemPropertiesValues() {}

  struct CtrlParameter
  {
    double value;
    std::string description;
    CtrlParameter(double v = 0.0) { value = v; }
  };

  const char**          pixmap;
  std::vector<CtrlParameter> parameters;
};

#endif
