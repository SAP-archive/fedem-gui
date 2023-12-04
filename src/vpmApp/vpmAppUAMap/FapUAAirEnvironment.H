// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_AIR_ENVIRONMENT_H
#define FAP_UA_AIR_ENVIRONMENT_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"

class FuiAirEnvironment;


class FapUAAirEnvironment : public FapUAExistenceHandler,
			    public FapUADataHandler,
			    public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAAirEnvironment(FuiAirEnvironment* ui);
  virtual ~FapUAAirEnvironment() {}

private:
  // from datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  // from finishhandler
  virtual void finishUI();

  FuiAirEnvironment* ui;
};

#endif
