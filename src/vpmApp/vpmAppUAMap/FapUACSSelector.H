// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_CS_SELECTOR_H
#define FAP_UA_CS_SELECTOR_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"

class FuiCSSelector;
class FapUACSListView;


class FapUACSSelector : public FapUAExistenceHandler
{
  Fmd_HEADER_INIT();

public:
  FapUACSSelector(FuiCSSelector* ui);
  virtual ~FapUACSSelector() {}

private:
  void onImport();

private:
  FuiCSSelector*   myUI;
  FapUACSListView* csUA;
  FapUACSListView* matUA;
};

#endif
