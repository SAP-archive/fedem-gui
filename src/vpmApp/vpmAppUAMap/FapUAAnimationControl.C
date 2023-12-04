// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAAnimationControl.H"
#include "vpmApp/vpmAppUAMap/FapUAQuery.H"
#include "vpmApp/vpmAppDisplay/FFaLegendMapper.H"
#include "vpmUI/vpmUITopLevels/FuiAnimationControl.H"
#include "vpmUI/Fui.H"
#include "vpmDB/FmAnimation.H"


Fmd_SOURCE_INIT(FAPUAANIMATIONCONTROL, FapUAAnimationControl, FapUAExistenceHandler);

//----------------------------------------------------------------------------

FapUAAnimationControl::FapUAAnimationControl(FuiAnimationControl* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic),
    signalConnector(this)
{
  Fmd_CONSTRUCTOR_INIT(FapUAAnimationControl);
  this->ui = uic;
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAAnimationControl::createValuesObject()
{
  return new FuaAnimationControlValues();
}
//----------------------------------------------------------------------------

void FapUAAnimationControl::setDBValues(FFuaUIValues* values)
{
  FmAnimation* dbanimation = FapEventManager::getActiveAnimation();
  if (!dbanimation) return;

  FuaAnimationControlValues* animValues = (FuaAnimationControlValues*) values;

  // Follow-me camera
  dbanimation->linkToFollow = static_cast<FmLink*>(animValues->myLinkToFollow);

  // motion
  dbanimation->showLinkMotion = animValues->linkMotion;
  dbanimation->showTriadMotion = animValues->triadMotion;

  // def
  dbanimation->showDeformation = animValues->def;
  dbanimation->deformationScale = animValues->defScale;

  // legend
  dbanimation->showFringes = animValues->fringe;
  dbanimation->showLegend = animValues->legend;
  dbanimation->colorMappingOpName = animValues->selLegendColor;
  dbanimation->legendMappingOpName = animValues->selLegendMapping;
  dbanimation->smoothLegend = (animValues->selLegendLook == "Smooth");
  dbanimation->legendRange = animValues->legendRange;

  // tick marks
  dbanimation->useLegendTickCount = animValues->tickMarkCount;
  dbanimation->legendTickCount = animValues->tickMarkCountVal;
  dbanimation->legendTickSpacing = animValues->tickMarkSpacingVal;

  dbanimation->onChanged(); //dynamic update
}
//----------------------------------------------------------------------------

void FapUAAnimationControl::getDBValues(FFuaUIValues* values)
{
  FmAnimation* dbanimation = FapEventManager::getActiveAnimation();
  if (!dbanimation) return;

  FuaAnimationControlValues* animValues = (FuaAnimationControlValues*) values;

  // Follow-me camera
  animValues->myLinkToFollow = dbanimation->linkToFollow;
  animValues->myLinkQuery = FapUALinkQuery::instance();

  // motion
  animValues->linkMotion = dbanimation->showLinkMotion.getValue();
  animValues->triadMotion = dbanimation->showTriadMotion.getValue();

  // def
  animValues->def = dbanimation->showDeformation.getValue();
  animValues->defScale = dbanimation->deformationScale.getValue();
  animValues->defScalePossible = !dbanimation->isModesAnimation.getValue();

  // legend
  animValues->fringe = dbanimation->showFringes.getValue();
  animValues->legend = dbanimation->showLegend.getValue();
  animValues->selLegendColor = dbanimation->colorMappingOpName.getValue();
  animValues->selLegendMapping = dbanimation->legendMappingOpName.getValue();
  if (dbanimation->smoothLegend.getValue())
    animValues->selLegendLook = "Smooth";
  else
    animValues->selLegendLook = "Discrete";
  animValues->legendRange = dbanimation->legendRange.getValue();

  // tick marks
  animValues->tickMarkCount = dbanimation->useLegendTickCount.getValue();
  animValues->tickMarkCountVal = dbanimation->legendTickCount.getValue();
  animValues->tickMarkSpacingVal = dbanimation->legendTickSpacing.getValue();

  // Option Menues fill-in
  // static content
  animValues->legendLooks.clear();
  animValues->legendLooks.push_back("Discrete");
  animValues->legendLooks.push_back("Smooth");

  // operations
  std::vector<std::string> opers;
  FFaLegendMapper::getColorMappingNames(opers);
  animValues->legendColors = opers;

  opers.clear();
  FFaLegendMapper::getValueMappingNames(opers);
  animValues->legendMappings = opers;
}
//----------------------------------------------------------------------------

void FapUAAnimationControl::finishUI()
{
  Fui::animationControlUI(false,true);
}
//----------------------------------------------------------------------------

void FapUAAnimationControl::onActiveAnimationChanged(FmAnimation* newActive, FmAnimation*)
{
  if (newActive) this->ui->setSensitivity(true);

  this->updateUIValues();

  if (!newActive) this->ui->setSensitivity(false);
}
//----------------------------------------------------------------------------
