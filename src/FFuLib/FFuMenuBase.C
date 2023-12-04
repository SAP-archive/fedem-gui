// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuMenuBase.H"


void FFuMenuBase::deleteItems()
{
  this->basicDeleteItems();
  cmdItems.clear();
  popups.clear();
}


void FFuMenuBase::setCmdItemToggled(FFuaCmdItem* item, bool toggle)
{
  this->setItemToggled(this->findCmdItem(item),toggle);
}


FFuaCmdItem* FFuMenuBase::findCmdItem(int anId) const
{
  std::map<int,FFuaCmdItem*>::const_iterator id = cmdItems.find(anId);
  return id == cmdItems.end() ? NULL : id->second;
}


int FFuMenuBase::findCmdItem(FFuaCmdItem* item) const
{
  for (const std::pair<const int,FFuaCmdItem*>& id : this->cmdItems)
    if (id.second == item) return id.first;
  return 0;
}


FFuPopUpMenu* FFuMenuBase::findPopup(int anId) const
{
  std::map<int,FFuPopUpMenu*>::const_iterator id = popups.find(anId);
  return id == popups.end() ? NULL : id->second;
}
