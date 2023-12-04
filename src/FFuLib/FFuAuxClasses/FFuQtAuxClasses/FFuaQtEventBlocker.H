// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_QT_EVENT_BLOCKER_H
#define FFUA_QT_EVENT_BLOCKER_H

#include <QObject>

class QEvent;


/*!
  Class used to keep an eventfilter for blocking of all user input.

  Alternatives:

   o Install event filter on every widget
   o Install event filter on app, but this must have a list over nonblockables
-->o Install event filter on app, block every widget.
*/

class FFuaQtEventBlocker : public QObject
{
public :
  FFuaQtEventBlocker() : IAmBreakingBlock(false), myBlockRefCount(0) {}

  virtual bool eventFilter(QObject* receiver, QEvent* e);

  void block(bool doBlock);
  void breakBlock(bool doBreak) { IAmBreakingBlock = doBreak; }

protected:
  bool IAmBreakingBlock;
  int myBlockRefCount;
};

#endif
