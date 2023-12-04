// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_UA_FINISH_HANDLER_H
#define FFU_UA_FINISH_HANDLER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"


class FFuUAFinishHandler
{
public:
  FFuUAFinishHandler() {}
  virtual ~FFuUAFinishHandler() {}

// Operations  
public:
  // Callbacks are set by FapUAFinishHandler
  void setFinishedCB(FFaDynCB0 dynCB)
    {this->finishedCB = dynCB;}

protected:
  // This callback should be invoked when the ui has finished its user dialog,
  // Usually, the effect is that the ui disappers.
  bool invokeFinishedCB();
  
private:
  FFaDynCB0 finishedCB;
};

////////////////////////////////////////////////////////////////////////

#endif
