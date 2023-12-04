// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAAppearance.H"
#include "vpmUI/vpmUITopLevels/FuiAppearance.H"
#include "vpmUI/FuiModes.H"
#include "vpmDB/FmRefPlane.H"
#include "vpmDB/FmSeaState.H"
#include "vpmDB/FmLink.H"
#include "vpmPM/FpPM.H"


Fmd_SOURCE_INIT(FAPUAAPPEARANCE, FapUAAppearance, FapUAExistenceHandler);


FapUAAppearance::FapUAAppearance(FuiAppearance* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), FapUAFinishHandler(uic),
    signalConnector(this)
{
  Fmd_CONSTRUCTOR_INIT(FapUAAppearance);

  myAppearanceUI = uic;

  myRefPlaneLODText.push_back("n/a");

  myLinkLODText.push_back("Surface and Internals");
  myLinkLODText.push_back("Reduced Surface and Internals");
  myLinkLODText.push_back("Surface");
  myLinkLODText.push_back("Reduced Surface");
  myLinkLODText.push_back("Off");

  myLinesLODText.push_back("Full");
  myLinesLODText.push_back("Surface");
  myLinesLODText.push_back("Outline");
  myLinesLODText.push_back("Outline No 1D-Elements");
  myLinesLODText.push_back("Simplified");
  myLinesLODText.push_back("Off");

  myGenPPolyLODText.push_back("On");
  myGenPPolyLODText.push_back("Off");

  myGenPLinesLODText.push_back("Simplified");
  myGenPLinesLODText.push_back("Off");

  myCadGenPLinesLODText.push_back("Outline");
  myCadGenPLinesLODText.push_back("Simplified");
  myCadGenPLinesLODText.push_back("Off");
}


FFuaUIValues* FapUAAppearance::createValuesObject()
{
  return new FuaAppearanceValues();
}


void FapUAAppearance::finishUI()
{
  FuiModes::cancel();
}


void FapUAAppearance::getDBValues(FFuaUIValues* values)
{
  FuaAppearanceValues* appVals = (FuaAppearanceValues*) values;
  if (myCurrentObj->isOfType(FmLink::getClassTypeID()))
    {
      FmLink* link = (FmLink*)myCurrentObj;

      appVals->myColor        = link->getRGBColor();
      appVals->myShininess    = (int)(link->getShininess()*100.0);
      appVals->myTransparency = (int)(link->getTransparency()*100.0);

      if (link->isUsingGenPartVis())
        {
          if (link->isCADLoaded())
            switch (link->getMeshType()) {
            case FmLink::FULL:
            case FmLink::SURFACE:
            case FmLink::REDUCED:
            case FmLink::REDUCED_NO1D:
              appVals->myLinesValue = 0;
              break;
            case FmLink::SIMPLIFIED:
              appVals->myLinesValue = 1;
              break;
            case FmLink::OFF:
              appVals->myLinesValue = 2;
              break;
            default:
              break;
            }
          else
            switch (link->getMeshType()) {
            case FmLink::FULL:
            case FmLink::SURFACE:
            case FmLink::REDUCED:
            case FmLink::REDUCED_NO1D:
            case FmLink::SIMPLIFIED:
              appVals->myLinesValue = 0;
              break;
            case FmLink::OFF:
              appVals->myLinesValue = 1;
              break;
            default:
              break;
            }

          switch (link->getModelType())
            {
            case FmLink::FULL:
            case FmLink::RED_FULL:
            case FmLink::SURFACE:
            case FmLink::REDUCED:
              appVals->myPolygonsValue = 0;
              break;
            case FmLink::OFF:
              appVals->myPolygonsValue = 1;
              break;
            default:
              break;
            }
        }
      else
        {
          switch (link->getMeshType())
            {
            case FmLink::FULL:
              appVals->myLinesValue = 0;
              break;
            case FmLink::SURFACE:
              appVals->myLinesValue = 1;
              break;
            case FmLink::REDUCED:
              appVals->myLinesValue = 2;
              break;
            case FmLink::REDUCED_NO1D:
              appVals->myLinesValue = 3;
              break;
            case FmLink::SIMPLIFIED:
              appVals->myLinesValue = 4;
              break;
            case FmLink::OFF:
              appVals->myLinesValue = 5;
              break;
            default:
              break;
            }

          switch (link->getModelType())
            {
            case FmLink::FULL:
              appVals->myPolygonsValue = 0;
              break;
            case FmLink::RED_FULL:
              appVals->myPolygonsValue = 1;
              break;
            case FmLink::SURFACE:
              appVals->myPolygonsValue = 2;
              break;
            case FmLink::REDUCED:
              appVals->myPolygonsValue = 3;
              break;
            case FmLink::OFF:
              appVals->myPolygonsValue = 4;
              break;
            default:
              break;
            }
        }
    }

  else if (myCurrentObj->isOfType(FmRefPlane::getClassTypeID()))
    {
      FmRefPlane* refp = (FmRefPlane*)myCurrentObj;

      appVals->myColor        = refp->getRGBColor();
      appVals->myTransparency = (int)(refp->getTransparency()*100.0);
    }
  else if (myCurrentObj->isOfType(FmSeaState::getClassTypeID()))
    {
      FmSeaState* seastate = (FmSeaState*)myCurrentObj;

      appVals->myColor        = seastate->getRGBColor();
      appVals->myTransparency = (int)(seastate->getTransparency()*100.0);
    }
}


void FapUAAppearance::setDBValues(FFuaUIValues* values)
{
  FuaAppearanceValues* appVals = (FuaAppearanceValues*) values;
  for (FmModelMemberBase* obj : FapEventManager::getPermMMBSelection())
    if (obj->isOfType(FmLink::getClassTypeID()))
      {
	FmLink* link = (FmLink*)obj;
	if (appVals->isColorChanged)
	  if (link->setRGBColor(appVals->myColor))
	    FpPM::touchModel();

	if (appVals->isShininessChanged)
	  if (link->setShininess(((double)appVals->myShininess)/100))
	    FpPM::touchModel();

	if (appVals->isTransparencyChanged)
	  if (link->setTransparency(((double)appVals->myTransparency)/100))
	    FpPM::touchModel();

	if (appVals->isPolygonsChanged)
	  {
	    FmLink::Detail det = FmLink::REDUCED;
	    if (link->isUsingGenPartVis())
	      {
		det = link->getModelType();
		// Turn on if Off, Turn off if on,  Don't tuch othervise.
		if (appVals->myPolygonsValue == 0 && det == FmLink::OFF)
		  det = FmLink::REDUCED;
		else if (appVals->myPolygonsValue == 1 && det != FmLink::OFF)
		  det = FmLink::OFF;
	      }
	    else
	      switch (appVals->myPolygonsValue)
		{
		case 0:
		  det = FmLink::FULL;
		  break;
		case 1:
		  det = FmLink::RED_FULL;
		  break;
		case 2:
		  det = FmLink::SURFACE;
		  break;
		case 3:
		  det = FmLink::REDUCED;
		  break;
		case 4:
		  det = FmLink::OFF;
		  break;
		}

	    if (link->setModelType(det))
	      FpPM::touchModel();
	  }

	if (appVals->isLinesChanged)
	  {
	    FmLink::Detail det = FmLink::REDUCED;
	    if (link->isUsingGenPartVis())
	      {
		det = link->getMeshType();
                if (link->isCADLoaded())
                {
                  if (appVals->myLinesValue == 0 && (det == FmLink::OFF || det == FmLink::SIMPLIFIED))
                    det = FmLink::REDUCED;
                  else if (appVals->myLinesValue == 1)
                    det = FmLink::SIMPLIFIED;
                  else if (appVals->myLinesValue == 2)
                    det = FmLink::OFF;
                }
                else{
                  // Turn on if Off, Turn off if on, don't touch othervise.
                  if (appVals->myLinesValue == 0 && det == FmLink::OFF)
                    det = FmLink::SIMPLIFIED;
                  else if (appVals->myLinesValue == 1 && det != FmLink::OFF)
                    det = FmLink::OFF;
                }
            }
            else
	      switch (appVals->myLinesValue)
		{
		case 0:
		  det = FmLink::FULL;
		  break;
		case 1:
		  det = FmLink::SURFACE;
		  break;
		case 2:
		  det = FmLink::REDUCED;
		  break;
		case 3:
		  det = FmLink::REDUCED_NO1D;
		  break;
		case 4:
		  det = FmLink::SIMPLIFIED;
		  break;
		case 5:
		  det = FmLink::OFF;
		  break;
		}

	    if (link->setMeshType(det))
	      FpPM::touchModel();
	  }
      }

    else if (obj->isOfType(FmRefPlane::getClassTypeID()))
      {
	FmRefPlane* refp = (FmRefPlane*)obj;
	if (appVals->isColorChanged)
	  if (refp->setRGBColor(appVals->myColor))
	    FpPM::touchModel();

	if (appVals->isTransparencyChanged)
	  if (refp->setTransparency(((double)appVals->myTransparency)/100))
	    FpPM::touchModel();
      }

    else if (obj->isOfType(FmSeaState::getClassTypeID()))
      {
	FmSeaState* seastate = (FmSeaState*)obj;
	if (appVals->isColorChanged)
	  if (seastate->setRGBColor(appVals->myColor))
	    FpPM::touchModel();

	if (appVals->isTransparencyChanged)
	  if (seastate->setTransparency(((double)appVals->myTransparency)/100))
	    FpPM::touchModel();
      }
}


void FapUAAppearance::onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
					     const std::vector<FFaViewItem*>&,
					     const std::vector<FFaViewItem*>&)
{
  // Ignore signal if not in appearance mode
  if (FuiModes::getMode() != FuiModes::APPEARANCE_MODE)
    return;

  // Show last selected one if model member
  if (totalSelection.empty())
    myCurrentObj = NULL;
  else
    myCurrentObj = dynamic_cast<FmIsRenderedBase*>(totalSelection.back());

  if (!myCurrentObj)
    myAppearanceUI->popDown();
  else if (myCurrentObj->isOfType(FmLink::getClassTypeID()))
  {
    if (((FmLink*)myCurrentObj)->isUsingGenPartVis())
    {
      myAppearanceUI->setPolygonLODText(myGenPPolyLODText);
      if (((FmLink*)myCurrentObj)->isCADLoaded())
        myAppearanceUI->setLinesLODText(myCadGenPLinesLODText);
      else
        myAppearanceUI->setLinesLODText(myGenPLinesLODText);
      myAppearanceUI->disableAdvancedOptions(false);
    }
    else {
      myAppearanceUI->setPolygonLODText(myLinkLODText);
      myAppearanceUI->setLinesLODText(myLinesLODText);
      myAppearanceUI->disableAdvancedOptions(false);
    }
    this->updateUIValues();
    myAppearanceUI->popUp();
  }
  else if (myCurrentObj->isOfType(FmRefPlane::getClassTypeID()) ||
           myCurrentObj->isOfType(FmSeaState::getClassTypeID()))
  {
    myAppearanceUI->setPolygonLODText(myRefPlaneLODText);
    myAppearanceUI->setLinesLODText(myRefPlaneLODText);
    myAppearanceUI->disableAdvancedOptions(true);
    this->updateUIValues();
    myAppearanceUI->popUp();
  }
}
