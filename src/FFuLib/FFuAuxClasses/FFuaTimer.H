// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_TIMER_H
#define FFUA_TIMER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"


class FFuaTimer
{
public:
  static FFuaTimer* create(const FFaDynCB0& aDynCB);

  virtual ~FFuaTimer() {}

  virtual void start(int, bool = false) = 0;
  virtual void restart() = 0;
  virtual void stop() = 0;

  bool isActive() const { return myTimerID > 0; }
  void changeInterval(int newMsecInterval);
  int getInterval() const { return myMsecInterval; }

protected:
  FFaDynCB0 myTimerCB;
  bool amISShot;
  int myTimerID;
  int myMsecInterval;

  FFuaTimer(const FFaDynCB0& aTimerCB);

private:
  // disable copy constructor and assignment operator
  FFuaTimer(const FFuaTimer&) = delete;
  FFuaTimer& operator=(const FFuaTimer&) = delete;
};

#endif
