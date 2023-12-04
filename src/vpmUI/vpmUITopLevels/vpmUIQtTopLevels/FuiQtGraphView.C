// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QMdiSubWindow>
#include <QtGui/QPixmap>
#include <QIcon>
#include <QEvent>

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtGraphView.H"

extern const char* graph_xpm[];

//----------------------------------------------------------------------------

//  Qt implementation of static create method in FuiGraphViewTLS:
FuiGraphView* FuiGraphViewTLS::create(FFuComponentBase* parent,
                                      int xpos, int ypos,
                                      int width, int height,
                                      const char* title,
                                      const char* name)
{
  FuiGraphViewTLS* tls = new FuiQtGraphViewTLS(dynamic_cast<QWidget*>(parent),
                                               xpos,ypos,width,height,title,name);
  tls->popUp();
  return tls->getGraphViewComp();
}
//----------------------------------------------------------------------------

FuiQtGraphViewTLS::FuiQtGraphViewTLS(QWidget* parent,
                                     int xpos, int ypos,
                                     int width, int height,
                                     const char* title,
                                     const char* name)
  : FFuQtMDIWindow(parent,xpos,ypos,width,height,title,name)
{
  this->graphView = new FuiQtGraphView(this);

  QPixmap icon(graph_xpm);
  myQtSubWindow->setWindowIcon(QIcon(icon));

  this->setFocusProxy(dynamic_cast<QWidget*>(this->graphView));

  FFuUAExistenceHandler::invokeCreateUACB(this);

  this->graphView->updateSession();
}
//----------------------------------------------------------------------------

FuiQtGraphView::FuiQtGraphView(QWidget* parent, const char* name)
  : FFuQt2DPlotter(parent,name)
{
  this->setFocusPolicy(Qt::StrongFocus);

  this->initWidgets();

  //this->onPoppedUpFromMem();//hack -> causes crash...
}
//----------------------------------------------------------------------------

void FuiQtGraphView::setVisible(bool visible)
{
  //TODO isVisible/isMinimized doesn't work on a mdi window yet,
  //hack :onPoppedUpFrom/ToMem on construction/destr
  //bool wasvisible = this->isVisible();
  this->FFuQt2DPlotter::setVisible(visible);
  /*
  if (!wasvisible && visible)
    this->onPoppedUpFromMem();
  else if (wasvisible && !visible)
    this->onPoppedDownToMem();
  */
}
//----------------------------------------------------------------------------

bool FuiQtGraphView::event(QEvent* e)
{
  bool ret = this->FFuQt2DPlotter::event(e);

  switch (e->type()) {
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
