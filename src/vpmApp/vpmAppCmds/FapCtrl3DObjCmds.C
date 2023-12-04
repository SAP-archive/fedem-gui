// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapCtrl3DObjCmds.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "vpmUI/FuiCtrlModes.H"
#include "vpmDB/FmControlAdmin.H"
#include "vpmDB/FmcInput.H"
#include "vpmDB/FmcOutput.H"
#include "vpmDB/FmcElements.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdCtrlDB.H"
#include <Inventor/SbVec2f.h>
#include <Inventor/SbVec3f.h>
#endif

//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::init()
{
  FFuaCmdItem* cmdItem = 0;

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createInput");
  cmdItem->setSmallIcon(ctrlElemIn_xpm);
  cmdItem->setText("Input");
  cmdItem->setToolTip("Input");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createInput));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createOutput");
  cmdItem->setSmallIcon(ctrlElemOut_xpm);
  cmdItem->setText("Output");
  cmdItem->setToolTip("Output");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createOutput));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createAmplifier");
  cmdItem->setSmallIcon(ctrlAmplifier_xpm);
  cmdItem->setText("Amplifier");
  cmdItem->setToolTip("Amplifier");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createAmplifier));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPower");
  cmdItem->setSmallIcon(ctrlPower_xpm);
  cmdItem->setText("Power");
  cmdItem->setToolTip("Power");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPower));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createComparator");
  cmdItem->setSmallIcon(ctrlComparator_xpm);
  cmdItem->setText("Comparator");
  cmdItem->setToolTip("Comparator");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createComparator));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createAdder");
  cmdItem->setSmallIcon(ctrlAdder_xpm);
  cmdItem->setText("Adder");
  cmdItem->setToolTip("Adder");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createAdder));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createMultiplyer");
  cmdItem->setSmallIcon(ctrlMultiplier_xpm);
  cmdItem->setText("Multiplier");
  cmdItem->setToolTip("Multiplier");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createMultiplyer));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createIntegrator");
  cmdItem->setSmallIcon(ctrlIntegrator_xpm);
  cmdItem->setText("Integrator");
  cmdItem->setToolTip("Integrator");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createIntegrator));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createLimDerivator");
  cmdItem->setSmallIcon(ctrlLimDerivator_xpm);
  cmdItem->setText("Derivator");
  cmdItem->setToolTip("Derivator");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createLimDerivator));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createTimeDelay");
  cmdItem->setSmallIcon(ctrlTimeDelay_xpm);
  cmdItem->setText("Delay");
  cmdItem->setToolTip("Delay");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createTimeDelay));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createSampleHold");
  cmdItem->setSmallIcon(ctrlSampleHold_xpm);
  cmdItem->setText("Sample and Hold");
  cmdItem->setToolTip("Sample and Hold");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createSampleHold));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createLogicalSwitch");
  cmdItem->setSmallIcon(ctrlLogicalSwitch_xpm);
  cmdItem->setText("Logic Switch");
  cmdItem->setToolTip("Logic Switch");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createLogicalSwitch));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createLimitation");
  cmdItem->setSmallIcon(ctrlLimitation_xpm);
  cmdItem->setText("Limiter");
  cmdItem->setToolTip("Limiter");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createLimitation));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createDeadZone");
  cmdItem->setSmallIcon(ctrlDeadZone_xpm);
  cmdItem->setText("Dead Zone");
  cmdItem->setToolTip("Dead Zone");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createDeadZone));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createHysteresis");
  cmdItem->setSmallIcon(ctrlHysteresis_xpm);
  cmdItem->setText("Hysteresis");
  cmdItem->setToolTip("Hysteresis");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createHysteresis));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPid");
  cmdItem->setSmallIcon(ctrlPid_xpm);
  cmdItem->setText("PID Controller");
  cmdItem->setToolTip("PID Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPid));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPi");
  cmdItem->setSmallIcon(ctrlPi_xpm);
  cmdItem->setText("PI Controller");
  cmdItem->setToolTip("PI Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPi));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPd");
  cmdItem->setSmallIcon(ctrlPd_xpm);
  cmdItem->setText("PD Controller");
  cmdItem->setToolTip("PD Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPd));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPlimIlimD");
  cmdItem->setSmallIcon(ctrlPlimIlimD_xpm);
  cmdItem->setText("P+lim I+lim D Controller");
  cmdItem->setToolTip("P+lim I+lim D Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPlimIlimD));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPIlimD");
  cmdItem->setSmallIcon(ctrlPIlimD_xpm);
  cmdItem->setText("PI+lim D Controller");
  cmdItem->setToolTip("PI+lim D Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPIlimD));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPlimI");
  cmdItem->setSmallIcon(ctrlPlimI_xpm);
  cmdItem->setText("P+lim I Controller");
  cmdItem->setToolTip("P+lim I Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPlimI));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createPlimD");
  cmdItem->setSmallIcon(ctrlPlimD_xpm);
  cmdItem->setText("P+lim D Controller");
  cmdItem->setToolTip("P+lim D Controller");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createPlimD));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createRealPole");
  cmdItem->setSmallIcon(ctrlRealPole_xpm);
  cmdItem->setText("Real Pole");
  cmdItem->setToolTip("Real Pole");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createRealPole));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_createCompConjPole");
  cmdItem->setSmallIcon(ctrlCompConjPole_xpm);
  cmdItem->setText("Complex Conjungate Poles");
  cmdItem->setToolTip("Complex Conjungate Poles");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::createCompConjPole));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_create1ordTF");
  cmdItem->setSmallIcon(ctrl1ordTF_xpm);
  cmdItem->setText("1st Order Transfer Function");
  cmdItem->setToolTip("1st Order Transfer Function");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::create1ordTF));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_create2ordTF");
  cmdItem->setSmallIcon(ctrl2ordTF_xpm);
  cmdItem->setText("2nd Order Transfer Function");
  cmdItem->setToolTip("2nd Order Transfer Function");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::create2ordTF));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_rotate");
  cmdItem->setSmallIcon(ctrlRotate_xpm);
  cmdItem->setText("Flip Element Direction");
  cmdItem->setToolTip("Flip Element Direction");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::rotate));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_addPoint");
  cmdItem->setSmallIcon(ctrlAddPoint_xpm);
  cmdItem->setText("Add Breakpoint");
  cmdItem->setToolTip("Add Breakpoint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::addPoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl3DObj_removePoint");
  cmdItem->setSmallIcon(ctrlRemovePoint_xpm);
  cmdItem->setText("Remove Breakpoint");
  cmdItem->setToolTip("Remove Breakpoint");
  cmdItem->setActivatedCB(FFaDynCB0S(FapCtrl3DObjCmds::removePoint));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCtrl3DObjCmds::getSensitivity,bool&));
}

//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createInput()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcInput::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createOutput()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcOutput::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createAmplifier()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcAmplifier::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPower()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPower::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createComparator()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcComparator::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createAdder()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcAdder::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createMultiplyer()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcMultiplier::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createIntegrator()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcIntegrator::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createLimDerivator()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcLimDerivator::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createTimeDelay()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcTimeDelay::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createSampleHold()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcSampleHold::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createLogicalSwitch()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcLogicalSwitch::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createLimitation()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcLimitation::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createDeadZone()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcDeadZone::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createHysteresis()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcHysteresis::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPid()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPid::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPi()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPi::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPd()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPd::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPlimIlimD()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPlimIlimD::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPIlimD()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPIlimD::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPlimI()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPlimI::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createPlimD()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcPlimD::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createRealPole()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcRealPole::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::createCompConjPole()
{
  FapCtrl3DObjCmds::ctrlCreate(FmcCompConjPole::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::create1ordTF()
{
  FapCtrl3DObjCmds::ctrlCreate(Fmc1ordTF::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::create2ordTF()
{
  FapCtrl3DObjCmds::ctrlCreate(Fmc2ordTF::getClassTypeID());
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::rotate()
{
  if (!FapLicenseManager::hasCtrlLicense()) return;
  if (FapCmdsBase::hasResultsCheck()) return;

  FuiCtrlModes::setMode(FuiCtrlModes::ROTATE_MODE);
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::addPoint()
{
  if (!FapLicenseManager::hasCtrlLicense()) return;
  if (FapCmdsBase::hasResultsCheck()) return;

  FuiCtrlModes::setMode(FuiCtrlModes::ADDLINEPOINT_MODE);
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::removePoint()
{
  if (!FapLicenseManager::hasCtrlLicense()) return;
  if (FapCmdsBase::hasResultsCheck()) return;

  FuiCtrlModes::setMode(FuiCtrlModes::REMOVELINEPOINT_MODE);
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::ctrlCreate(int elemType)
{
  if (!FapLicenseManager::hasCtrlLicense(elemType)) return;
  if (FapCmdsBase::hasResultsCheck()) return;

  FuiCtrlModes::setMode(FuiCtrlModes::CREATE_MODE);
#ifdef USE_INVENTOR
  SbVec2f secondPos(2,2); // (1,1) is upper right screen corner
  // Using (2,2) here to ensure that the user can't see the element symbol
  SbVec3f startPos = FdCtrlDB::getNewVec(secondPos);
  FdCtrlDB::setCreatedElem(FmControlAdmin::createElement(elemType,startPos[0],startPos[1]));
#endif
}
//----------------------------------------------------------------------------

void FapCtrl3DObjCmds::getSensitivity(bool& isSensitive)
{
  FapCmdsBase::isModelEditable(isSensitive);
  if (!isSensitive) return;

  FapCmdsBase::isCtrlModellerActive(isSensitive);
}
//----------------------------------------------------------------------------
