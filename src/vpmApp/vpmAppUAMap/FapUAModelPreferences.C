// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAModelPreferences.H"
#include "vpmApp/vpmAppCmds/FapFileCmds.H"
#include "vpmUI/vpmUITopLevels/FuiModelPreferences.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmTire.H"
#include "vpmDB/FmEngine.H"
#include "FFaLib/FFaAlgebra/FFaUnitCalculator.H"
#include "FFaLib/FFaOS/FFaFilePath.H"


Fmd_SOURCE_INIT(FAPUAMODELPREFERENCES, FapUAModelPreferences, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAModelPreferences::FapUAModelPreferences(FuiModelPreferences* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAModelPreferences);

  this->ui = uic;

  uic->setUpdateDescriptionCB(FFaDynCB1M(FapUAModelPreferences,this,
					 updateDescriptionCB,const std::string&));
  uic->setChangeRepositoryCB(FFaDynCB1M(FapUAModelPreferences,this,
					changeRepositoryCB,bool));
}
//----------------------------------------------------------------------------

void FapUAModelPreferences::updateDescriptionCB(const std::string& newdescr)
{
  FmMechanism* mech = FmDB::getMechanismObject();
  if (mech->getUserDescription() == newdescr) return; // no change

  FpPM::vpmSetUndoPoint("Model description");

  mech->setUserDescription(newdescr);

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAModelPreferences::changeRepositoryCB(bool switchToInternal)
{
  FapFileCmds::setModelLinkRep(switchToInternal);
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAModelPreferences::createValuesObject()
{
  return new FuaModelPreferencesValues();
}
//----------------------------------------------------------------------------

void FapUAModelPreferences::setDBValues(FFuaUIValues* values)
{
  FpPM::vpmSetUndoPoint("Model preferences");

  FuaModelPreferencesValues* modelValues = (FuaModelPreferencesValues*) values;

  FmMechanism* mech = FmDB::getMechanismObject();
  FmAnalysis*  anal = FmDB::getActiveAnalysis();

  mech->setUserDescription(modelValues->description);

  if (mech->positionTolerance.setValue(modelValues->modelingTol))
    Fui::okDialog("Changing the position tolerance might result\n"
		  "in inconsistent modeling and/or unexpected\n"
		  "behaviour when reloading the model.\n\n"
		  "Please consult the documentation.");

  double origLScale = mech->modelDatabaseUnits.getValue().convFactor("LENGTH");
  if (modelValues->selectedUnits == "SI")
    mech->modelDatabaseUnits.reset();
  else
  {
    std::vector<const FFaUnitCalculator*> definedCalcs = FFaUnitCalculatorProvider::instance()->getCalculators();
    for (const FFaUnitCalculator* calc : definedCalcs)
      if (calc->getOrigUnits() == modelValues->selectedUnits)
        mech->modelDatabaseUnits.setValue(*calc);
  }

  mech->setGravity(modelValues->gravitation);
  mech->initVel.setValue(modelValues->velocity);

  anal->overwriteFEParts.setValue(modelValues->overwriteFE);
  if (modelValues->useFuncFile >= 0) {
    anal->useExternalFuncFile.setValue(modelValues->useFuncFile);
    anal->externalFuncFileName.setValue(modelValues->extFuncFileName);
  }

  FpPM::touchModel(); // Indicate that the model needs save

  if (mech->modelDatabaseUnits.getValue().convFactor("LENGTH") == origLScale)
    return;

  // Update tire renderings due to changed length scale
  std::vector<FmModelMemberBase*> objs;
  FmDB::getAllOfType(objs,FmTire::getClassTypeID());
  for (FmModelMemberBase* tire : objs)
    ((FmTire*)tire)->draw();
}
//----------------------------------------------------------------------------

void FapUAModelPreferences::getDBValues(FFuaUIValues* values)
{
  FuaModelPreferencesValues* modelValues = (FuaModelPreferencesValues*) values;

  FmMechanism* mech = FmDB::getMechanismObject();
  FmAnalysis*  anal = FmDB::getActiveAnalysis();

  modelValues->description = mech->getUserDescription();
  modelValues->repository = mech->modelLinkRepository.getValue();
  modelValues->modelingTol = mech->positionTolerance.getValue();
  modelValues->selectedUnits = mech->modelDatabaseUnits.getValue().getOrigUnits();

  std::vector<const FFaUnitCalculator*> definedCalcs = FFaUnitCalculatorProvider::instance()->getCalculators();
  modelValues->units.push_back("SI");
  for (const FFaUnitCalculator* calc : definedCalcs)
    if (calc->getConvUnits() == "SI (kg/m/N)")
      modelValues->units.push_back(calc->getOrigUnits());

  modelValues->gravitation = mech->gravity.getValue();
  modelValues->velocity = mech->initVel.getValue();

  modelValues->overwriteFE = anal->overwriteFEParts.getValue();

  std::vector<FmEngine*> engines;
  FmDB::getAllEngines(engines);
  for (FmEngine* e : engines)
    if (e->isExternalFunc())
    {
      modelValues->useFuncFile = anal->useExternalFuncFile.getValue();
      modelValues->extFuncFileName = anal->externalFuncFileName.getValue();
      modelValues->modelFilePath = mech->getAbsModelFilePath() + FFaFilePath::getPathSeparator();
      break;
    }

  modelValues->isSensitive = FpPM::isModelEditable();
}
//----------------------------------------------------------------------------

void FapUAModelPreferences::finishUI()
{
  Fui::modelPreferencesUI(false,true);
}
//----------------------------------------------------------------------------
