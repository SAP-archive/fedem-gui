// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "FFuLib/FFuQtComponents/FFuQtListView.H"
#include "FFuLib/FFuAuxClasses/FFuQtAuxClasses/FFuaQtPixmapCache.H"
#include "FFuLib/FFuQtComponents/FFuQtListViewItem.H"


//////////////////////////////////////////////////////////////////////////////
// FFuQtListViewItem Methods

FFuQtListViewItem::FFuQtListViewItem(FFuQtListView* parent,FFuQtListViewItem* after,const char* label)
  : Q3ListViewItem(parent,after)
{
  this->setItemText(0,label);
}
//----------------------------------------------------------------------------

FFuQtListViewItem::FFuQtListViewItem(FFuQtListView* parent,FFuQtListViewItem* after,
				     FFuQtListViewItem* original)
  : Q3ListViewItem(parent,after)
{
  this->copyData(original);
}
//----------------------------------------------------------------------------

FFuQtListViewItem::FFuQtListViewItem(FFuQtListViewItem* parent,FFuQtListViewItem* after,const char* label)
  : Q3ListViewItem(parent,after)
{
  this->setItemText(0,label);
}
//----------------------------------------------------------------------------

FFuQtListViewItem::FFuQtListViewItem(FFuQtListViewItem* parent,FFuQtListViewItem* after,
				     FFuQtListViewItem* original)
  : Q3ListViewItem(parent,after)
{
  this->copyData(original);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::copyPixmaps(FFuListViewItem* original)
{
  for (int i = 0; i < this->getListView()->getNColumns(); i++)
  {
    Q3ListViewItem* qitem = dynamic_cast<Q3ListViewItem*>(original);
    if (qitem)
    {
      const QPixmap* pm = qitem->pixmap(i);
      if (pm) this->setPixmap(i,QPixmap(*pm));
    }
  }
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemText(int col,const char* text)
{
  this->setText(col,text);
}
//----------------------------------------------------------------------------

char* FFuQtListViewItem::getItemText(int col)
{
  return ((char*) ((const char*) this->text(col)));
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemTextBold(bool bold)
{
  this->boldtext = bold;
  this->repaint();
}

//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemTextItalic(bool italic)
{
  this->italictext = italic;
  this->repaint();
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemImage(int col,const char **pixmap)
{
  this->setPixmap(col, FFuaQtPixmapCache::getPixmap(pixmap));
}
//----------------------------------------------------------------------------

bool FFuQtListViewItem::isItemSelected()
{
  return this->isSelected();
}
//----------------------------------------------------------------------------

int FFuQtListViewItem::getDepth()
{
  return this->depth();
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemSelectable(bool enable)
{
  this->setSelectable(enable);
}
//----------------------------------------------------------------------------

FFuListView* FFuQtListViewItem::getListView()
{
  return dynamic_cast<FFuListView*>(this->listView());
}
//----------------------------------------------------------------------------

FFuListViewItem* FFuQtListViewItem::getParentItem()
{
  return dynamic_cast<FFuListViewItem*>(this->parent());
}
//----------------------------------------------------------------------------

FFuListViewItem* FFuQtListViewItem::getFirstChildItem()
{
  return dynamic_cast<FFuListViewItem*>(this->firstChild());
}
//----------------------------------------------------------------------------

FFuListViewItem* FFuQtListViewItem::getNextSiblingItem()
{
  return dynamic_cast<FFuListViewItem*>(this->nextSibling());
}
//----------------------------------------------------------------------------

FFuListViewItem* FFuQtListViewItem::getLastChildItem()
{
  Q3ListViewItem* item = this->firstChild();
  while (item && item->nextSibling())
    item = item->nextSibling();

  return dynamic_cast<FFuListViewItem*>(item);
}
//----------------------------------------------------------------------------

int FFuQtListViewItem::getNSiblings()
{
  if (this->parent())
    return this->parent()->childCount();
  else
    return this->listView()->childCount();
}
//----------------------------------------------------------------------------

int FFuQtListViewItem::getNChildren()
{
  return this->childCount();
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemToggleAble(bool able)
{
  if (this->col0Pixmap) return;
  if (able == this->toggleAble) return;

  this->toggleAble = able;

  if (this->toggleAble)
    this->setToggleValue(this->toggle,false);
  else {
    this->setPixmap(0, QPixmap(this->col0Pixmap));
    this->toggle = 0;
    this->threeStepToggleAble = false;
  }
}
//----------------------------------------------------------------------------

void  FFuQtListViewItem::setToggleValue(int toggleVal,bool notify)
{
  if (this->col0Pixmap) return;
  if (toggleVal >= NTOGGLES) return;

  if (toggleVal == HALFTOGGLED && !this->threeStepToggleAble)
    this->toggle = TOGGLED;
  else
    this->toggle = toggleVal;

  this->setItemToggleAble(true);

  this->setPixmap(0,QPixmap(FFuListViewItem::togglepx[this->toggle]));

  if (notify)
    this->getListView()->onListItemToggled(this,this->toggle);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setSelected(bool isSelected)
{
  this->Q3ListViewItem::setSelected(isSelected);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::paintCell(QPainter* p,const QColorGroup& cg,int column,int width,int align)
{
  QFont newfont(p->font());
  newfont.setBold(this->boldtext);
  newfont.setItalic(this->italictext);
  p->setFont(newfont);

  this->Q3ListViewItem::paintCell(p,cg,column,width,align);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::paintFocus(QPainter* p,const QColorGroup& cg,const QRect& r)
{
  this->Q3ListViewItem::paintFocus(p,cg,r);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemDropable(bool enable)
{
  this->setDropEnabled(enable);
}
//----------------------------------------------------------------------------

void FFuQtListViewItem::setItemDragable(bool enable)
{
  this->setDragEnabled(enable);
}
