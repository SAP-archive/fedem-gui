// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_EDIT_STRAIN_ROSETTE_NODES_CMD_H
#define FAP_EDIT_STRAIN_ROSETTE_NODES_CMD_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class SoEventCallback;
class FmStrainRosette;


class FapEditStrainRosetteNodesCmd : public FapCmdsBase
{
private:
  static void init();

  static void getSensitivity(bool& isSensitive);

  static void setState(int newState);
  static void eventCB(void*, SoEventCallback* eventCallbackNode);

  static void setStrainRosetteNodes();

public:
  static void editStrainRosetteNodes();

  static void enterMode();
  static void cancelMode();
  static void done();

private:
  static int ourState;
  static FmStrainRosette* ourStrainRosette;

  friend class FFaInitialisation<FapEditStrainRosetteNodesCmd>;
};

static FFaInitialisation<FapEditStrainRosetteNodesCmd> FapEditStrainRosetteNodesCmd_Init;

#endif
