// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUACtrlGridAttributes.H"
#include "vpmUI/vpmUITopLevels/FuiCtrlGridAttributes.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdCtrlGrid.H"
#endif

Fmd_SOURCE_INIT(FAPUACTRLGRIDATTRIBUTES, FapUACtrlGridAttributes, FapUAExistenceHandler);


FapUACtrlGridAttributes::FapUACtrlGridAttributes(FuiCtrlGridAttributes* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUACtrlGridAttributes);
}


FFuaUIValues* FapUACtrlGridAttributes::createValuesObject()
{
  return new FuaCtrlGridValues();
}


void FapUACtrlGridAttributes::setDBValues(FFuaUIValues* values)
{
  FuaCtrlGridValues* newVals = dynamic_cast<FuaCtrlGridValues*>(values);
  if (newVals)
    {
#ifdef USE_INVENTOR
      FdCtrlGrid::setGridSize(newVals->gridXSpacing, newVals->gridYSpacing);
      FdCtrlGrid::setSnapDistance(newVals->snapXSpacing, newVals->snapYSpacing);
      FdCtrlGrid::setGridState(newVals->gridOn);
      FdCtrlGrid::setSnapState(newVals->snapOn);
#endif
    }
}


void FapUACtrlGridAttributes::getDBValues(FFuaUIValues* values)
{
  FuaCtrlGridValues* newVals = dynamic_cast<FuaCtrlGridValues*>(values);
  if (newVals)
    {
#ifdef USE_INVENTOR
      newVals->gridXSpacing = FdCtrlGrid::getGridSizeX();
      newVals->gridYSpacing = FdCtrlGrid::getGridSizeY();
      newVals->snapXSpacing = FdCtrlGrid::getSnapDistanceX();
      newVals->snapYSpacing = FdCtrlGrid::getSnapDistanceY();
      newVals->gridOn = FdCtrlGrid::getGridState();
      newVals->snapOn = FdCtrlGrid::getSnapState();
#endif
    }
}
