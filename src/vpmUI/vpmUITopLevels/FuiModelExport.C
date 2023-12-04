// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiModelExport.H"

Fmd_SOURCE_INIT(FUI_MODELEXPORT, FuiModelExport, FFuTopLevelShell);


FuiModelExport::FuiModelExport()
{
  Fmd_CONSTRUCTOR_INIT(FuiModelExport);
}


void FuiModelExport::onPoppedUp()
{
  this->updateUIValues();
}


bool FuiModelExport::onClose()
{
  this->invokeFinishedCB();
  return false;
}


FFuaUIValues* FuiModelExport::createValuesObject()
{
  return new FuaModelExportValues();
}
