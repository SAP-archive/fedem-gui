// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QEvent>
#include <QTimerEvent>

#include "FFuaQtTimer.H"


FFuaTimer* FFuaTimer::create(const FFaDynCB0& cb)
{
  return new FFuaQtTimer(cb);
}


void FFuaQtTimer::start(int msecInterval, bool isSShot)
{
  this->stop();

  myMsecInterval = msecInterval;
  amISShot = isSShot;
  myTimerID = this->startTimer(myMsecInterval);
}


void FFuaQtTimer::restart()
{
  this->stop();

  myTimerID = this->startTimer(myMsecInterval);
}


void FFuaQtTimer::stop()
{
  if (myTimerID > 0)
    this->killTimer(myTimerID);

  myTimerID = -1;
}


bool FFuaQtTimer::event(QEvent *e)
{
  // Ignore non-timer events
  if (e->type() != QEvent::Timer)
    return false;

  // Ignore other all other timer events
  if (((QTimerEvent*)e)->timerId() != myTimerID)
    return false;

  // Stop single shot timer
  if (amISShot)
    this->stop();

  // Invoke callback
  myTimerCB.invoke();

  return true;
}

