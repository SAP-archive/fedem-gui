// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_FUNCTION_CMDS_H
#define FAP_FUNCTION_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapFunctionCmds : public FapCmdsBase
{
public:
  static void getConvertFuncSensitivity(bool& sens, bool& sprDaSens, bool& driveFileSens);

private:
  static void init();

  static void createSpringCharTrans();
  static void createSpringCharRot();

  static void createSprTransStiffFunc();
  static void createSprTransForceFunc();
  static void createSprRotStiffFunc();
  static void createSprRotTorqueFunc();

  static void createDaTransCoeffFunc();
  static void createDaTransForceFunc();
  static void createDaRotCoeffFunc();
  static void createDaRotTorqueFunc();

  static void createGeneralFunction();
  static void createDriveFile();
  static void createRoadFunction();
  static void createWaveFunction();
  static void createCurrFunction();

  static void convertToSprTransStiffFunc();
  static void convertToSprTransForceFunc();
  static void convertToSprRotStiffFunc();
  static void convertToSprRotTorqueFunc();

  static void convertToDaTransCoeffFunc();
  static void convertToDaTransForceFunc();
  static void convertToDaRotCoeffFunc();
  static void convertToDaRotTorqueFunc();

  static void convertToGeneralFunction();
  static void convertToRoadFunction();
  static void convertToDriveFile();

  friend class FFaInitialisation<FapFunctionCmds>;
};

static FFaInitialisation<FapFunctionCmds> FapFunctionCmds_Init;

#endif
