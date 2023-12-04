// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAEigenOptions.H"
#include "vpmApp/FapLicenseManager.H"
#include "vpmUI/vpmUITopLevels/FuiEigenOptions.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmModesOptions.H"
#include "FFaLib/FFaOS/FFaFilePath.H"


Fmd_SOURCE_INIT(FAPUAEIGENOPTIONS, FapUAEigenOptions, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAEigenOptions::FapUAEigenOptions(FuiEigenOptions* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAEigenOptions);
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAEigenOptions::createValuesObject()
{
  return new FuaEigenOptionsValues();
}
//----------------------------------------------------------------------------

void FapUAEigenOptions::finishUI()
{
  Fui::eigenmodeOptionsUI(false,true);
}
//----------------------------------------------------------------------------

void FapUAEigenOptions::setDBValues(FFuaUIValues* values)
{
  FuaEigenOptionsValues* eigenValues = (FuaEigenOptionsValues*) values;

  FmModesOptions* modes = FmDB::getModesOptions();

  // Remove superfluous DB eigenmode data
  FmModeVec& dbmodes = modes->modesArray.getValue();
  FmModeVec::iterator it = dbmodes.begin();
  while (it != dbmodes.end())
  {
    bool found = false;
    for (const FuiModeData& uimode : eigenValues->selectedModes)
      if (uimode.mode == it->first && uimode.time == it->second)
      {
        found = true;
        break;
      }

    if (!found)
      dbmodes.erase(it);
    else
      it++;
  }

  for (const FuiModeData& uimode : eigenValues->selectedModes)
    modes->addEigenmodeData(uimode.mode,uimode.time);

  if (eigenValues->autoVTFSwitch >= 0) {
    modes->autoVTFExport = eigenValues->autoVTFSwitch && FapLicenseManager::hasVTFExportLicense();
    modes->vtfFileName = eigenValues->autoVTFFileName;
    modes->vtfFileType = (VTFFileType)eigenValues->autoVTFFileType;
  }

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAEigenOptions::getDBValues(FFuaUIValues* values)
{
  FuaEigenOptionsValues* eigenValues = (FuaEigenOptionsValues*) values;

  eigenValues->modes.clear();
  eigenValues->times.clear();
  eigenValues->selectedModes.clear();

  FmAnalysis* analysis = FmDB::getActiveAnalysis();

  // Don't create a modes options object here, if we don't have any yet
  FmModesOptions* modes = FmDB::getModesOptions(false);
  if (!modes)
  {
    if (analysis->solveEigenvalues.getValue() &&
	analysis->numEigenmodes.getValue() > 0)
      modes = new FmModesOptions(); // create a object to get default values
    else
      return; // eigenvalue analysis is not toggled on
  }

  analysis->getEigenvalueList(eigenValues->modes);
  analysis->getEigenvalueSamples(eigenValues->times);

  FuiModeData uimodedata;
  for (const FmModeType& dbmode : modes->modesArray.getValue())
  {
    uimodedata.mode = dbmode.first;
    uimodedata.time = dbmode.second;
    eigenValues->selectedModes.push_back(uimodedata);
  }

  if (FapLicenseManager::hasFeature("FA-VTF")) {
    eigenValues->autoVTFSwitch   = modes->autoVTFExport.getValue();
    eigenValues->autoVTFFileName = modes->vtfFileName.getValue();
    eigenValues->autoVTFFileType = modes->vtfFileType.getValue();
    eigenValues->modelFilePath   = FmDB::getMechanismObject()->getAbsModelFilePath() + FFaFilePath::getPathSeparator();
  }
  else // hide VTF field and toggle, feature not available
    eigenValues->autoVTFSwitch = -1;

  // Delete the temporary modes options object
  if (!FmDB::getModesOptions(false)) modes->erase();

  eigenValues->isSensitive = FpPM::isModelTouchable();
}
//----------------------------------------------------------------------------
