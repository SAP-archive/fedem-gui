// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_UA_ITEMS_VIEW_HANDLER_H
#define FFU_UA_ITEMS_VIEW_HANDLER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <vector>


class FFuUAItemsViewHandler
{
public:
  FFuUAItemsViewHandler() {}
  virtual ~FFuUAItemsViewHandler() {}

  // These callbacks are set by FapUAItemsViewHandler
  void setSetUpdateOnChangesWhenInMemCB(const FFaDynCB1<bool>& dynCB)
    {this->setUpdateOnChangesWhenInMemCB = dynCB;}
  void setGetUpdateOnChangesWhenInMemCB(const FFaDynCB1<bool&>& dynCB)
    {this->getUpdateOnChangesWhenInMemCB = dynCB;}
  void setUpdateSessionCB(const FFaDynCB0& dynCB)
    {this->updateSessionCB = dynCB;}
  void setClearSessionCB(const FFaDynCB0& dynCB)
    {this->clearSessionCB = dynCB;}
  void setPermTotSelectItemsCB(const FFaDynCB1<std::vector<int>&>& dynCB)
    {this->permTotSelectItemsCB = dynCB;}

  // session
  // update = true  -> initial updateSession
  // update = false -> update/clearSession on onPoppedUp/onPoppedDownToMem
  void setUpdateOnChangesWhenInMem(bool update);
  bool getUpdateOnChangesWhenInMem();
  void updateSession();
  void clearSession();

  // selection
  virtual void permTotSelectItems(const std::vector<int>&) {} //no notify
  virtual std::vector<int> getSelectedItems() { return std::vector<int>(); }
  virtual bool isItemSelected(int) { return false; }
  virtual bool isSglSelectionMode() { return false; }

  // item manipulation
  virtual void deleteItem(int) {}
  virtual void deleteItems() {}

protected:
  void onPoppedUpFromMemory();
  void onPoppedDownToMemory();

  void invokeSetUpdateOnChangesWhenInMemCB(bool update)
    {this->setUpdateOnChangesWhenInMemCB.invoke(update);}
  void invokeGetUpdateOnChangesWhenInMemCB(bool& update)
    {this->getUpdateOnChangesWhenInMemCB.invoke(update);}
  void invokeUpdateSessionCB()
    {this->updateSessionCB.invoke();}
  void invokeClearSessionCB()
    {this->clearSessionCB.invoke();}
  void invokePermTotSelectItemsCB(std::vector<int> totalSelection)
    {this->permTotSelectItemsCB.invoke(totalSelection);}

private:
  FFaDynCB1<bool> setUpdateOnChangesWhenInMemCB;
  FFaDynCB1<bool&> getUpdateOnChangesWhenInMemCB;
  FFaDynCB0 updateSessionCB;
  FFaDynCB0 clearSessionCB;
  FFaDynCB1<std::vector<int>&> permTotSelectItemsCB;
};

#endif
