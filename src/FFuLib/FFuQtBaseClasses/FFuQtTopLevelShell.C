// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QEvent>
#include <QCloseEvent>
#include <QApplication>
#include <QtGui/QCursor>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"

std::map<QWidget*,QWidget*> FFuQtTopLevelShell::ourTopLevelsToBlock;


FFuQtTopLevelShell::FFuQtTopLevelShell(QWidget* parent,
				       int xpos, int ypos,
				       int width,int height,
				       const char* title,
				       const char* name,
				       Qt::WindowFlags f)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name,f)
{
  this->setWindowTitle(title);
}


void FFuQtTopLevelShell::popUp()
{
  this->show();
  this->raise();
}


void FFuQtTopLevelShell::refresh()
{
  if (this->isVisible()) this->repaint();
}


void FFuQtTopLevelShell::iconify()
{
  this->iconify();
}


void FFuQtTopLevelShell::deiconify()
{
  this->show();
  this->raise();
}


void FFuQtTopLevelShell::showTLSNormal()
{
  this->showNormal();
  this->setFocus();
}


void FFuQtTopLevelShell::setTitle(const char* title)
{
  this->setWindowTitle(title);
}


void FFuQtTopLevelShell::blockThis(bool everything)
{
  ourTopLevelsToBlock[this] = NULL;
}


void FFuQtTopLevelShell::unBlockThis()
{
  ourTopLevelsToBlock.erase(this);
}


void FFuQtTopLevelShell::closeEvent(QCloseEvent* e)
{
  if (this->onClose())
    e->accept();
  else
    e->ignore();
}


void FFuQtTopLevelShell::initQtBlocking()
{
  static Blocker* eventFilter = new Blocker();
  qApp->installEventFilter(eventFilter);
}


bool FFuQtTopLevelShell::filterEventsDueToBlocking(QObject* receiver, QEvent* e)
{
  int type = e->type();
  bool doBlockEvent = false;

  if ((type == QEvent::MouseButtonPress ||
       type == QEvent::MouseButtonRelease ||
       type == QEvent::Timer ||
       type == QEvent::MouseButtonDblClick ||
       type == QEvent::MouseMove ||
       type == QEvent::KeyPress ||
       type == QEvent::KeyRelease ||
       type == QEvent::FocusIn ||
       type == QEvent::FocusOut ||
       type == QEvent::Enter ||
       type == QEvent::Leave ||
       type == QEvent::Close ||
       type == QEvent::Shortcut ||
       type == QEvent::DragMove ||
       type == QEvent::DragLeave ||
       type == QEvent::Drop ||
       type == QEvent::None) && receiver->isWidgetType())
  {
    QWidget* w = (QWidget*)receiver;
    std::map<QWidget*,QWidget*>::const_iterator it = ourTopLevelsToBlock.find(w->topLevelWidget());
    if (it != ourTopLevelsToBlock.end())
    {
      if (w == it->second)
        ; // Event hit NoblockWidget, don't block.
      else while ((w = w->parentWidget()))
        if (w == it->second)
          break; // Event hit child of noblock widget, don't block

      doBlockEvent = w == NULL;
    }

    // Set cursor :

    if (!QApplication::overrideCursor() && doBlockEvent)
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    if (QApplication::overrideCursor() && !doBlockEvent)
      QApplication::restoreOverrideCursor();
  }

  return doBlockEvent;
}
