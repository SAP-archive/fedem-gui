// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QEvent>
#include <QDropEvent>

#include "FFuLib/FFuQtComponents/FFuQtListViewItem.H"
#include "FuiQtItemsListView.H"

//----------------------------------------------------------------------------

FuiQtItemsListView::FuiQtItemsListView(QWidget* parent, const char* name)
  : FFuQtListView(parent,1,name)
{
  connect(this, SIGNAL(dropped(QDropEvent*)),
          this, SLOT(onDropped(QDropEvent*)));

  setStyleSheet("selection-color: white;"
                "selection-background-color: #3399ff;");
}
//----------------------------------------------------------------------------

void FuiQtItemsListView::setVisible(bool visible)
{
  bool wasvisible = this->isVisible();

  this->FFuQtListView::setVisible(visible);

  if (!wasvisible && visible)
    this->onPoppedUpFromMem();
  else if (wasvisible && !visible)
    this->onPoppedDownToMem();
}
//----------------------------------------------------------------------------

bool FuiQtItemsListView::event(QEvent* e)
{
  bool ret = this->FFuQtListView::event(e);

  switch (e->type())
  {
  case QEvent::Show:
    this->onPoppedUp();
    return true;
  case QEvent::Hide:
    this->onPoppedDown();
    return true;
  default:
    break;
  }

  return ret;
}
//----------------------------------------------------------------------------

void FuiQtItemsListView::onDropped(QDropEvent* e)
{
  Q3ListViewItem* dropItem = this->itemAt(this->contentsToViewport(e->pos()));
  FFuQtListViewItem* dropItemFFu = dynamic_cast<FFuQtListViewItem*>(dropItem);

  int itemId = dropItemFFu ? dropItemFFu->getItemId() : -1;
  this->droppedCB.invoke(itemId, e->dropAction() == Qt::CopyAction, e);
}
