// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef _FP_RDBHANDLER_H_
#define _FP_RDBHANDLER_H_

class FFuaTimer;


class FpRDBHandler
{
public:
  static void onProcessGroupStarted(int groupId);

  static void startRDBChecking();
  static void stopRDBChecking();

private:
  static void checkForNewHeaders();
  static void checkForNewData();

  static FFuaTimer* ourHeaderChangedTimer;
  static FFuaTimer* ourDataChangedTimer;
};

#endif
