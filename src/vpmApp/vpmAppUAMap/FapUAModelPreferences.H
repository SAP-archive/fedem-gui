// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPUAMODELPREFERENCES_H
#define FAPUAMODELPREFERENCES_H

#include <string>

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"


class FuiModelPreferences;


class FapUAModelPreferences : public FapUAExistenceHandler,
			      public FapUADataHandler,
			      public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAModelPreferences(FuiModelPreferences* ui);
  virtual ~FapUAModelPreferences() {}

private:
  // from datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  // from finishhandler
  virtual void finishUI();

  void updateDescriptionCB(std::string const& newdescr);
  void changeRepositoryCB(bool switchToInternal);

  FuiModelPreferences* ui;
};

#endif
