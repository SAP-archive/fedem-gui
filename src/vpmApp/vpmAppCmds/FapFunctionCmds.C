// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapFunctionCmds.H"
#include "vpmApp/vpmAppCmds/FapDBCreateCmds.H"
#include "vpmApp/FapEventManager.H"
#include "vpmDB/FmEngine.H"
#include "vpmDB/FmfLinVar.H"
#include "vpmDB/FmSubAssembly.H"
#include "vpmDB/FmfDeviceFunction.H"
#include "vpmDB/FmfSinusoidal.H"
#include "vpmDB/FmSpringChar.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "vpmPM/FpPM.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"


void FapFunctionCmds::init()
{
  FFuaCmdItem* i;

#ifdef FAP_DEBUG
  std::cout <<"FapFunctionCmds::init()"<< std::endl;
#endif

  i = new FFuaCmdItem("cmdId_function_SpringCharTrans");
  i->setText("Adv. Spring Characteristics, Translation");
  i->setSmallIcon(spring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSpringCharTrans));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_SpringCharRot");
  i->setText("Adv. Spring Characteristics, Rotation");
  i->setSmallIcon(spring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSpringCharRot));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_SprTransStiff");
  i->setText("Stiffness - Translation");
  i->setSmallIcon(K_Tspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSprTransStiffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_SprTransForce");
  i->setText("Force - Translation");
  i->setSmallIcon(F_Tspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSprTransForceFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_SprRotStiff");
  i->setText("Stiffness - Rotation");
  i->setSmallIcon(K_Rspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSprRotStiffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_SprRotTorque");
  i->setText("Torque - Rotation");
  i->setSmallIcon(T_Rspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createSprRotTorqueFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_DaTransCoeff");
  i->setText("Coefficient - Velocity");
  i->setSmallIcon(C_Tdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createDaTransCoeffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_DaTransForce");
  i->setText("Force - Velocity");
  i->setSmallIcon(F_Tdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createDaTransForceFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_DaRotCoeff");
  i->setText("Coefficient - Rotational Vel.");
  i->setSmallIcon(C_Rdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createDaRotCoeffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_DaRotTorque");
  i->setText("Torque - Rotational Velocity");
  i->setSmallIcon(T_Rdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createDaRotTorqueFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_GeneralFunction");
  i->setText("Function");
  i->setSmallIcon(function_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createGeneralFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_DriveFile");
  i->setText("Time history input file");
  i->setSmallIcon(timeHistInputFile_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createDriveFile));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_RoadFunction");
  i->setText("Road elevation");
  i->setSmallIcon(createRoad_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createRoadFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_WaveFunction");
  i->setText("Sea wave function");
  i->setSmallIcon(f_of_xt_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createWaveFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_CurrFunction");
  i->setText("Sea current function");
  i->setSmallIcon(f_of_xt_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::createCurrFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertSprTransStiff");
  i->setText("Stiffness - Translation");
  i->setSmallIcon(K_Tspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToSprTransStiffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertSprTransForce");
  i->setText("Force - Translation");
  i->setSmallIcon(F_Tspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToSprTransForceFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertSprRotStiff");
  i->setText("Stiffness - Rotation");
  i->setSmallIcon(K_Rspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToSprRotStiffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertSprRotTorque");
  i->setText("Torque - Rotation");
  i->setSmallIcon(T_Rspring_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToSprRotTorqueFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertDaTransCoeff");
  i->setText("Coefficient - Velocity");
  i->setSmallIcon(C_Tdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToDaTransCoeffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertDaTransForce");
  i->setText("Force - Velocity");
  i->setSmallIcon(F_Tdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToDaTransForceFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertDaRotCoeff");
  i->setText("Coefficient - Rotational Velocity");
  i->setSmallIcon(C_Rdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToDaRotCoeffFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertDaRotTorque");
  i->setText("Torque - Rotational Velocity");
  i->setSmallIcon(T_Rdamper_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToDaRotTorqueFunc));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertGeneralFunction");
  i->setText("Function");
  i->setSmallIcon(function_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToGeneralFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertRoadFunction");
  i->setText("Road elevation");
  i->setSmallIcon(createRoad_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToRoadFunction));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));

  i = new FFuaCmdItem("cmdId_function_ConvertDriveFile");
  i->setText("Time history input file");
  i->setSmallIcon(timeHistInputFile_xpm);
  i->setActivatedCB(FFaDynCB0S(FapFunctionCmds::convertToDriveFile));
  i->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isModelEditable,bool&));
}

static void createSpringChar(FmSpringChar::SpringCharUse useType)
{
#ifdef FAP_DEBUG
  std::cout <<"FapFunctionCmds::createSpringChar() "<< useType << std::endl;
#endif

  FmSpringChar* sc = new FmSpringChar();
  sc->setSpringCharUse(useType);
  sc->setParentAssembly(FapDBCreateCmds::getSelectedAssembly());
  sc->connect();

  FapEventManager::permTotalSelect(sc);
}


static void createFunc(FmMathFuncBase::FuncUse useType,
		       bool defaultSine = false)
{
#ifdef FAP_DEBUG
  std::cout <<"FapFunctionCmds::createFunc() "<< useType << std::endl;
#endif

  FmMathFuncBase* f;
  if (defaultSine)
    f = new FmfSinusoidal();
  else
    f = new FmfLinVar();

  f->setFunctionUse(useType,true);
  f->setParentAssembly(FapDBCreateCmds::getSelectedAssembly());
  f->connect();

  FapEventManager::permTotalSelect(f);
}


void FapFunctionCmds::createSpringCharTrans()
{
  createSpringChar(FmSpringChar::TRANSLATION);
}

void FapFunctionCmds::createSpringCharRot()
{
  createSpringChar(FmSpringChar::ROTATION);
}


void FapFunctionCmds::createSprTransStiffFunc()
{
  createFunc(FmMathFuncBase::SPR_TRA_STIFF);
}

void FapFunctionCmds::createSprTransForceFunc()
{
  createFunc(FmMathFuncBase::SPR_TRA_FORCE);
}

void FapFunctionCmds::createSprRotStiffFunc()
{
  createFunc(FmMathFuncBase::SPR_ROT_STIFF);
}

void FapFunctionCmds::createSprRotTorqueFunc()
{
  createFunc(FmMathFuncBase::SPR_ROT_TORQUE);
}

void FapFunctionCmds::createDaTransCoeffFunc()
{
  createFunc(FmMathFuncBase::DA_TRA_COEFF);
}

void FapFunctionCmds::createDaTransForceFunc()
{
  createFunc(FmMathFuncBase::DA_TRA_FORCE);
}

void FapFunctionCmds::createDaRotCoeffFunc()
{
  createFunc(FmMathFuncBase::DA_ROT_COEFF);
}

void FapFunctionCmds::createDaRotTorqueFunc()
{
  createFunc(FmMathFuncBase::DA_ROT_TORQUE);
}


void FapFunctionCmds::createRoadFunction()
{
  FpPM::vpmSetUndoPoint("Road function");
  createFunc(FmMathFuncBase::ROAD_FUNCTION);
}


void FapFunctionCmds::createWaveFunction()
{
  FpPM::vpmSetUndoPoint("Wave function");
  createFunc(FmMathFuncBase::WAVE_FUNCTION,true);
}


void FapFunctionCmds::createCurrFunction()
{
  FpPM::vpmSetUndoPoint("Current function");
  createFunc(FmMathFuncBase::CURR_FUNCTION);
}


void FapFunctionCmds::createDriveFile()
{
#ifdef FAP_DEBUG
  std::cout <<"FapFunctionCmds::createDriveFile()"<< std::endl;
#endif

  FmBase* subass = FapDBCreateCmds::getSelectedAssembly();
  FmMathFuncBase* f = new FmfDeviceFunction();
  f->setFunctionUse(FmMathFuncBase::DRIVE_FILE);
  f->setParentAssembly(subass);
  f->connect();

  FmEngine* e = new FmEngine();
  e->setFunction(f);
  e->setParentAssembly(subass);
  e->connect();

  FapEventManager::permTotalSelect(e);
}


void FapFunctionCmds::createGeneralFunction()
{
#ifdef FAP_DEBUG
  std::cout <<"FapFunctionCmds::createGeneralFunction()"<< std::endl;
#endif

  FmEngine* e = new FmEngine();
  e->setParentAssembly(FapDBCreateCmds::getSelectedAssembly());
  e->connect();

  FapEventManager::permTotalSelect(e);
}


static void convertFunc(FmMathFuncBase::FuncUse use)
{
  std::vector<FmMathFuncBase*> selection;
  FapCmdsBase::getSelected(selection);

  for (FmMathFuncBase* f : selection)
    if (f->getFunctionUse() == FmMathFuncBase::NONE)
      if (f->setFunctionUse(use,true))
      {
        // The function was assigned a new userID due to conflict among
        // other functions with similar use. Must reconnect in order to
        // maintain the sorting of the linked list of functions.
        f->disconnect();
        f->connect();
      }
}


void FapFunctionCmds::convertToSprTransStiffFunc()
{
  convertFunc(FmMathFuncBase::SPR_TRA_STIFF);
}

void FapFunctionCmds::convertToSprTransForceFunc()
{
  convertFunc(FmMathFuncBase::SPR_TRA_FORCE);
}

void FapFunctionCmds::convertToSprRotStiffFunc()
{
  convertFunc(FmMathFuncBase::SPR_ROT_STIFF);
}

void FapFunctionCmds::convertToSprRotTorqueFunc()
{
  convertFunc(FmMathFuncBase::SPR_ROT_TORQUE);
}

void FapFunctionCmds::convertToDaTransCoeffFunc()
{
  convertFunc(FmMathFuncBase::DA_TRA_COEFF);
}

void FapFunctionCmds::convertToDaTransForceFunc()
{
  convertFunc(FmMathFuncBase::DA_TRA_FORCE);
}

void FapFunctionCmds::convertToDaRotCoeffFunc()
{
  convertFunc(FmMathFuncBase::DA_ROT_COEFF);
}

void FapFunctionCmds::convertToDaRotTorqueFunc()
{
  convertFunc(FmMathFuncBase::DA_ROT_TORQUE);
}

void FapFunctionCmds::convertToRoadFunction()
{
  convertFunc(FmMathFuncBase::ROAD_FUNCTION);
}


static void convertToEngine(FmMathFuncBase::FuncUse use)
{
  std::vector<FmMathFuncBase*> selection;
  FapCmdsBase::getSelected(selection);

  for (FmMathFuncBase* f : selection)
    if (f->getFunctionUse() == FmMathFuncBase::NONE)
    {
      FmEngine* e = new FmEngine();
      f->setFunctionUse(use);
      e->setUserDescription(f->getUserDescription());
      e->setFunction(f);
      e->setParentAssembly(f->getParentAssembly());
      e->connect();
    }
}


void FapFunctionCmds::convertToGeneralFunction()
{
  convertToEngine(FmMathFuncBase::GENERAL);
}


void FapFunctionCmds::convertToDriveFile()
{
  convertToEngine(FmMathFuncBase::DRIVE_FILE);
}


void FapFunctionCmds::getConvertFuncSensitivity(bool& generalSensitivity,
						bool& convertSpringDamper,
						bool& convertDriveFile)
{
  FapCmdsBase::isModelEditable(generalSensitivity);
  if (!generalSensitivity) return;

  generalSensitivity = false;
  std::vector<FmMathFuncBase*> selection;
  if (!FapCmdsBase::getSelected(selection)) return;

  convertSpringDamper = convertDriveFile = true;

  for (FmMathFuncBase* func : selection)
    if (func->getFunctionUse() == FmMathFuncBase::NONE)
    {
      // Check if we can set to spring/damper function
      if (!func->isLegalSprDmpFunc())
	convertSpringDamper = false;

      // Check if we can set as time history input file
      if (!func->isOfType(FmfDeviceFunction::getClassTypeID()))
	convertDriveFile = false;
    }
    else // This is not an unused function
      return;

  // All selected functions are unused
  generalSensitivity = true;
}
