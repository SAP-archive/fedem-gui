// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapMech3DObjCmds.H"
#include "vpmApp/FapEventManager.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "vpmUI/FuiModes.H"
#include "vpmDB/FmRoad.H"


void FapMech3DObjCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createRevJoint");
  cmdItem->setSmallIcon(revJoint_xpm);
  cmdItem->setText("Revolute Joint");
  cmdItem->setToolTip("Revolute Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createRevJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createBallJoint");
  cmdItem->setSmallIcon(ballJoint_xpm);
  cmdItem->setText("Ball Joint");
  cmdItem->setToolTip("Ball Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createBallJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createRigidJoint");
  cmdItem->setSmallIcon(rigidJoint_xpm);
  cmdItem->setText("Rigid Joint");
  cmdItem->setToolTip("Rigid Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createRigidJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createFreeJoint");
  cmdItem->setSmallIcon(freeJoint_xpm);
  cmdItem->setText("Free Joint");
  cmdItem->setToolTip("Free Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createFreeJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createFreeJoint2");
  cmdItem->setSmallIcon(freeJoint_xpm);
  cmdItem->setText("Free Joint between Triads");
  cmdItem->setToolTip("Free Joint between existing Triads");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createFreeJointBetweenTriads));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createPrismJoint");
  cmdItem->setSmallIcon(prismJoint_xpm);
  cmdItem->setText("Prismatic Joint");
  cmdItem->setToolTip("Prismatic Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createPrismJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createPrismJoint2");
  cmdItem->setSmallIcon(prismJoint_xpm);
  cmdItem->setText("Prismatic Joint between Triads");
  cmdItem->setToolTip("Prismatic Joint between existing Triads");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createPrismJointBetweenTriads));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createCylJoint");
  cmdItem->setSmallIcon(cylJoint_xpm);
  cmdItem->setText("Cylindric Joint");
  cmdItem->setToolTip("Cylindric Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createCylJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createCylJoint2");
  cmdItem->setSmallIcon(cylJoint_xpm);
  cmdItem->setText("Cylindric Joint between Triads");
  cmdItem->setToolTip("Cylindric Joint between Triads");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createCylJointBetweenTriads));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createCamJoint");
  cmdItem->setSmallIcon(camJoint_xpm);
  cmdItem->setText("Cam Joint");
  cmdItem->setToolTip("Cam Joint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createCamJoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createGear");
  cmdItem->setSmallIcon(gear_xpm);
  cmdItem->setText("Gear");
  cmdItem->setToolTip("Gear");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createGear));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createRackPinon");
  cmdItem->setSmallIcon(rackPinon_xpm);
  cmdItem->setText("Rack-and-Pinion");
  cmdItem->setToolTip("Rack-and-Pinion");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createRackPinon));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createSpring");
  cmdItem->setSmallIcon(spring_xpm);
  cmdItem->setText("Spring");
  cmdItem->setToolTip("Spring");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createSpring));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createDamper");
  cmdItem->setSmallIcon(damper_xpm);
  cmdItem->setText("Damper");
  cmdItem->setToolTip("Damper");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createDamper));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createTriad");
  cmdItem->setSmallIcon(triad_xpm);
  cmdItem->setText("Triad");
  cmdItem->setToolTip("Triad");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createTriad));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createForce");
  cmdItem->setSmallIcon(force_xpm);
  cmdItem->setText("Force");
  cmdItem->setToolTip("Force");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createForce));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createTorque");
  cmdItem->setSmallIcon(torque_xpm);
  cmdItem->setText("Torque");
  cmdItem->setToolTip("Torque");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createTorque));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createSimpleSensor");
  cmdItem->setSmallIcon(makeSimpleSensor_xpm);
  cmdItem->setText("Simple Sensor");
  cmdItem->setToolTip("Simple Sensor");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createSimpleSensor));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createRelativeSensor");
  cmdItem->setSmallIcon(makeRelativeSensor_xpm);
  cmdItem->setText("Relative Sensor");
  cmdItem->setToolTip("Relative Sensor");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createRelativeSensor));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createSticker");
  cmdItem->setSmallIcon(sticker_xpm);
  cmdItem->setText("Sticker");
  cmdItem->setToolTip("Sticker");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createSticker));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createTire");
  cmdItem->setSmallIcon(createTire_xpm);
  cmdItem->setText("Tire");
  cmdItem->setToolTip("Tire");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createTire));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_createRoad");
  cmdItem->setSmallIcon(createRoad_xpm);
  cmdItem->setText("Road");
  cmdItem->setToolTip("Road");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::createRoad));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_pointToPointMove");
  cmdItem->setSmallIcon(pointToPointMove_xpm);
  cmdItem->setText("Smart Move");
  cmdItem->setToolTip("Smart Move");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::pointToPointMove));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_attach");
  cmdItem->setSmallIcon(attach_xpm);
  cmdItem->setText("Attach");
  cmdItem->setToolTip("Attach");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::attach));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_detach");
  cmdItem->setSmallIcon(detach_xpm);
  cmdItem->setText("Detach");
  cmdItem->setToolTip("Detach");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::detach));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapMech3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_setObjAppearance");
  cmdItem->setSmallIcon(appearance_xpm);
  cmdItem->setText("Item Appearance...");
  cmdItem->setToolTip("Item Appearance");
  cmdItem->setActivatedCB(FFaDynCB0S(FapMech3DObjCmds::setLinkAppearance));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createRevJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEREVJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createBallJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEBALLJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createRigidJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKERIGIDJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createFreeJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEFREEJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createFreeJointBetweenTriads()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEFREEJOINTBETWEENTRIADS_MODE);
}
//----------------------------------------------------------------------------
void FapMech3DObjCmds::createPrismJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEPRISMJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createPrismJointBetweenTriads()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEPRISMJOINTBETWEENTRIADS_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createCylJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKECYLJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createCylJointBetweenTriads()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKECYLJOINTBETWEENTRIADS_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createCamJoint()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKECAMJOINT_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createGear()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEGEAR_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createRackPinon()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKERACKPIN_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createSpring()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKESPRING_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createDamper()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEDAMPER_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createTriad()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKETRIAD_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createForce()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKEFORCE_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createTorque()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKETORQUE_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createSimpleSensor()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKESIMPLESENSOR_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createRelativeSensor()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKERELATIVESENSOR_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createSticker()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKESTICKER_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createTire()
{
  if (!FapLicenseManager::hasTireLicense())
    return;

  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::MAKETIRE_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::createRoad()
{
  if (!FapLicenseManager::hasTireLicense())
    return;

  if (!FapCmdsBase::hasResultsCheck()) {
    FmRoad* road = new FmRoad();
    road->connect();
    FapEventManager::permTotalSelect(road);
  }
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::pointToPointMove()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::PTPMOVE_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::attach()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::ATTACH_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::detach()
{
  if (!FapCmdsBase::hasResultsCheck())
    FuiModes::setMode(FuiModes::DETACH_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::setLinkAppearance()
{
  FuiModes::setMode(FuiModes::APPEARANCE_MODE);
}
//----------------------------------------------------------------------------

void FapMech3DObjCmds::getSensitivity(bool& isSensitive)
{
  FapCmdsBase::isModelEditable(isSensitive);
  if (isSensitive)
    FapCmdsBase::isModellerActive(isSensitive);
}
//----------------------------------------------------------------------------
