// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_MAIN_WIN_CMDS_H
#define FAP_MAIN_WIN_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapMainWinCmds : public FapCmdsBase
{
private:
  static void init();

  static void showModelManager(bool show);
  static void getModelManagerToggle(bool& toggle);

  static void showProperties(bool show);
  static void getPropertiesToggle(bool& toggle);

  static void showStdToolBar(bool show);
  static void getStdToolBarToggle(bool& toggle);

  static void showWindowsToolBar(bool show);
  static void getWindowsToolBarToggle(bool& toggle);

  static void showSolveToolBar(bool show);
  static void getSolveToolBarToggle(bool& toggle);

  static void showViewCtrlToolBar(bool show);
  static void getViewCtrlToolBarToggle(bool& toggle);

  static void showThreeDViewsToolBar(bool show);
  static void getThreeDViewsToolBarToggle(bool& toggle);

  static void showMechCreateToolBar(bool show);
  static void getMechCreateToolBarToggle(bool& toggle);

  static void showMechModellingToolsToolBar(bool show);
  static void getMechModellingToolsToolBarToggle(bool& toggle);

  static void showCtrlCreateToolBar(bool show);
  static void getCtrlCreateToolBarToggle(bool& toggle);

  static void showCtrlModellingToolsToolBar(bool show);
  static void getCtrlModellingToolsToolBarToggle(bool& toggle);

  static void showMechWindToolBar(bool show);
  static void getMechWindToolBarToggle(bool& toggle);

private:
  friend class FFaInitialisation<FapMainWinCmds>;
};

static FFaInitialisation<FapMainWinCmds> FapMainWinCmds_Init;

#endif
