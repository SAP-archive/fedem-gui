// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAObjectBrowser.H"
#include "vpmUI/vpmUITopLevels/FuiObjectBrowser.H"


Fmd_SOURCE_INIT(FAPUAOBJECTBROWSER, FapUAObjectBrowser, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAObjectBrowser::FapUAObjectBrowser(FuiObjectBrowser* ui)
  : FapUAExistenceHandler(ui), FapUADataHandler(ui),
    permSignalConnector(this), modelMemberChangedConnector(this)
{
  Fmd_CONSTRUCTOR_INIT(FapUAObjectBrowser);

  this->myUI = ui;
  this->mySelectedFmItem = NULL;

  // Find selection that created this dialog
  std::vector<FmModelMemberBase*> objs;
  FapEventManager::getMMBSelection(objs,mySelectedFmItem);
  if (!mySelectedFmItem && !objs.empty())
    mySelectedFmItem = objs.back();
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAObjectBrowser::createValuesObject()
{
  return new FuaObjectBrowserValues();
}
//----------------------------------------------------------------------------

void FapUAObjectBrowser::getDBValues(FFuaUIValues* values)
{
  static_cast<FuaObjectBrowserValues*>(values)->obj = mySelectedFmItem;
}
//----------------------------------------------------------------------------

void FapUAObjectBrowser::onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
                                                const std::vector<FFaViewItem*>&,
                                                const std::vector<FFaViewItem*>&)
{
  // Show the last selected model member
  mySelectedFmItem = NULL;
  size_t i = totalSelection.size();
  while (i > 0 && !mySelectedFmItem)
    mySelectedFmItem = dynamic_cast<FmModelMemberBase*>(totalSelection[--i]);

  this->updateUI();
}
//----------------------------------------------------------------------------

void FapUAObjectBrowser::onModelMemberChanged(FmModelMemberBase* changedObj)
{
  if (changedObj == mySelectedFmItem)
    this->updateUI();
}
