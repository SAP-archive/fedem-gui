// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAPreferences.H"
#include "vpmUI/vpmUITopLevels/FuiPreferences.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmModesOptions.H"
#include "vpmDB/FmGageOptions.H"
#include "vpmDB/FmFppOptions.H"
#include "FFaLib/FFaString/FFaStringExt.H"


Fmd_SOURCE_INIT(FAPUAPREFERENCES, FapUAPreferences, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAPreferences::FapUAPreferences(FuiPreferences* ui)
  : FapUAExistenceHandler(ui), FapUADataHandler(ui), FapUAFinishHandler(ui)
{
  Fmd_CONSTRUCTOR_INIT(FapUAPreferences);
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAPreferences::createValuesObject()
{
  return new FuaPreferencesValues();
}
//----------------------------------------------------------------------------

void FapUAPreferences::finishUI()
{
  Fui::preferencesUI(false,true);
}
//----------------------------------------------------------------------------

void FapUAPreferences::setDBValues(FFuaUIValues* values)
{
  FuaPreferencesValues* prefValues = (FuaPreferencesValues*) values;

  FmAnalysis* analysis = FmDB::getActiveAnalysis();

  analysis->reducerAddOpts = prefValues->options[FuiPreferences::REDUCER];
  analysis->solverAddOpts = prefValues->options[FuiPreferences::SOLVER];
  analysis->stressAddOpts = prefValues->options[FuiPreferences::STRESS];

  FmModesOptions* modesOptions = FmDB::getModesOptions(!prefValues->options[FuiPreferences::MODES].empty());
  if (modesOptions)
    modesOptions->addOptions = prefValues->options[FuiPreferences::MODES];

  FmGageOptions* gageOptions = FmDB::getGageOptions(!prefValues->options[FuiPreferences::GAGE].empty());
  if (gageOptions)
    gageOptions->addOptions = prefValues->options[FuiPreferences::GAGE];

  FmFppOptions* fppOptions = FmDB::getFppOptions(!prefValues->options[FuiPreferences::FPP].empty());
  if (fppOptions)
    fppOptions->addOptions = prefValues->options[FuiPreferences::FPP];

  char* endPtr = NULL;
  const char* maxCP = prefValues->options[FuiPreferences::MAX_CONC_PROC].c_str();
  analysis->maxConcurrentProcesses = strtol(maxCP,&endPtr,10);
  prefValues->optionStatus[FuiPreferences::MAX_CONC_PROC] = (endPtr == maxCP+strlen(maxCP) &&
							     analysis->maxConcurrentProcesses.getValue() > 0);

  analysis->useRamSizeGSF  = prefValues->useEqSolverBuffer;
  analysis->autoRamSizeGSF = prefValues->autoEqSolverBuffer;
  const char* ramS = prefValues->options[FuiPreferences::EQ_SOLVER_SWAP].c_str();
  analysis->ramSizeGSF = strtol(ramS,&endPtr,10);
  prefValues->optionStatus[FuiPreferences::EQ_SOLVER_SWAP] = (endPtr == ramS+strlen(ramS) &&
							      analysis->ramSizeGSF.getValue() >= 0);

  analysis->useRamSizeBmat  = prefValues->useRecMatrixBuffer;
  analysis->autoRamSizeBmat = prefValues->autoRecMatrixBuffer;
  const char* ramR = prefValues->options[FuiPreferences::REC_MATRIX_SWAP].c_str();
  analysis->ramSizeBmat = strtol(ramR,&endPtr,10);
  prefValues->optionStatus[FuiPreferences::REC_MATRIX_SWAP] = (endPtr == ramR+strlen(ramR) &&
							       analysis->ramSizeBmat.getValue() >= 0);

  analysis->useProcessPrefix = prefValues->useSolverPrefix;
  analysis->processPrefix = prefValues->options[FuiPreferences::SOLVER_PREFIX];
  analysis->useProcessPath = prefValues->useSolverPath;
  analysis->processPath = prefValues->options[FuiPreferences::SOLVER_PATH];

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAPreferences::getDBValues(FFuaUIValues* values)
{
  FuaPreferencesValues* prefValues = (FuaPreferencesValues*) values;

  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  FmModesOptions* modesOptions = FmDB::getModesOptions(false);
  FmGageOptions* gageOptions = FmDB::getGageOptions(false);
  FmFppOptions* fppOptions = FmDB::getFppOptions(false);

  prefValues->options[FuiPreferences::REDUCER] = analysis->reducerAddOpts.getValue();
  prefValues->options[FuiPreferences::SOLVER] = analysis->solverAddOpts.getValue();
  prefValues->options[FuiPreferences::STRESS] = analysis->stressAddOpts.getValue();
  if (modesOptions)
    prefValues->options[FuiPreferences::MODES] = modesOptions->addOptions.getValue();
  if (gageOptions)
    prefValues->options[FuiPreferences::GAGE] = gageOptions->addOptions.getValue();
  if (fppOptions)
    prefValues->options[FuiPreferences::FPP] = fppOptions->addOptions.getValue();

  prefValues->options[FuiPreferences::MAX_CONC_PROC] = FFaNumStr(analysis->maxConcurrentProcesses.getValue());

  prefValues->useEqSolverBuffer = analysis->useRamSizeGSF.getValue();
  prefValues->autoEqSolverBuffer = analysis->autoRamSizeGSF.getValue();
  prefValues->options[FuiPreferences::EQ_SOLVER_SWAP] = FFaNumStr(analysis->ramSizeGSF.getValue());

  prefValues->useRecMatrixBuffer = analysis->useRamSizeBmat.getValue();
  prefValues->autoRecMatrixBuffer = analysis->autoRamSizeBmat.getValue();
  prefValues->options[FuiPreferences::REC_MATRIX_SWAP] = FFaNumStr(analysis->ramSizeBmat.getValue());

  prefValues->useSolverPrefix = analysis->useProcessPrefix.getValue();
  prefValues->options[FuiPreferences::SOLVER_PREFIX] = analysis->processPrefix.getValue();

  prefValues->useSolverPath = analysis->useProcessPath.getValue();
  prefValues->options[FuiPreferences::SOLVER_PATH] = analysis->processPath.getValue();

  prefValues->isRestarted = analysis->doRestart.getValue();
  prefValues->isSensitive = FpPM::isModelEditable();
  prefValues->isTouchable = FpPM::isModelTouchable();
}
//----------------------------------------------------------------------------
