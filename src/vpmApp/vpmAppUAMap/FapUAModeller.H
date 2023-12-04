// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_MODELLER_H
#define FAP_UA_MODELLER_H

class FuiModeller;
class FaVec3;


//! \brief Mapper class between FuiModeller and the application.

class FapUAModeller
{
public:
  static void init(FuiModeller* aFuiModeller);

  static FuiModeller* getFuiModeller() { return ourFuiModeller; }

  // Mode and state interface

  static void updateMode();
  static void updateState(int newState);
  static void cancel();

  // 3D point select UI interface

  static void onPointChanged(const FaVec3& newPoint, bool isGlobal);
  static void onPointRefChanged(bool isGlobal);

  static void updatePointUI();
  static void setPointIdx(int idx) { whichPoint = idx; }
  static void setGlobalOnly();
  static void setLocal();
  static void showPointUI(bool doShow);

  // Animation control:

  static void onAllFramesToggle(bool onOrOff);
  static void onSpeedScaleChange(int value);

  static void onAnimationPress(int action);
  static void onRealTimePress();

  static void onAnimTypeChange(int animationType);
  static void closeAnimation();

private:
  // 3D point select UI interface
  static int          whichPoint;
  static FuiModeller* ourFuiModeller;
};

#endif
