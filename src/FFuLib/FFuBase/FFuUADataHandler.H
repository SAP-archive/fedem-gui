// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_UA_DATA_HANDLER_H
#define FFU_UA_DATA_HANDLER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuaUIValues;


class FFuUADataHandler
{
public:
  FFuUADataHandler() {}
  virtual ~FFuUADataHandler() {}

public:
  // Callbacks are set by FapUADataHandler
  // These callbacks are set by FapUADataHandler
  void setSetAndGetDBValuesCB(const FFaDynCB1<FFuaUIValues*>& dynCB)
    {this->setAndGetDBValuesCB = dynCB;}
  void setUpdateUIValuesCB(const FFaDynCB0& dynCB)
    {this->updateUIValuesCB = dynCB;}

  // Functionality
  virtual void updateUIValues() { this->invokeUpdateUIValuesCB(); }
  virtual bool updateDBValues(bool updateui=true);

  // no need for a clear session for a datadialog, the ua class should
  // only ping-pong data uncritically, opposit the modelview dialog

  // REIMPL's
  // Method concerning values in ui
  virtual void clearUIValues() {}
  // This method is supposed to heap-allocate a FFuaUIValues object.
  // Remember to delete it.
  virtual FFuaUIValues* createValuesObject() { return 0; }
  virtual void setUIValues(const FFuaUIValues*) {}
  virtual void getUIValues(FFuaUIValues*) {}

  // Method to set up the "dynamic widgets" in ui.
  // Reimplement if you want some major changes done
  // more seldom than the setting/getting of values.
  virtual void buildDynamicWidgets(const FFuaUIValues*) {}

protected:
  // This CB sets the ui values in the DB, and re-gets the values from the DB.
  // This is done to ensure correspondance between DB and UI and the user is
  // strongly recommmended to update the ui's values afterwards.
  void invokeSetAndGetDBValuesCB(FFuaUIValues* values)
    {this->setAndGetDBValuesCB.invoke(values);}

private:
  // This CB gets the current DB values and sets them in the UI
  // This should normally be done each time the ui poppes up
  void invokeUpdateUIValuesCB() { this->updateUIValuesCB.invoke(); }

private:
  FFaDynCB1<FFuaUIValues*> setAndGetDBValuesCB;
  FFaDynCB0 updateUIValuesCB;
};

////////////////////////////////////////////////////////////////////////

class FFuaUIValues
{
public:
  FFuaUIValues(){}
  virtual ~FFuaUIValues(){}
};
////////////////////////////////////////////////////////////////////////

#endif
