// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_ADV_ANALYSIS_OPTIONS_H
#define FAP_UA_ADV_ANALYSIS_OPTIONS_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"

class FuiAdvAnalysisOptions;


class FapUAAdvAnalysisOptions : public FapUAExistenceHandler,
                                public FapUADataHandler,
                                public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAAdvAnalysisOptions(FuiAdvAnalysisOptions* ui);
  virtual ~FapUAAdvAnalysisOptions() {}

private:
  virtual FFuaUIValues* createValuesObject();

  // DB interface
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  // Callbacks
  virtual void finishUI();
};

#endif
