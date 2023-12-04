// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_MENU_BASE_H
#define FFU_MENU_BASE_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <map>

class FFuPopUpMenu;
class FFuaCmdItem;


class FFuMenuBase : virtual public FFuComponentBase
{
public:
  FFuMenuBase() {}
  virtual ~FFuMenuBase() {}

  //! \brief Method to add entries (separators, regular items or other menus).
  //! \details If \a item is a FFuaCmdHeaderItem, a popup menu is created
  //! and parented to *this. Regular and header items are book-kept and must
  //! not be deleted as long as their parent menu exists.
  //! A menu bar views only text.
  //! A popup menu views pixmap and text:
  //! pixmap+text -> icon(small pixmap) and text, pixmap only -> (big)pixmap.
  virtual bool insertCmdItem(FFuaCmdItem* item) = 0;

  //! \brief Method to update sensitivity or toggle status of \a item.
  virtual void updateCmdItem(FFuaCmdItem* item, bool sensitivity) = 0;

  void deleteItems();

  virtual bool isMenuEmpty() const = 0;

  // Invoked both for toggle and nontoggle items
  void setCommonCB(const FFaDynCB1<FFuaCmdItem*>& cb) { commonCB = cb; }
  void invokeCommonCB(FFuaCmdItem* item) { commonCB.invoke(item); }
  void setCmdItemToggled(FFuaCmdItem* item, bool toggle);

protected:
  virtual void insertSeparator() = 0;
  virtual void setItemSensitivity(int,bool) {}
  virtual void setItemToggled(int,bool) {}

  //convertions id's <->  FFuaCmdItem objects
  FFuaCmdItem* findCmdItem(int anId) const;
  int findCmdItem(FFuaCmdItem* item) const;
  FFuPopUpMenu* findPopup(int anId) const;

  virtual int basicNewItem(FFuaCmdItem* item, FFuPopUpMenu* menu = NULL) = 0;
  virtual void basicDeleteItems() = 0;

  std::map<int,FFuaCmdItem*> cmdItems;
  std::map<int,FFuPopUpMenu*> popups;//because stupid qt cannot retrive the popup from an id 

private:
  FFaDynCB1<FFuaCmdItem*> commonCB;
};

#endif
