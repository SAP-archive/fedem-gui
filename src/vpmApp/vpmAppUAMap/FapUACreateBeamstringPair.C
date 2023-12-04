// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUACreateBeamstringPair.H"
#include "vpmApp/vpmAppUAMap/FapUAQuery.H"
#include "vpmApp/FapLicenseManager.H"
#include "vpmUI/vpmUITopLevels/FuiCreateBeamstringPair.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmRiser.H"
#include "vpmDB/FmSoilPile.H"
#include "vpmDB/FmMathFuncBase.H"


Fmd_SOURCE_INIT(FAPUACREATEBEAMSTRINGPAIR, FapUACreateBeamstringPair, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUACreateBeamstringPair::FapUACreateBeamstringPair(FuiCreateBeamstringPair* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUACreateBeamstringPair);

  this->ui = uic;

  FuiCreateBeamstringPairCBs cb;
  cb.createCB = FFaDynCB4M(FapUACreateBeamstringPair,this,createCB,
                           FmModelMemberBase*,FmModelMemberBase*,
                           FmModelMemberBase*,bool);
  cb.deleteCB = FFaDynCB2M(FapUACreateBeamstringPair,this,deleteCB,
                           FmModelMemberBase*,FmModelMemberBase*);
  uic->setCBs(cb);
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUACreateBeamstringPair::createValuesObject()
{
  return new FuaCreateBeamstringPairValues();
}
//----------------------------------------------------------------------------

void FapUACreateBeamstringPair::setDBValues(FFuaUIValues*)
{
}
//----------------------------------------------------------------------------

static void verifyBeamstring1(bool& isOK, FmModelMemberBase* item)
{
  isOK = dynamic_cast<FmRiser*>(item) || dynamic_cast<FmSoilPile*>(item);
}
static void verifyBeamstring2(bool& isOK, FmModelMemberBase* item)
{
  isOK = dynamic_cast<FmRiser*>(item) ? true : false;
}
//----------------------------------------------------------------------------

static void verifyStiffnessFunction(bool& isOK, FmModelMemberBase* item)
{
  isOK = false;
  FmMathFuncBase* func = dynamic_cast<FmMathFuncBase*>(item);
  if (func && func->isLegalSprDmpFunc())
    isOK = (func->getFunctionUse() == FmMathFuncBase::SPR_TRA_STIFF ||
            func->getFunctionUse() == FmMathFuncBase::SPR_TRA_FORCE);
}
//----------------------------------------------------------------------------

void FapUACreateBeamstringPair::getDBValues(FFuaUIValues* values)
{
  FuaCreateBeamstringPairValues* cbpValues = (FuaCreateBeamstringPairValues*) values;

  static FapUAQuery beamstringQuery1;
  beamstringQuery1.clear();
  beamstringQuery1.typesToFind[FmSubAssembly::getClassTypeID()] = true;
  beamstringQuery1.verifyCB = FFaDynCB2S(verifyBeamstring1,bool&,FmModelMemberBase*);
  cbpValues->beamstringQuery1 = &beamstringQuery1;

  static FapUAQuery beamstringQuery2;
  beamstringQuery2.clear();
  beamstringQuery2.typesToFind[FmSubAssembly::getClassTypeID()] = true;
  beamstringQuery2.verifyCB = FFaDynCB2S(verifyBeamstring2,bool&,FmModelMemberBase*);
  cbpValues->beamstringQuery2 = &beamstringQuery2;

  static FapUAQuery stiffnessFunctionQuery;
  stiffnessFunctionQuery.clear();
  stiffnessFunctionQuery.typesToFind[FmMathFuncBase::getClassTypeID()] = true;
  stiffnessFunctionQuery.verifyCB = FFaDynCB2S(verifyStiffnessFunction,bool&,FmModelMemberBase*);
  cbpValues->stiffnessFunctionQuery = &stiffnessFunctionQuery;

  cbpValues->isSensitive = FpPM::isModelEditable();
}
//----------------------------------------------------------------------------

void FapUACreateBeamstringPair::createCB(FmModelMemberBase* beam1,
                                         FmModelMemberBase* beam2,
                                         FmModelMemberBase* spr, bool radial)
{
  if (!FapLicenseManager::checkLicense("FA-RIS"))
    return;
  else if (!beam1)
    Fui::okDialog("Please specify the first beamstring.\n\nNote: Click Help for more information.");
  else if (!beam2)
    Fui::okDialog("Please specify the second beamstring.\n\nNote: Click Help for more information.");
  else if (!spr)
    Fui::okDialog("Please specify the stiffness function.\n\nNote: Click Help for more information.");
  else
  {
    FpPM::vpmSetUndoPoint("Beamstring pair creation");
    if (FmRiser::stitch(beam1,beam2,spr,radial))
      Fui::okDialog("Beamstring pair successfully created.");
    else
      Fui::okDialog("Failed to create beamstring pair.");
  }
}
//----------------------------------------------------------------------------

void FapUACreateBeamstringPair::deleteCB(FmModelMemberBase* beam1,
                                         FmModelMemberBase* beam2)
{
  if (!FapLicenseManager::checkLicense("FA-RIS"))
    return;
  else if (!beam1)
    Fui::okDialog("Please specify the first beamstring.\n\nNote: Click Help for more information.");
  else if (!beam2)
    Fui::okDialog("Please specify the second beamstring.\n\nNote: Click Help for more information.");
  else
  {
    FpPM::vpmSetUndoPoint("Beamstring pair deletion");
    if (FmRiser::split(beam1,beam2))
      Fui::okDialog("Beamstring pair successfully deleted.");
  }
}
