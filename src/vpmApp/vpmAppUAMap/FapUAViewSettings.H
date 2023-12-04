// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_VIEW_SETTINGS_H
#define FAP_UA_VIEW_SETTINGS_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"

class FuiViewSettings;


class FapUAViewSettings : public FapUAExistenceHandler, public FapUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAViewSettings(FuiViewSettings* ui);
  virtual ~FapUAViewSettings() {}

protected:
  virtual FFuaUIValues* createValuesObject();  

  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values); 
};

#endif
