// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAStressOptions.H"
#include "vpmApp/FapLicenseManager.H"
#include "vpmUI/vpmUITopLevels/FuiStressOptions.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmAnalysis.H"
#include "FFaLib/FFaOS/FFaFilePath.H"


Fmd_SOURCE_INIT(FAPUASTRESSOPTIONS, FapUAStressOptions, FapUAExistenceHandler);

//----------------------------------------------------------------------------

FapUAStressOptions::FapUAStressOptions(FuiStressOptions* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAStressOptions);

  this->ui = uic;

  ui->setResetTimeCB(FFaDynCB0M(FapUAStressOptions,this,resetTime));
}
//----------------------------------------------------------------------------

FapUAStressOptions::~FapUAStressOptions()
{
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAStressOptions::createValuesObject()
{
  return new FuaStressOptionsValues();
}
//----------------------------------------------------------------------------

void FapUAStressOptions::finishUI()
{
  Fui::stressOptionsUI(false,true);
}
//----------------------------------------------------------------------------

void FapUAStressOptions::resetTime()
{
  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  if (!analysis) return;

  FuaTimeIntervalValues timeValues;

  timeValues.start = analysis->startTime.getValue();
  timeValues.stop = analysis->stopTime.getValue();
  timeValues.incr = analysis->timeIncr.getValue() * 10.0;
  timeValues.dontTouchIncr = false;
  timeValues.allSteps = false;

  this->ui->setTimeUIValues(&timeValues);
}
//----------------------------------------------------------------------------

void FapUAStressOptions::setDBValues(FFuaUIValues* values)
{
  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  if (!analysis) return;

  FuaStressOptionsValues* stressValues = (FuaStressOptionsValues*) values;

  analysis->stressStartTime = stressValues->timeValues.start;
  analysis->stressStopTime = stressValues->timeValues.stop;
  analysis->stressTimeIncr = stressValues->timeValues.incr;
  analysis->stressAllTimeSteps = stressValues->timeValues.allSteps;

  analysis->stressDeformation = stressValues->deformationOutput;
  analysis->stressStrainTensor = stressValues->strainOutput[0];
  analysis->stressVMstrain = stressValues->strainOutput[1];
  analysis->stressMaxPstrain = stressValues->strainOutput[2];
  analysis->stressMinPstrain = stressValues->strainOutput[3];
  analysis->stressMaxSstrain = stressValues->strainOutput[4];
  analysis->stressStressTensor = stressValues->stressOutput[0];
  analysis->stressVMstress = stressValues->stressOutput[1];
  analysis->stressMaxPstress = stressValues->stressOutput[2];
  analysis->stressMinPstress = stressValues->stressOutput[3];
  analysis->stressMaxSstress = stressValues->stressOutput[4];
  analysis->stressSRTensor = stressValues->stressResOutput;

  if (stressValues->autoVTFSwitch > 0) {
    analysis->autoStressVTFExport = FapLicenseManager::hasVTFExportLicense();
    analysis->stressVTFname = stressValues->autoVTFFileName;
    analysis->stressVTFtype = (VTFFileType)stressValues->autoVTFFileType;
    analysis->stressVTFrange = std::make_pair(stressValues->vtfFringeMin,
                                              stressValues->vtfFringeMax);
  }
  else if (stressValues->autoVTFSwitch == 0)
    analysis->autoStressVTFExport = false;

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAStressOptions::getDBValues(FFuaUIValues* values)
{
  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  if (!analysis) return;

  FuaStressOptionsValues* stressValues = (FuaStressOptionsValues*) values;

  stressValues->timeValues.start = analysis->stressStartTime.getValue();
  stressValues->timeValues.stop = analysis->stressStopTime.getValue();
  stressValues->timeValues.incr = analysis->stressTimeIncr.getValue();
  stressValues->timeValues.allSteps = analysis->stressAllTimeSteps.getValue();

  stressValues->deformationOutput = analysis->stressDeformation.getValue();
  stressValues->strainOutput[0] = analysis->stressStrainTensor.getValue();
  stressValues->strainOutput[1] = analysis->stressVMstrain.getValue();
  stressValues->strainOutput[2] = analysis->stressMaxPstrain.getValue();
  stressValues->strainOutput[3] = analysis->stressMinPstrain.getValue();
  stressValues->strainOutput[4] = analysis->stressMaxSstrain.getValue();
  stressValues->stressOutput[0] = analysis->stressStressTensor.getValue();
  stressValues->stressOutput[1] = analysis->stressVMstress.getValue();
  stressValues->stressOutput[2] = analysis->stressMaxPstress.getValue();
  stressValues->stressOutput[3] = analysis->stressMinPstress.getValue();
  stressValues->stressOutput[4] = analysis->stressMaxSstress.getValue();
  stressValues->stressResOutput = analysis->stressSRTensor.getValue();

  if (FapLicenseManager::checkVTFExportLicense(false)) {
    stressValues->autoVTFSwitch   = analysis->autoStressVTFExport.getValue();
    stressValues->autoVTFFileName = analysis->stressVTFname.getValue();
    stressValues->autoVTFFileType = analysis->stressVTFtype.getValue();
    stressValues->modelFilePath   = FmDB::getMechanismObject()->getAbsModelFilePath() + FFaFilePath::getPathSeparator();
    stressValues->vtfFringeMin = analysis->stressVTFrange.getValue().first;
    stressValues->vtfFringeMax = analysis->stressVTFrange.getValue().second;
  }
  else // hide VTF field and toggle, feature not available
    stressValues->autoVTFSwitch = -1;

  stressValues->isSensitive = FpPM::isModelTouchable();
}
//----------------------------------------------------------------------------
