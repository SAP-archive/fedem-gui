// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtMenuBase.H"
#include "FFuLib/FFuQtComponents/FFuQtPopUpMenu.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"


bool FFuQtMenuBase::insertCmdItem(FFuaCmdItem* item)
{
  FFuaCmdHeaderItem* header = dynamic_cast<FFuaCmdHeaderItem*>(item);

  if (header) {
    FFuPopUpMenu* popup = new FFuQtPopUpMenu(dynamic_cast<QWidget*>(this));
    int id = this->basicNewItem(item,popup);
    if (!id) return false;
    this->cmdItems[id] = item; // header cmds are book-kept
    this->popups[id] = popup;
    for (FFuaCmdItem* child : header->getChildren())
      popup->insertCmdItem(child);
  }
  else if (dynamic_cast<FFuaCmdSeparatorItem*>(item))
    this->insertSeparator();
  else {
    int id = this->basicNewItem(item);
    if (!id) return false;
    this->cmdItems[id] = item; // real cmds are book-kept
  }
  return true;
}


void FFuQtMenuBase::updateCmdItem(FFuaCmdItem* item, bool sensitivity)
{
  if (dynamic_cast<FFuaCmdSeparatorItem*>(item)) return;

  FFuaCmdHeaderItem* header = dynamic_cast<FFuaCmdHeaderItem*>(item);
  if (header) {
    FFuPopUpMenu* popup = this->findPopup(this->findCmdItem(item));
    if (popup)
      for (FFuaCmdItem* child : header->getChildren())
        popup->updateCmdItem(child, sensitivity);
  }
  else if (sensitivity)
    this->setItemSensitivity(this->findCmdItem(item), item->getSensitivity());
  else if (item->getToggleAble())
    this->setItemToggled(this->findCmdItem(item), item->getToggled());
}
