// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAQuery.H"
#include "vpmApp/FapEventManager.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "vpmDB/FmFileReference.H"
#include "vpmDB/FmBeamProperty.H"
#include "vpmDB/FmMaterialProperty.H"
#include "vpmDB/FmEngine.H"
#include "vpmDB/FmTriad.H"
#include "vpmDB/FmRevJoint.H"


FapUAFileRefQuery::FapUAFileRefQuery()
{
  this->typesToFind[FmFileReference::getClassTypeID()] = true;
}


FapUABeamPropQuery::FapUABeamPropQuery()
{
  this->typesToFind[FmBeamProperty::getClassTypeID()] = true;
}


FapUAMaterialPropQuery::FapUAMaterialPropQuery()
{
  this->typesToFind[FmMaterialProperty::getClassTypeID()] = true;
}


FapUATriadQuery::FapUATriadQuery()
{
  this->typesToFind[FmTriad::getClassTypeID()] = true;
}


FapUALinkQuery::FapUALinkQuery()
{
  this->typesToFind[FmLink::getClassTypeID()] = true;
}


FapUARevJointQuery::FapUARevJointQuery()
{
  this->typesToFind[FmRevJoint::getClassTypeID()] = true;
}


FapUAEngineQuery::FapUAEngineQuery()
{
  this->typesToFind[FmEngine::getClassTypeID()] = true;
  this->verifyCB = FFaDynCB2S(FapUAEngineQuery::verify,bool&,FmModelMemberBase*);
}


FapUARoadFuncQuery::FapUARoadFuncQuery()
{
  this->typesToFind[FmMathFuncBase::getClassTypeID()] = true;
  this->verifyCB = FFaDynCB2S(FapUARoadFuncQuery::verify,bool&,FmModelMemberBase*);
}


FapUAWaveFuncQuery::FapUAWaveFuncQuery()
{
  this->typesToFind[FmMathFuncBase::getClassTypeID()] = true;
  this->verifyCB = FFaDynCB2S(FapUAWaveFuncQuery::verify,bool&,FmModelMemberBase*);
}


FapUACurrFuncQuery::FapUACurrFuncQuery()
{
  this->typesToFind[FmMathFuncBase::getClassTypeID()] = true;
  this->verifyCB = FFaDynCB2S(FapUACurrFuncQuery::verify,bool&,FmModelMemberBase*);
}


void FapUAEngineQuery::verify(bool& isOK, FmModelMemberBase* item)
{
  FmEngine* engine = dynamic_cast<FmEngine*>(item);
  isOK = engine && !engine->isControlInEngine();
}


void FapUARoadFuncQuery::verify(bool& isOK, FmModelMemberBase* item)
{
  isOK = false;
  FmMathFuncBase* func = dynamic_cast<FmMathFuncBase*>(item);
  if (func)
    if (func->getFunctionUse() == FmMathFuncBase::ROAD_FUNCTION)
      isOK = true;
}


void FapUAWaveFuncQuery::verify(bool& isOK, FmModelMemberBase* item)
{
  isOK = false;
  FmMathFuncBase* func = dynamic_cast<FmMathFuncBase*>(item);
  if (func)
    if (func->getFunctionUse() == FmMathFuncBase::WAVE_FUNCTION)
      isOK = true;
}


void FapUACurrFuncQuery::verify(bool& isOK, FmModelMemberBase* item)
{
  isOK = false;
  FmMathFuncBase* func = dynamic_cast<FmMathFuncBase*>(item);
  if (func)
    if (func->getFunctionUse() == FmMathFuncBase::CURR_FUNCTION)
      isOK = true;
}


void FapUAQuery::onQIFieldButtonCB(FuiQueryInputFieldValues& v)
{
  if (v.selectedRef)
    FapEventManager::permTotalSelect(static_cast<FFaViewItem*>(v.selectedRef));
}
