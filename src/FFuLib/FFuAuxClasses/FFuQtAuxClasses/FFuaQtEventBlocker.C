// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QCursor>

#include "FFuaQtEventBlocker.H"


void FFuaQtEventBlocker::block(bool doBlock)
{
  if (doBlock)
  {
    if (++myBlockRefCount == 1) // Start blocking
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  }
  else if (myBlockRefCount > 0)
  {
    if (--myBlockRefCount == 0) // Open blocked UI
      QApplication::restoreOverrideCursor();
  }
}


bool FFuaQtEventBlocker::eventFilter(QObject* receiver, QEvent* e)
{
  if (myBlockRefCount && !IAmBreakingBlock && receiver->isWidgetType())
    switch (e->type()) {
      case QEvent::MouseMove:
      case QEvent::Enter:
      case QEvent::Leave:
      case QEvent::MouseButtonPress:
      case QEvent::MouseButtonRelease:
      case QEvent::MouseButtonDblClick:
      case QEvent::FocusIn:
      case QEvent::FocusOut:
      case QEvent::KeyPress:
      case QEvent::KeyRelease:
      case QEvent::Close:
      case QEvent::Shortcut:
      case QEvent::DragMove:
      case QEvent::DragLeave:
      case QEvent::Drop:
      case QEvent::None:
        return true;
      default:
        break;
    }

  return false;
}
