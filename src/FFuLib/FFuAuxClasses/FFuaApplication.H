// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_APPLICATION_H
#define FFUA_APPLICATION_H

class QSplashScreen;
class QTimer;


class FFuaApplication
{
public:
  static void init(int argc, char** argv, bool useGUI);

  static int getScreenHeight();
  static int getScreenWidth();

  // Event handling

  static void handlePendingEvents();
  static int mainLoop();

  // Block and unblock the GUI

  static void blockUserEvents(bool doBlock);
  static void breakUserEventBlock(bool doBreak);

  // Splash screen messages
  static bool splashMessage(const char* msg);
  static void splashScreenWindpower();
  static void splashScreenOffshore();

private:
  static bool isBlocked;

  static QSplashScreen* splashScreen;
  static QTimer*        splashTimer;
};

#endif
