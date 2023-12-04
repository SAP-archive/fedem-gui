// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_QUERY_INPUT_FIELD_H
#define FAP_UA_QUERY_INPUT_FIELD_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/FapUAQueryMatch.H"
#include <vector>


class FuiQueryInputField;

class FapUAQueryInputField : public FapUAExistenceHandler, public FapUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAQueryInputField(FuiQueryInputField* ui);

protected:
  virtual void getDBValues(FFuaUIValues* values); 
  virtual FFuaUIValues* createValuesObject();

private:
  FuiQueryInputField*         myQueryInputFieldUI;
  std::vector<FFuaQueryMatch> myQueryMatches;
};

#endif
