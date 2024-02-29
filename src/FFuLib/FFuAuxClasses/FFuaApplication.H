// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_APPLICATION_H
#define FFUA_APPLICATION_H


namespace FFuaApplication
{
  // Note: argc must be passed as reference
  // to avoid crash in Qt6 for Release build on Linux
  void init(int& argc, char** argv, bool useGUI);

  int getScreenHeight();
  int getScreenWidth();

  // Event handling
  void handlePendingEvents();
  int mainLoop();

  // Block and unblock the GUI
  void blockUserEvents(bool doBlock);
  void breakUserEventBlock(bool doBreak);

  // Splash screen messages
  bool splashMessage(const char* msg);
  void splashScreenWindpower();
  void splashScreenOffshore();
}

#endif
