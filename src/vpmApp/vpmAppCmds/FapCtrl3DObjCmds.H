// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPCTRL3DOBJCMDS_H
#define FAPCTRL3DOBJCMDS_H
#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class FapCtrl3DObjCmds: public FapCmdsBase
{
// Operations
private:
  static void init();

  // creation
  static void createInput();
  static void createOutput();

  static void createAmplifier();
  static void createPower();

  static void createComparator();
  static void createAdder();
  static void createMultiplyer();

  static void createIntegrator();
  static void createLimDerivator();

  static void createTimeDelay();
  static void createSampleHold();

  static void createLogicalSwitch();
  static void createLimitation();

  static void createDeadZone();
  static void createHysteresis();

  static void createPid();
  static void createPi();
  static void createPd();

  static void createPlimIlimD();
  static void createPIlimD();
  static void createPlimI();
  static void createPlimD();

  static void createRealPole();
  static void createCompConjPole();

  static void create1ordTF();
  static void create2ordTF();

  // operation
  static void rotate();
  static void addPoint();
  static void removePoint();

  //misc
  static void ctrlCreate(int elemType);

  // Sensitivity :
  static void getSensitivity(bool & isSensitive);

// Attributes
private:
  friend class FFaInitialisation<FapCtrl3DObjCmds>;
};

static FFaInitialisation<FapCtrl3DObjCmds> FapCtrl3DObjCmdsInit;



/////////////////////////////////////////////////////////////////////////////

#endif




