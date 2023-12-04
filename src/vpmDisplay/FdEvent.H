// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_EVENT_H
#define FD_EVENT_H

#include <Inventor/nodes/SoEventCallback.h>

class SoSeparator;


class FdEvent
{
public:
  static void init();
  static void start(SoSeparator* dbRoot);

  static void addEventCB(SoEventCallbackCB* cb, void* userData = NULL);
  static void removeEventCB(SoEventCallbackCB* cb, void* userData = NULL);

protected:
  static void adminCB(void*, SoEventCallback* eventCB);
  static void examCB(void*, SoEventCallback* eventCB);

private:
  static SoEventCallback* adminCallbackNode;
  static SoEventCallback* eventCallbackNode;
};

#endif
