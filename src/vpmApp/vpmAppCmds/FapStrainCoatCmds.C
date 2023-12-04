// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapStrainCoatCmds.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "vpmUI/Fui.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdPart.H"
#endif
#include "vpmDB/FmPart.H"
#include "vpmDB/FmElementGroupProxy.H"
#include "vpmDB/FmDB.H"

#include "FFlLib/FFlLinkHandler.H"
#include "FFlLib/FFlVisualization/FFlGroupPartCreator.H"
#ifdef FT_HAS_GRAPHVIEW
#include "FFpLib/FFpFatigue/FFpSNCurveLib.H"
#endif
#include "FFaLib/FFaDefinitions/FFaMsg.H"


void FapStrainCoatCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_StrainCoat_make");
  cmdItem->setText("Generate full Strain Coat");
  cmdItem->setToolTip("Generate full Strain Coat");
  cmdItem->setActivatedCB(FFaDynCB0S(FapStrainCoatCmds::makeFullStrainCoat));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapStrainCoatCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_StrainCoat_selection");
  cmdItem->setText("Generate Strain Coat");
  cmdItem->setToolTip("Generate Strain Coat");
  cmdItem->setActivatedCB(FFaDynCB0S(FapStrainCoatCmds::makeStrainCoatOnSelection));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapStrainCoatCmds::getOnSelectionSensitivity,bool&));
}


void FapStrainCoatCmds::makeFullStrainCoat()
{
  if (!FapLicenseManager::hasDurabilityLicense())
    return;

  Fui::noUserInputPlease();
  FFaMsg::pushStatus("Generating Full Strain Coat");

  std::vector<FmPart*> parts;
  FmDB::getFEParts(parts);
  FapStrainCoatCmds::makeStrainCoat(parts);

  FFaMsg::popStatus();
  Fui::okToGetUserInput();
}


static bool isFEPart(const FmModelMemberBase* obj)
{
  const FmPart* part = dynamic_cast<const FmPart*>(obj);
  if (!part)
    return false;
  else if (part->useGenericProperties.getValue())
    return false;
  else if (part->suppressInSolver.getValue())
    return false;

  return true;
}


void FapStrainCoatCmds::makeStrainCoatOnSelection()
{
  if (!FapLicenseManager::hasDurabilityLicense())
    return;

  std::vector<FmModelMemberBase*> selection;
  if (!FapCmdsBase::getCurrentSelection(selection))
    return;

  Fui::noUserInputPlease();

  std::vector<FmPart*> parts;
  std::vector<FmElementGroupProxy*> groups;
  for (FmModelMemberBase* item : selection)
    if (item->isOfType(FmElementGroupProxy::getClassTypeID()))
      groups.push_back(static_cast<FmElementGroupProxy*>(item));
    else if (isFEPart(item))
      parts.push_back(static_cast<FmPart*>(item));

  if (!groups.empty())
  {
    FFaMsg::pushStatus("Strain coating element groups");
    FapStrainCoatCmds::makeStrainCoat(groups,true);
    FFaMsg::popStatus();
  }

  if (!parts.empty())
  {
    FFaMsg::pushStatus("Strain coating FE parts");
    FapStrainCoatCmds::makeStrainCoat(parts);
    FFaMsg::popStatus();
  }

  Fui::okToGetUserInput();
}


void FapStrainCoatCmds::getSensitivity(bool& isSensitive)
{
  isSensitive = FapLicenseManager::isProEdition();
  if (!isSensitive) return;

  std::vector<FmPart*> parts;
  FmDB::getFEParts(parts);
  isSensitive = !parts.empty();
}


void FapStrainCoatCmds::getOnSelectionSensitivity(bool& isSensitive)
{
  isSensitive = FapLicenseManager::isProEdition();
  if (!isSensitive) return;

  std::vector<FmModelMemberBase*> selection;
  isSensitive = FapCmdsBase::getCurrentSelection(selection);
  if (!isSensitive) return;

  std::vector<FmModelMemberBase*>::iterator it;
  for (it = selection.begin(); it != selection.end();)
    if ((*it)->isOfType(FmElementGroupProxy::getClassTypeID()))
      ++it;
    else if (isFEPart(*it))
      ++it;
    else
      it = selection.erase(it);

  isSensitive = !selection.empty();
}


void FapStrainCoatCmds::makeStrainCoat(const std::vector<FmPart*>& parts)
{
  int ipart = 0;
  FFaMsg::enableSubSteps(parts.size());

  std::set<FmPart*> touchedParts;
  for (FmPart* part : parts)
  {
    FFaMsg::setSubTask(part->baseFTLFile.getValue());
    FFaMsg::setSubStep(++ipart);

    if (FapStrainCoatCmds::makeStrainCoat(part,NULL))
      touchedParts.insert(part);
  }

  FFaMsg::setSubTask("");
  FFaMsg::disableSubSteps();

  for (FmPart* part : touchedParts)
    part->getLinkHandler()->updateGroupVisibilityStatus();
}


void FapStrainCoatCmds::makeStrainCoat(const std::vector<FmElementGroupProxy*>& groups,
				       bool showProgress)
{
  int igroup = 0;
  if (showProgress)
    FFaMsg::enableSubSteps(groups.size());

  std::set<FmPart*> touchedParts;
  for (FmElementGroupProxy* group : groups)
  {
    if (showProgress)
    {
      FFaMsg::setSubTask(group->getUserDescription());
      FFaMsg::setSubStep(++igroup);
    }

    FmPart* part = group->getOwner();
    if (part)
      if (FapStrainCoatCmds::makeStrainCoat(part,group))
	touchedParts.insert(part);
  }

  if (showProgress)
  {
    FFaMsg::setSubTask("");
    FFaMsg::disableSubSteps();
  }

  for (FmPart* part : touchedParts)
    part->getLinkHandler()->updateGroupVisibilityStatus();
}


void FapStrainCoatCmds::makeStrainCoat(FmPart* fmPart)
{
  if (FapStrainCoatCmds::makeStrainCoat(fmPart,0))
    fmPart->getLinkHandler()->updateGroupVisibilityStatus();
}


bool FapStrainCoatCmds::makeStrainCoat(FmPart* fmPart,
				       FmElementGroupProxy* group)
{
  if (!isFEPart(fmPart)) return false;

  bool retVal = false;
#ifdef USE_INVENTOR
  FdPart* fdPart = (FdPart*)fmPart->getFdPointer();
  if (!fdPart) return false;
  if (!fdPart->getGroupPartCreator()) return false;

  FFlFaceGenerator* geometry = fdPart->getGroupPartCreator()->getFaceGenerator();
  FFlLinkHandler*   workPart = fmPart->getLinkHandler();
  if (!geometry || !workPart) return false;

  if (group)
    retVal = workPart->makeStrainCoat(geometry,group->getRealObject());
  else
    retVal = workPart->makeStrainCoat(geometry);
#endif

  if (!group)
  {
    std::vector<FmElementGroupProxy*> groups;
    fmPart->getElementGroups(groups);
    FapStrainCoatCmds::addFatigueProps(groups);
  }
  else if (group->doFatigue())
    FapStrainCoatCmds::addFatigueProps(fmPart,group);

  return retVal;
}


void FapStrainCoatCmds::addFatigueProps(const std::vector<FmElementGroupProxy*>& groups)
{
  for (FmElementGroupProxy* group : groups)
    if (group->doFatigue())
      FapStrainCoatCmds::addFatigueProps(group->getOwner(),group);
}


void FapStrainCoatCmds::addFatigueProps(FmPart* part, FmElementGroupProxy* group)
{
  if (!part) return;

  FFlLinkHandler* workPart = part->getLinkHandler();
  if (!workPart) return;

  int iSNstd = group->myFatigueSNStd.getValue();
  int iCurve = group->myFatigueSNCurve.getValue();
#ifdef FT_HAS_GRAPHVIEW
  ListUI <<"  -> "<< group->getIdString(true) <<" on "
	 << part->getIdString(true) <<"\n     is assigned S-N curve: "
	 << FFpSNCurveLib::instance()->getCurveId(iSNstd,iCurve) <<".\n";

  workPart->assignFatigueProperty(iSNstd,iCurve,
				  group->myFatigueSCF.getValue(),
				  group->getRealObject());
#else
  ListUI <<" --> Ignoring fatigue properties ("<< iSNstd <<","<< iCurve
         <<") from "<< group->getIdString(true)
         <<" on "<< part->getIdString(true) <<"\n";
#endif
}
