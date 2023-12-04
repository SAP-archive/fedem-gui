// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_TOOLS_CMDS_H
#define FAP_TOOLS_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapToolsCmds : public FapCmdsBase
{
public:
  static void setFileAssociations();
  static bool setFileAssociationsEx();
  static bool checkFileAssociations();

  static bool getAddonExe(int index = 0, char* pExePath = NULL, char* pExeName = NULL);

private:
  static void init();

  static void showModeler();
  static void showCtrlEditor();
  static void ctrlGridSnap();

  static void preferences();
  static void viewFilter();
  static void outputList();
  static void resultFileBrowser();
  static void linkRamSettings();
  static void modelPreferences();
  static void seaEnvironment();
  static void airEnvironment();
  static void airfoilDefinition();
  static void bladeDefinition();
  static void turbineAssembly();
  static void turbineTower();
  static void beamstringPair();
  static void objectBrowser();
  static void plugins();
  static void eventDefinition();
  static void measureDistance();
  static void measureAngle();
  
  static void addon0() { addonLaunch(0); }
  static void addon1() { addonLaunch(1); }
  static void addon2() { addonLaunch(2); }
  static void addon3() { addonLaunch(3); }
  static void addon4() { addonLaunch(4); }
  static void addon5() { addonLaunch(5); }
  static void addon6() { addonLaunch(6); }
  static void addon7() { addonLaunch(7); }
  static void addon8() { addonLaunch(8); }
  static void addon9() { addonLaunch(9); }
  static void addon10() { addonLaunch(10); }
  static void addon11() { addonLaunch(11); }
  static void addon12() { addonLaunch(12); }
  static void addon13() { addonLaunch(13); }
  static void addon14() { addonLaunch(14); }
  static void addon15() { addonLaunch(15); }
  static void addon16() { addonLaunch(16); }
  static void addon17() { addonLaunch(17); }
  static void addon18() { addonLaunch(18); }
  static void addon19() { addonLaunch(19); }
  static void addon20() { addonLaunch(20); }
  static void addon21() { addonLaunch(21); }
  static void addon22() { addonLaunch(22); }
  static void addon23() { addonLaunch(23); }
  static void addon24() { addonLaunch(24); }
  static void addon25() { addonLaunch(25); }
  static void addon26() { addonLaunch(26); }
  static void addon27() { addonLaunch(27); }
  static void addon28() { addonLaunch(28); }
  static void addon29() { addonLaunch(29); }
  static void addon30() { addonLaunch(30); }
  static void addon31() { addonLaunch(31); }
  static void addon32() { addonLaunch(32); }
  static void addon33() { addonLaunch(33); }
  static void addon34() { addonLaunch(34); }
  static void addon35() { addonLaunch(35); }
  static void addon36() { addonLaunch(36); }
  static void addon37() { addonLaunch(37); }
  static void addon38() { addonLaunch(38); }
  static void addon39() { addonLaunch(39); }
  static void addonLaunch(int index);

  static void getTurbineTowerSensitivity(bool& isSensitive);

  friend class FFaInitialisation<FapToolsCmds>;
};

static FFaInitialisation<FapToolsCmds> _Init;

#endif
