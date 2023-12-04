// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPMECH3DOBJCMDS_H
#define FAPMECH3DOBJCMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapMech3DObjCmds : public FapCmdsBase
{
private:
  static void init();

  static void createRevJoint();
  static void createBallJoint();
  static void createRigidJoint();
  static void createFreeJoint();
  static void createFreeJointBetweenTriads();
  static void createPrismJoint();
  static void createPrismJointBetweenTriads();
  static void createCylJoint();
  static void createCylJointBetweenTriads();
  static void createCamJoint();
  static void createGear();
  static void createRackPinon();
  static void createSpring();
  static void createDamper();
  static void createTriad();
  static void createForce();
  static void createTorque();
  static void createSimpleSensor();
  static void createRelativeSensor();
  static void createSticker();
  static void createTire();
  static void createRoad();

  static void pointToPointMove();
  static void attach();
  static void detach();
  static void setLinkAppearance(); // move to FapToolsCmds if preselect

  static void getSensitivity(bool& isSensitive);

  friend class FFaInitialisation<FapMech3DObjCmds>;
};

static FFaInitialisation<FapMech3DObjCmds> FapMech3DObjCmds_Init;

#endif
