// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_VIEW_CTRL_CMDS_H
#define FAP_VIEW_CTRL_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapViewCtrlCmds : public FapCmdsBase
{
private:
  static void init();

  static void zoomAll();
  static void zoomTo();
  static void getZoomToSensitivity(bool& isSensitive);

  //graph
  static void zoomWindow();
  static void zoomAllInWindow();
  static void zoomIn();
  static void zoomOut();

  static void shiftLeft();
  static void shiftRight();
  static void shiftUp();
  static void shiftDown();

  //mech
  static void solidView(bool show);
  static void getSolidViewToggle(bool& toggle);

  static void solidViewNoEdge(bool show);
  static void getSolidViewNoEdgeToggle(bool& toggle);

  static void flatColorView(bool setFlat);
  static void getFlatColorToggle(bool& isFlat);

  static void topLightOnly(bool setFlat);
  static void getTopLightOnlyToggle(bool& isFlat);

  static void lineView(bool show);
  static void getLineViewToggle(bool& toggle);

  static void perspectiveView(bool show);
  static void getPerspectiveViewToggle(bool& toggle);

  static void parallellView(bool show);
  static void getParallellViewToggle(bool& toggle);

  static void isometricView();

  static void symbolSize(double newSize);
  static void symbolSize0001() { symbolSize(0.001); }
  static void symbolSize001()  { symbolSize(0.01); }
  static void symbolSize01()   { symbolSize(0.1); }
  static void symbolSize1()    { symbolSize(1.0); }
  static void symbolSize10()   { symbolSize(10.0); }

private:
  friend class FFaInitialisation<FapViewCtrlCmds>;
};

static FFaInitialisation<FapViewCtrlCmds> FapViewCtrlCmds_Init;

#endif
