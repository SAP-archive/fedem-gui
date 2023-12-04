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

FapUAOutputList::~FapUAOutputList()
{
}
//----------------------------------------------------------------------------

void FapUAOutputList::finishUI()
{
  Fui::outputListUI(false,true);
}
//----------------------------------------------------------------------------

FFuaUICommands* FapUAOutputList::createCommandsObject()
{
  return new FuaOutputListCommands();
}
//----------------------------------------------------------------------------

void FapUAOutputList::getCommands(FFuaUICommands* commands)
{
  FuaOutputListCommands* cmds = (FuaOutputListCommands*) commands;
  cmds->popUpMenu.clear();

  cmds->popUpMenu.push_back(FFuaCmdItem::getCmdItem("cmdId_outputList_copy"));
  cmds->popUpMenu.push_back(FFuaCmdItem::getCmdItem("cmdId_outputList_selectAll"));
  cmds->popUpMenu.push_back(&this->separator);
  cmds->popUpMenu.push_back(FFuaCmdItem::getCmdItem("cmdId_outputList_clear"));
}
