// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUACtrlModeller.H"
#include "vpmApp/vpmAppUAMap/FapUACtrlGridAttributes.H"

#include "vpmUI/vpmUITopLevels/FuiCtrlModeller.H"
#include "vpmUI/vpmUITopLevels/FuiCtrlGridAttributes.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdCtrlDB.H"
#endif


Fmd_SOURCE_INIT(FAPUACTRLMODELLER, FapUACtrlModeller, FapUAExistenceHandler);


FapUACtrlModeller::FapUACtrlModeller(FuiCtrlModeller* uic)
  : FapUAExistenceHandler(uic), FapUAFinishHandler(uic)
{
  myCtrlModeller = uic;

  myUACtrlGridAttributes = new FapUACtrlGridAttributes(uic->getGridAttributesUI());
}


void FapUACtrlModeller::finishUI()
{
#ifdef USE_INVENTOR
  FdCtrlDB::closeCtrl();
#endif
}
