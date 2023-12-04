// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAAirEnvironment.H"
#include "vpmUI/vpmUITopLevels/FuiAirEnvironment.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmTurbine.H"
#include "vpmDB/FmAirState.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmMechanism.H"
#include "FFaLib/FFaAlgebra/FFaMath.H"
#include "FFaLib/FFaOS/FFaFilePath.H"


Fmd_SOURCE_INIT(FAPUAAIRENVIRONMENT, FapUAAirEnvironment, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAAirEnvironment::FapUAAirEnvironment(FuiAirEnvironment* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAAirEnvironment);

  this->ui = uic;
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAAirEnvironment::createValuesObject()
{
  return new FuaAirEnvironmentValues();
}
//----------------------------------------------------------------------------

void FapUAAirEnvironment::setDBValues(FFuaUIValues* values)
{
  FuaAirEnvironmentValues* airValues = (FuaAirEnvironmentValues*) values;

  FmTurbine* turb = FmDB::getTurbineObject();
  FmAirState* air = FmDB::getAirStateObject();

  air->stallMod.setValue(static_cast<FmAirState::FmStallModel>(airValues->stallMod));
  air->useCM.setValue(airValues->useCM);
  air->infMod.setValue(static_cast<FmAirState::FmInfModel>(airValues->infMod));
  air->indMod.setValue(static_cast<FmAirState::FmIndModel>(airValues->indMod));
  air->aToler.setValue(airValues->aToler);
  air->tlMod.setValue(static_cast<FmAirState::FmLossModel>(airValues->tlMod));
  air->hlMod.setValue(static_cast<FmAirState::FmLossModel>(airValues->hlMod));
  air->useWindFile.setValue(!airValues->constWnd);
  air->windSpeed.setValue(airValues->windVel);
  air->windDirection.setValue(airValues->windDir);
  air->windFile.setValue(airValues->windFile);
  air->twrPot.setValue(airValues->twrPot);
  air->twrShad.setValue(airValues->twrShad);
  if (turb) turb->towerFile.setValue(airValues->twrFile);
  air->airDens.setValue(airValues->airDens);
  air->kinVisc.setValue(airValues->kinVisc);
  air->dtAero.setValue(airValues->dtAero);
  air->useDSdt.setValue(airValues->useDSdt);

  FpPM::touchModel(); // Indicate that the model needs save
}
//----------------------------------------------------------------------------

void FapUAAirEnvironment::getDBValues(FFuaUIValues* values)
{
  FuaAirEnvironmentValues* airValues = (FuaAirEnvironmentValues*) values;

  FmAnalysis* analysis = FmDB::getActiveAnalysis();
  FmTurbine* turb = FmDB::getTurbineObject();
  // Don't create an air state object here, if we don't have any yet
  FmAirState* air = FmDB::getAirStateObject(false);
  // Create a temporary object to get default values
  if (!air) air = new FmAirState();

  // Set values
  airValues->stallMod = air->stallMod.getValue();
  airValues->useCM = air->useCM.getValue();
  airValues->infMod = air->infMod.getValue();
  airValues->indMod = air->indMod.getValue();
  airValues->aToler = air->aToler.getValue();
  airValues->tlMod = air->tlMod.getValue();
  airValues->hlMod = air->hlMod.getValue();
  airValues->constWnd = !air->useWindFile.getValue();
  airValues->windVel = air->windSpeed.getValue();
  airValues->windDir = air->windDirection.getValue();
  airValues->windFile = air->windFile.getValue();
  airValues->twrPot = air->twrPot.getValue();
  airValues->twrShad = air->twrShad.getValue();
  airValues->airDens = air->airDens.getValue();
  airValues->kinVisc = air->kinVisc.getValue();
  airValues->dtAero = air->dtAero.getValue();
  airValues->useDSdt = air->useDSdt.getValue();
  if (turb) {
    airValues->twrFile = turb->towerFile.getValue();
    airValues->windTurbHubHeight = turb->getHubHeight();
    airValues->windTurbGridSize = turb->getRotorSize();
  }
  airValues->windTurbDuration = analysis->stopTime.getValue() - analysis->startTime.getValue();
  airValues->windTurbTimeInc = analysis->timeIncr.getValue();
  airValues->modelFilePath = FmDB::getMechanismObject()->getAbsModelFilePath() + FFaFilePath::getPathSeparator();

  // Delete the temporary air state object
  if (!FmDB::getAirStateObject(false))
    air->erase();

  airValues->isSensitive = FpPM::isModelEditable();
}
//----------------------------------------------------------------------------

void FapUAAirEnvironment::finishUI()
{
  Fui::airEnvironmentUI(false,true);
}
//----------------------------------------------------------------------------
