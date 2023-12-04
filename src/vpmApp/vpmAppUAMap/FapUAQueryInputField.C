// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAQueryInputField.H"
#include "vpmApp/vpmAppUAMap/FapUAQuery.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "vpmDB/FmModelMemberBase.H"
#include "vpmDB/FmDB.H"


Fmd_SOURCE_INIT(FAPUAENGINEREFFIELD, FapUAQueryInputField, FapUAExistenceHandler);

FapUAQueryInputField::FapUAQueryInputField(FuiQueryInputField* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAQueryInputField);

  myQueryInputFieldUI = uic;
}


FFuaUIValues* FapUAQueryInputField::createValuesObject()
{
  return new FuaQueryInputFieldValues();
}


void FapUAQueryInputField::getDBValues(FFuaUIValues* values)
{
  FuaQueryInputFieldValues* v = dynamic_cast<FuaQueryInputFieldValues*>(values);
  if (!v) return;

  // Check if we've got a query specification

  if (v->query)
  {
    // Get Query
    std::vector<FmModelMemberBase*> matches;
    FmDB::getQuery(matches,static_cast<FapUAQuery*>(v->query));

    // Fill this's storage with result and send pointers to the UI

    myQueryMatches.clear();
    myQueryMatches.reserve(matches.size());
    v->matches.clear();
    v->matches.reserve(matches.size());

    for (FmModelMemberBase* obj : matches)
    {
      myQueryMatches.push_back({obj,obj->getInfoString()});
      v->matches.push_back(&myQueryMatches.back());
    }
  }

  // Check if we've got a query match to look up index for

  if (v->matchToLookupIndexFor)
    for (size_t i = 0; i < myQueryMatches.size(); i++)
      if (myQueryMatches[i].matchItem == v->matchToLookupIndexFor)
      {
        v->selectedIdx = i;
        return;
      }

  v->selectedIdx = -1;
}
