// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  \file FapUADataHandler.H

  \date May 12 1999

  \brief A plugin class that is a receiver for FFuUADataHandler.

  \details FapUADataHandler's task is to handle the data transfer between
  the UI and the DB. Plugin whenever needed that fuctionallity.

  \author Dag R. Christensen
*/

#ifndef FAP_UA_DATA_HANDLER_H
#define FAP_UA_DATA_HANDLER_H

#include <cstddef>

class FFuUADataHandler;
class FFuaUIValues;


class FapUADataHandler
{
public:
  FapUADataHandler(FFuUADataHandler* ui = NULL);
  virtual ~FapUADataHandler() {}

  //! Does a complete update of the UI (dynamic widgets and all)
  void updateUI();

  virtual void updateUIValues();
  void setUIValues(const FFuaUIValues* values);
  void getUIValues(FFuaUIValues* values);
  void updateDBValues();
  void clearUIValues();

protected:
  virtual void setAndGetDBValues(FFuaUIValues* values);

  // Reimplementations

  //! This method is supposed to heap-allocate FFuaUIValues.
  //! Remember to delete.
  virtual FFuaUIValues* createValuesObject() { return NULL; }
  //! Sets values in DB, which is expected to be re-implemented for the UA's.
  virtual void setDBValues(FFuaUIValues*) {}
  //! Gets values in DB, which is expected to be re-implemented for the UA's.
  virtual void getDBValues(FFuaUIValues*) {}

private:
  FFuUADataHandler* ui;
};

#endif
