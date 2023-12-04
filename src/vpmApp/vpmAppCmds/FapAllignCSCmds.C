// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapAllignCSCmds.H"
#include "vpmApp/FapEventManager.H"

#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaDefinitions/FFaViewItem.H"
#include "FFaLib/FFaString/FFaStringExt.H"

#include "vpmUI/Icons/AllignCS_xpm.xpm"
#include "vpmUI/Icons/AllignCSRotation_xpm.xpm"

#include "vpmUI/FuiModes.H"
#include "vpmUI/Fui.H"
#include "vpmDB/FmTriad.H"

#ifdef USE_INVENTOR
#include "vpmDisplay/FdTriad.H"
#include "vpmDisplay/FdLink.H"
#include "vpmDisplay/FdSimpleJoint.H"
#include "vpmDisplay/FdRefPlane.H"
#include "vpmDisplay/FdEvent.H"
#include "vpmDisplay/FdConverter.H"
#include "vpmDisplay/FdPickFilter.H"
#include "vpmDisplay/FdExtraGraphics.H"

#include <Inventor/SbRotation.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#endif

FaMat34 FapAllignCSCmds::ourAllignCS;
int FapAllignCSCmds::myState = 0;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: It is spelled "align" with a single "l". The text menu and top texts
// should be correct at least. Method- and other symbol names do not have to.
//----------------------------------------------------------------------------

void FapAllignCSCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_allignCS");
  cmdItem->setSmallIcon(AllignCS_xpm);
  cmdItem->setText("Align CS");
  cmdItem->setToolTip("Align object to a coordinate system");
  cmdItem->setActivatedCB(FFaDynCB0S(FapAllignCSCmds::allignCS));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapAllignCSCmds::getSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mech3DObj_allignRotations");
  cmdItem->setSmallIcon(AllignCSRotation_xpm);
  cmdItem->setText("Align rotations");
  cmdItem->setToolTip("Align orientation of an object to a coordinate system");
  cmdItem->setActivatedCB(FFaDynCB0S(FapAllignCSCmds::allignRotations));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapAllignCSCmds::getSensitivity,bool&));
}
//----------------------------------------------------------------------------

void FapAllignCSCmds::enterMode()
{
  FapEventManager::permUnselectAll();
#ifdef USE_INVENTOR
  FdEvent::addEventCB(FapAllignCSCmds::eventCB);
#endif
  FapAllignCSCmds::myState = 0;
  FapAllignCSCmds::setState(0);
}

void FapAllignCSCmds::cancelMode()
{
  FapEventManager::permUnselectAll();
#ifdef USE_INVENTOR
  FdExtraGraphics::hideCS();
  FdEvent::removeEventCB(FapAllignCSCmds::eventCB);
#endif
  FapAllignCSCmds::myState = 0;
}


void FapAllignCSCmds::setState(int newState)
{
  switch (FapAllignCSCmds::myState)
    {
    case 0:
      break;
    case 1:
      if (newState == 2)
	FapAllignCSCmds::ourAllignCS.setIdentity();
      break;
    case 2:
      if (newState == 0)
        {
          if (FuiModes::getMode() == FuiModes::ALLIGNCS_MODE)
            FapAllignCSCmds::allignCS(FapAllignCSCmds::ourAllignCS);
          if (FuiModes::getMode() == FuiModes::ALLIGNROT_MODE)
            FapAllignCSCmds::allignRotations(FapAllignCSCmds::ourAllignCS);

          FapEventManager::permUnselectAll();
#ifdef USE_INVENTOR
          FdExtraGraphics::hideCS();
#endif
        }
      break;
    }

  FapAllignCSCmds::myState = newState;

  switch (FuiModes::getMode())
    {
    case FuiModes::ALLIGNCS_MODE:
      switch (FapAllignCSCmds::myState)
        {
        case 0:
          Fui::tip("Select an object to align");
          break;
        case 1:
          Fui::tip("Select another object, or press and hold the <Ctrl>-Key to add objects to selection (Done when ready).");
          break;
        case 2:
          Fui::tip("Select a coordinate system to align to (Done when ready).");
          break;
        }
      break;
    case FuiModes::ALLIGNROT_MODE:
      switch (FapAllignCSCmds::myState)
        {
        case 0:
          Fui::tip("Select an object to rotate");
          break;
        case 1:
          Fui::tip("Select another object, or press and hold the <Ctrl>-Key to add objects to selection (Done when ready).");
          break;
        case 2:
          Fui::tip("Select a coordinate system to align the rotations to (Done when ready).");
          break;
        }
      break;
    default:
      break;
    }
}


void FapAllignCSCmds::allignCSDone()
{
 switch (FapAllignCSCmds::myState)
    {
    case 0:
      FuiModes::cancel();
      break;
    case 1:
      FapAllignCSCmds::setState(2);
      break;
    case 2:
      FapAllignCSCmds::setState(0);
      break;
    default:
      FuiModes::cancel();
      break;
    }
}


void FapAllignCSCmds::getSensitivity(bool& isSensitive)
{
  FapCmdsBase::isModelEditable(isSensitive);
  if (!isSensitive) return;

  FapCmdsBase::isModellerActive(isSensitive);
}

//----------------------------------------------------------------------------

#ifdef USE_INVENTOR
void FapAllignCSCmds::eventCB(void*, SoEventCallback* eventCallbackNode)
{
  const SoEvent* event = eventCallbackNode->getEvent();
  if (!event) return;

  if (!event->isOfType(SoMouseButtonEvent::getClassTypeId())) return;

  if (SoMouseButtonEvent::isButtonPressEvent(event,SoMouseButtonEvent::BUTTON1))
  {
    SoHandleEventAction* evHaAction = eventCallbackNode->getAction();

    int state = FapAllignCSCmds::myState;
    if (state == 0 || state == 1)
    {
      // Build Array of Interesting or non-interesting types:
      long indexToInterestingPP = -1;
      bool typesIsInteresting = true;
      std::vector<int> types(4,FdLink::getClassTypeID());
      types[1] = FdTriad::getClassTypeID();
      types[2] = FdSimpleJoint::getClassTypeID();
      types[3] = FdRefPlane::getClassTypeID();
      FdObject* pickedObject = FdPickFilter::getCyceledInterestingPObj(&(evHaAction->getPickedPointList()),
								       types,typesIsInteresting,
								       indexToInterestingPP);

      // Filter triads in LinJoints, moving them would mess up too much yet

      if (pickedObject)
	if (pickedObject->isOfType(FdTriad::getClassTypeID()))
	  if (((FmTriad*)pickedObject->getFmOwner())->isInLinJoint())
	    pickedObject = NULL;

      if (!event->wasCtrlDown())
	FapEventManager::permUnselectLast();

      if (pickedObject) {
	if (FapEventManager::isPermSelected(pickedObject->getFmOwner()))
	  FapEventManager::permUnselect(pickedObject->getFmOwner()); // Deselect previously selected instance
	// to put it as the last one selected
	FapEventManager::permSelect(pickedObject->getFmOwner());
	FapAllignCSCmds::setState(1);
      }
      else
	FapAllignCSCmds::setState(0);
    }
    else
    {
      long indexToInterestingPP = -1;
      bool typesIsInteresting = false;
      std::vector<int> types;
      FdObject* pickedObject = FdPickFilter::getCyceledInterestingPObj(&(evHaAction->getPickedPointList()),
								       types,typesIsInteresting,
								       indexToInterestingPP);
      if (pickedObject)
      {
	SoPickedPoint* interestingPickedPoint = evHaAction->getPickedPointList()[indexToInterestingPP];
	SoPath* path = interestingPickedPoint->getPath();

	// Get hit point on object in object space:
	// Get Object to world transformation:

	SoNode* tail = ((SoFullPath*)path)->getTail();
	SbMatrix SbObjToWorld = interestingPickedPoint->getObjectToWorld(tail);
	SbRotation scaleOrient, rotation;
	SbVec3f scale, translation;
	SbObjToWorld.getTransform(translation, rotation, scale, scaleOrient);
	SbMatrix SbObjToWorldUnscaled;
	SbObjToWorldUnscaled.setTransform(translation,rotation, SbVec3f());

	FaMat34 objToWorld = FdConverter::toFaMat34(SbObjToWorld);
	objToWorld[0].normalize();
	objToWorld[1].normalize();
	objToWorld[2].normalize();
	FdExtraGraphics::showCS(objToWorld);

	FapAllignCSCmds::ourAllignCS = objToWorld;

	FapAllignCSCmds::setState(2);
      }
    }
    eventCallbackNode->setHandled();
  }
  else if (SoMouseButtonEvent::isButtonReleaseEvent(event,SoMouseButtonEvent::BUTTON1))
  {
    // Do not send this event to the IV graph because
    // the SoSelection (selectionRoot) will handle it
    // and deselect what it should not.
    eventCallbackNode->setHandled();
  }
}
#else
void FapAllignCSCmds::eventCB(void*, SoEventCallback*) {}
#endif


void FapAllignCSCmds::allignCS()
{
  FuiModes::setMode(FuiModes::ALLIGNCS_MODE);
}


void FapAllignCSCmds::allignCS(const FaMat34& mx)
{
  std::vector<FFaViewItem*> selection;
  FFaViewItem* tmpSelection = NULL;
  FapEventManager::getSelection(selection,tmpSelection);

  std::string unMovables;
  FmIsPositionedBase* posBase;
  for (FFaViewItem* item : selection)
    if ((posBase = dynamic_cast<FmIsPositionedBase*>(item))) {
      if (posBase->isTranslatable() && posBase->isRotatable())
      {
	posBase->setGlobalCS(mx,true);
	posBase->updateDisplayTopology();
      }
      else if (posBase->isTranslatable())
      {
	// Only translate (mainly slave triads in simple joints)
	FaMat34 orgPos = posBase->getGlobalCS();
	orgPos[3] = mx[3];
	posBase->setGlobalCS(orgPos,true);
	posBase->updateDisplayTopology();
	unMovables += std::string("\t") + posBase->getUITypeName()
	  + FFaNumStr(" [%d] ",posBase->getID())
	  + posBase->getUserDescription() + " (Rotation locked) \n";
      }
      else
	unMovables += std::string("\t") + posBase->getUITypeName()
	  + FFaNumStr(" [%d] ",posBase->getID())
	  + posBase->getUserDescription() + "\n";
    }

  if (!unMovables.empty())
    Fui::dismissDialog(("The following objects can not be moved:\n"+unMovables).c_str());
}


void FapAllignCSCmds::allignRotations()
{
  FuiModes::setMode(FuiModes::ALLIGNROT_MODE);
}


void FapAllignCSCmds::allignRotations(const FaMat34& mx)
{
  std::vector<FFaViewItem*> selection;
  FFaViewItem* tmpSelection = NULL;
  FapEventManager::getSelection(selection,tmpSelection);

  FaMat34 rotMx(mx);
  std::string unMovables;
  FmIsPositionedBase* posBase;
  for (FFaViewItem* item : selection)
    if ((posBase = dynamic_cast<FmIsPositionedBase*>(item))) {
      if (posBase->isRotatable())
      {
	rotMx[3] = posBase->getGlobalCS().translation();
	posBase->setGlobalCS(rotMx,true);
	posBase->updateDisplayTopology();
      }
      else
	unMovables += std::string("\t") + posBase->getUITypeName()
	  + FFaNumStr(" [%d] ",posBase->getID())
	  + posBase->getUserDescription() + "\n";
    }

  if (!unMovables.empty())
    Fui::dismissDialog(("The following objects can not be rotated:\n"+unMovables).c_str());
}
