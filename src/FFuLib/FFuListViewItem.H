// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_LIST_VIEW_ITEM_H
#define FFU_LIST_VIEW_ITEM_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuListView;


/*!
  This class automatically sets an unique id (>-1) for the item. The id is
  meant to serve as an identifier for external bookkeeping. Never bookkeep
  the item pointers as they may change during item manipulation (QListView
  is no good!).

  \author Dag R. Christensen
  \date Mar 5 1999
*/

class FFuListViewItem 
{
public:
  FFuListViewItem();
  virtual ~FFuListViewItem();
  
  // Unique item identifier
  int  getItemId()       { return this->itemId;}
  void setItemId(int id) { this->itemId = id ; }

  // Copy text/toggle etc, but not ID (this item is unique)
  void copyData(FFuListViewItem* original);
  virtual void copyPixmaps(FFuListViewItem* original)=0;
  
  // Basic item functions
  virtual void  setItemText(int col,const char* text)=0;
  virtual char* getItemText(int col=0)=0;

  virtual void  setItemTextBold(bool bold=true)=0;
  virtual void  setItemTextItalic(bool italic=true)=0;

  virtual void  setItemImage(int col,const char **pixmap)=0;

  virtual bool  isItemSelected()= 0;

  virtual int   getDepth()=0;

  virtual void  setItemSelectable(bool enable)=0;

  // Relations
  virtual FFuListView*     getListView()= 0;
  virtual FFuListViewItem* getParentItem()= 0;
  virtual FFuListViewItem* getFirstChildItem()= 0;
  virtual FFuListViewItem* getLastChildItem()= 0;
  virtual FFuListViewItem* getNextSiblingItem()= 0;
          FFuListViewItem* getPreviousSiblingItem();
  virtual int              getNSiblings() = 0;//with me included
  virtual int              getNChildren() = 0;
  int              getItemPosition();//starts with 0
  
  virtual void setItemDropable(bool enable) = 0;
  virtual void setItemDragable(bool enable) = 0;


  // Levels
  bool isFirstLevel(); // no parent 
  bool isSecondLevel(); // no grandparent but parent 
  bool isThirdLevel();  // no grand-grandparent but grandparent and parent 
  
  

  //Toggle
  enum {UNTOGGLED,TOGGLED,HALFTOGGLED,NTOGGLES};//toggle
  bool isItemToggleAble() {return this->toggleAble;}

  //Togglestatus starts always on UNTOGGLED.
  virtual void setItemToggleAble(bool able)=0;
  void setItemThreeStepToggleAble(bool able) {
    if (able) this->setItemToggleAble(able);
    this->threeStepToggleAble = able;
  }
  virtual void setToggleValue(int toggle,bool notify=false)=0;
  void toggleItem(bool notify=false);

  int getToggleValue() {return this->toggle;}

protected:
  int itemId; 

  bool toggleAble;
  bool threeStepToggleAble;
  int toggle;
  static const char** togglepx[NTOGGLES]; 

  //itemtext manipulations
  bool boldtext,italictext;  

  const char** col0Pixmap;

private:
  static int itemCount;
};

#endif
