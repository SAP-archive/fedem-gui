// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  \class FFuaTimer FFuaTimer.H
  \brief A class with a high precision timer, both single and multi-shot.

  Callbacks are issued as normal dynamic callbacks, using FFaDynCB0.
  A timer is created using the FFuaTimer::create factory, as
  shown in the example below:

  \code
  class Foo
  {
  public:
    void timeOutMethod() { cout << "A timeout" << std::endl; }
  }

  void bar()
  {
    ....
    FFuaTimer *myTimer = FFuaTimer::create(FFaDynCB0M(Foo, timeOutMethod));
    myTimer->start(1000) // timeout every 1 second
    ....
  }
  \endcode

  \author Jens Lien
*/

#include "FFuLib/FFuAuxClasses/FFuaTimer.H"


FFuaTimer::FFuaTimer(const FFaDynCB0& aDynCB) : myTimerCB(aDynCB)
{
  amISShot = false;
  myMsecInterval = 50;
  myTimerID = -1;
}


/*!
  Changes the timeout interval. If the timer is active, the timer
  is restarted with the new interval
*/
void FFuaTimer::changeInterval(int msecInterval)
{
  if (this->isActive())
  {
    // TODO: Try to align the next timeout with the new interval
    this->stop();
    this->start(msecInterval, amISShot);
  }

  myMsecInterval = msecInterval;
}


/*!
  \fn virtual void FFuaTimer::start(int msecInterval, bool isSShot = false)
  Starts the timer.
  \param msecInterval The timer interval in milliseconds
  \param isSShot Sets the timer in single-shot mode.
*/
