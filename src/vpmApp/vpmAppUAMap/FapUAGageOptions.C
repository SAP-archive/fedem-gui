// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAGageOptions.H"
#include "vpmApp/FapLicenseManager.H"
#include "vpmUI/vpmUITopLevels/FuiGageOptions.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmStrainRosette.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmGageOptions.H"
#include "FFuLib/FFuFileDialog.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


Fmd_SOURCE_INIT(FAPUAGAGEOPTIONS, FapUAGageOptions, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAGageOptions::FapUAGageOptions(FuiGageOptions* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAGageOptions);

  this->ui = uic;

  ui->setResetTimeCB(FFaDynCB0M(FapUAGageOptions,this,resetTime));
  ui->setImportRosetteFileCB(FFaDynCB0M(FapUAGageOptions,this,importRosFile));
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAGageOptions::createValuesObject()
{
  return new FuaGageOptionsValues();
}
//----------------------------------------------------------------------------

void FapUAGageOptions::setDBValues(FFuaUIValues* values)
{
  FmGageOptions* dbgageOptions = FmDB::getGageOptions();

  FuaGageOptionsValues* gageValues = (FuaGageOptionsValues*) values;

  dbgageOptions->startTime = gageValues->timeValues.start;
  dbgageOptions->stopTime = gageValues->timeValues.stop;
  dbgageOptions->timeIncr = gageValues->timeValues.incr;
  dbgageOptions->allTimeSteps = gageValues->timeValues.allSteps;
  dbgageOptions->dacSampleRate = gageValues->dacSampleRate;
  if (FapLicenseManager::isProEdition())
    dbgageOptions->autoDacExport = gageValues->autoDacSwitch;
  else
  {
    dbgageOptions->autoDacExport = false;
    if (gageValues->autoDacSwitch)
      FFaMsg::dialog("Direct export of gage strains to DAC files\n"
		     "is not available in the free edition of Fedem.\n"
		     "You need a commercial license to use this feature.",
		     FFaMsg::WARNING);
  }
  dbgageOptions->binSize = gageValues->binSize;
  dbgageOptions->fatigue = gageValues->rainflowSwitch;

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAGageOptions::getDBValues(FFuaUIValues* values)
{
  // Don't create a gage options object here, if we don't have any yet
  FmGageOptions* dbgageOptions = FmDB::getGageOptions(false);
  // Create a temporary object to get default values
  if (!dbgageOptions) dbgageOptions = new FmGageOptions();

  FuaGageOptionsValues* gageValues = (FuaGageOptionsValues*) values;

  gageValues->timeValues.start = dbgageOptions->startTime.getValue();
  gageValues->timeValues.stop = dbgageOptions->stopTime.getValue();
  gageValues->timeValues.incr = dbgageOptions->timeIncr.getValue();
  gageValues->timeValues.allSteps = dbgageOptions->allTimeSteps.getValue();
  gageValues->dacSampleRate = dbgageOptions->dacSampleRate.getValue();
  gageValues->autoDacSwitch = dbgageOptions->autoDacExport.getValue();
  gageValues->binSize = dbgageOptions->binSize.getValue();
  gageValues->rainflowSwitch = dbgageOptions->fatigue.getValue();

  // Delete the temporary gage options object
  if (!FmDB::getGageOptions(false)) dbgageOptions->erase();

  gageValues->isSensitive = FpPM::isModelTouchable();
}
//----------------------------------------------------------------------------

void FapUAGageOptions::resetTime()
{
  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  if (!analysis) return;

  FuaTimeIntervalValues timeValues;

  timeValues.start = analysis->startTime.getValue();
  timeValues.stop = analysis->stopTime.getValue();
  timeValues.dontTouchIncr = true;
  timeValues.allSteps = true;

  this->ui->setTimeUIValues(&timeValues);
}
//----------------------------------------------------------------------------

void FapUAGageOptions::finishUI()
{
  Fui::gageOptionsUI(false,true);
}
//----------------------------------------------------------------------------

void FapUAGageOptions::importRosFile()
{
  std::string startPath = FmDB::getMechanismObject()->getAbsModelFilePath();
  FFuFileDialog* aDialog = FFuFileDialog::create(startPath, "Dialog",
						 FFuFileDialog::FFU_OPEN_FILE,
						 true);

  aDialog->addAllFilesFilter(true);
  aDialog->remember("ImportStrainRosetteFile");

  std::vector<std::string> fileNames = aDialog->execute();
  delete aDialog;

  if (fileNames.empty()) return;

  FmStrainRosette::createRosettesFromOldFile(fileNames.front(),true);

  std::vector<FmModelMemberBase*> allRosettes;
  FmDB::getAllOfType(allRosettes,FmStrainRosette::getClassTypeID());
  for (FmModelMemberBase* rosette : allRosettes)
    FmDB::resolveObject(rosette);

  FmStrainRosette::syncStrainRosettes();
}
