// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_LIST_VIEW_ITEM_H
#define FFU_QT_LIST_VIEW_ITEM_H

#include "FFuLib/FFuListViewItem.H"
#include <Qt3Support/Q3ListView>


class FFuQtListView;

class FFuQtListViewItem : public Q3ListViewItem, public FFuListViewItem
{
public:
  // If parent=0, the item is created at top level in the list view
  // If after=0 the item is inserted first in parents list
  FFuQtListViewItem(FFuQtListView* parent,FFuQtListViewItem* after,const char* label);
  FFuQtListViewItem(FFuQtListView* parent,FFuQtListViewItem* after,FFuQtListViewItem* original);
  FFuQtListViewItem(FFuQtListViewItem* parent,FFuQtListViewItem* after,const char* label);
  FFuQtListViewItem(FFuQtListViewItem* parent,FFuQtListViewItem* after,FFuQtListViewItem* original);
  virtual ~FFuQtListViewItem() {}
  virtual void copyPixmaps(FFuListViewItem* original);

  virtual void  setItemText(int col,const char* text);
  virtual char* getItemText(int col=0);
  virtual void setItemTextBold(bool bold=true);
  virtual void setItemTextItalic(bool italic=true);
  virtual void setItemImage(int col,const char **pixmap);
  virtual bool isItemSelected();
  virtual int  getDepth();
  virtual void setItemSelectable(bool enable);

  virtual FFuListView*     getListView();
  virtual FFuListViewItem* getParentItem();
  virtual FFuListViewItem* getFirstChildItem();
  virtual FFuListViewItem* getLastChildItem();
  virtual FFuListViewItem* getNextSiblingItem();
  virtual int              getNSiblings();
  virtual int              getNChildren();

  virtual void setItemToggleAble(bool able);
  virtual void setToggleValue(int toggle,bool notify=false);

  virtual void setItemDropable(bool enable);
  virtual void setItemDragable(bool enable);

private:
  //reimpl from QListItem
  virtual void setSelected(bool selected);
  virtual void paintCell(QPainter* p,const QColorGroup& cg,int column,int width,int align);
  virtual void paintFocus(QPainter* p,const QColorGroup& cg,const QRect& r);
};

#endif
