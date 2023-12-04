// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  Mapping class between DB/Application and UI for the Fedem control system modeller.
  Created from old code made by Magnus Svanberg.
*/

#ifndef FAP_UA_CTRL_MODELLER_H
#define FAP_UA_CTRL_MODELLER_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"

class FuiCtrlModeller;
class FapUACtrlGridAttributes;


class FapUACtrlModeller : public FapUAExistenceHandler,
                          public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUACtrlModeller(FuiCtrlModeller* ui);
  virtual ~FapUACtrlModeller() {}

private:
  virtual void finishUI();

private:
  FapUACtrlGridAttributes* myUACtrlGridAttributes;
  FuiCtrlModeller*         myCtrlModeller;
};

#endif
