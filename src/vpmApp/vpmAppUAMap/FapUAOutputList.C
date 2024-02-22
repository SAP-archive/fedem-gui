// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAOutputList.H"
#include "vpmUI/vpmUITopLevels/FuiOutputList.H"
#include "vpmUI/Fui.H"


Fmd_SOURCE_INIT(FAPUAOUTPUTLIST, FapUAOutputList, FapUAExistenceHandler);

//----------------------------------------------------------------------------

FapUAOutputList::FapUAOutputList(FuiOutputList* uic)
  : FapUAExistenceHandler(uic), FapUAFinishHandler(uic), FapUACommandHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAOutputList);

  this->ui = uic;
}
//----------------------------------------------------------------------------

void FapUAOutputList::finishUI()
{
  Fui::outputListUI(false,true);
}
//----------------------------------------------------------------------------

FFuaUICommands* FapUAOutputList::getCommands()
{
  FuaOutputListCommands* cmds = new FuaOutputListCommands();

  cmds->popUpMenu = {
    FFuaCmdItem::getCmdItem("cmdId_outputList_copy"),
    FFuaCmdItem::getCmdItem("cmdId_outputList_selectAll"),
    &this->separator,
    FFuaCmdItem::getCmdItem("cmdId_outputList_clear")
  };

  return cmds;
}
