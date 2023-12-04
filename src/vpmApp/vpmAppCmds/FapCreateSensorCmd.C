// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapCreateSensorCmd.H"
#include "vpmUI/FuiModes.H"
#include "vpmUI/Fui.H"

#ifdef USE_INVENTOR
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include "vpmDisplay/FdEvent.H"
#include "vpmDisplay/FdPickFilter.H"
#include "vpmDisplay/FdSelector.H"
#include "vpmDisplay/FdTriad.H"
#include "vpmDisplay/FdSimpleJoint.H"
#include "vpmDisplay/FdLinJoint.H"
#include "vpmDisplay/FdCamJoint.H"
#include "vpmDisplay/FdAxialSprDa.H"
#include "vpmDisplay/FdStrainRosette.H"
#endif

#include "vpmDB/FmTriad.H"
#include "vpmDB/FmEngine.H"
#include "vpmDB/FmcInput.H"
#include "vpmDB/FmcOutput.H"
#include "vpmDB/FmJointBase.H"
#include "vpmDB/FmAxialSpring.H"
#include "vpmDB/FmAxialDamper.H"
#include "vpmDB/FmStrainRosette.H"

#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFaLib/FFaDefinitions/FFaViewItem.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


enum {
  START,
  ANY_SELECTED,
  TRIAD_SELECTED,
  TRIAD1_ACCEPTED,
  TRIAD2_SELECTED,
  CREATING
};

int FapCreateSensorCmd::myState = START;


void FapCreateSensorCmd::onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
                                                const std::vector<FFaViewItem*>&,
                                                const std::vector<FFaViewItem*>&)
{
  if (FuiModes::getMode() != FuiModes::CREATE_SENSOR_MODE)
    return;

  FmEngine* e;
  switch (FapCreateSensorCmd::myState)
    {
    case START:
    case ANY_SELECTED:
    case TRIAD_SELECTED:
      if (totalSelection.empty())
        FapCreateSensorCmd::setState(START);
      else if (dynamic_cast<FmTriad*>(totalSelection[0]))
        FapCreateSensorCmd::setState(TRIAD_SELECTED);
      else if (((e = dynamic_cast<FmEngine*> (totalSelection[0])) && e != myEngine) ||
               dynamic_cast<FmJointBase*>    (totalSelection[0]) ||
               dynamic_cast<FmAxialSpring*>  (totalSelection[0]) ||
               dynamic_cast<FmAxialDamper*>  (totalSelection[0]) ||
               dynamic_cast<FmStrainRosette*>(totalSelection[0]) ||
               dynamic_cast<FmcOutput*>      (totalSelection[0]))
        FapCreateSensorCmd::setState(ANY_SELECTED);
      else
        FapCreateSensorCmd::setState(START);
      break;

    case TRIAD1_ACCEPTED:
      if (!totalSelection.empty() && dynamic_cast<FmTriad*>(totalSelection[0]))
        FapCreateSensorCmd::setState(TRIAD2_SELECTED);
      break;

    case TRIAD2_SELECTED:
      if (totalSelection.size() > 1 && dynamic_cast<FmTriad*>(totalSelection[1]))
        FapCreateSensorCmd::setState(TRIAD2_SELECTED);
      else
        FapCreateSensorCmd::setState(TRIAD1_ACCEPTED);
    }
}


void FapCreateSensorCmd::createSensor(unsigned int iArg)
{
  myArg = iArg;
  myEngine = dynamic_cast<FmEngine*>(FapEventManager::getFirstPermSelectedObject());
  if (!myEngine)
  {
    FmcInput* in = dynamic_cast<FmcInput*>(FapEventManager::getFirstPermSelectedObject());
    if (in) myEngine = in->getEngine();
  }

  if (myEngine)
    FuiModes::setMode(FuiModes::CREATE_SENSOR_MODE);
}


void FapCreateSensorCmd::enterMode()
{
  FapEventManager::pushPermSelection();
#ifdef USE_INVENTOR
  FdEvent::addEventCB(FapCreateSensorCmd::eventCB);
#endif
  FapCreateSensorCmd::setState(START); // To get the tip set right
}


void FapCreateSensorCmd::cancelMode()
{
#ifdef USE_INVENTOR
  FdEvent::removeEventCB(FapCreateSensorCmd::eventCB);
#endif
  if (FapEventManager::hasStackedSelections())
    FapEventManager::popPermSelection();

  FapCreateSensorCmd::myState = START;
}


void FapCreateSensorCmd::setState(int newState)
{
  FapCreateSensorCmd::myState = newState;

  switch (FapCreateSensorCmd::myState)
    {
    case START:
      Fui::tip("Select argument from the 3D view or the objects browser");
      break;
    case TRIAD_SELECTED:
      Fui::tip("Accept argument by pressing Done, or select a different object");
      break;
    case TRIAD1_ACCEPTED:
      Fui::tip("Accept Triad as argument by pressing Done, or select Triad 2 to create a relative sensor");
      break;
    case ANY_SELECTED:
      Fui::tip("Accept argument by pressing Done, or select a different object");
      break;
    case TRIAD2_SELECTED:
      Fui::tip("Accept by pressing Done, or select a different Triad");
      break;
    case CREATING:
      Fui::tip("Creating Sensor ...");
      break;
    }
}


void FapCreateSensorCmd::done()
{
  switch (FapCreateSensorCmd::myState)
    {
    case START:
      FuiModes::cancel();
      break;
    case ANY_SELECTED:
      FapCreateSensorCmd::createSensor(dynamic_cast<FmIsMeasuredBase*>(FapEventManager::getFirstPermSelectedObject()));
      FapEventManager::permUnselectAll();
      FuiModes::cancel();
      break;
    case TRIAD_SELECTED:
      FapEventManager::pushPermSelection();
      FapCreateSensorCmd::setState(TRIAD1_ACCEPTED);
      break;
    case TRIAD1_ACCEPTED:
      FapEventManager::popPermSelection();
      FapCreateSensorCmd::createSensor(dynamic_cast<FmIsMeasuredBase*>(FapEventManager::getFirstPermSelectedObject()));
      FapEventManager::permUnselectAll();
      FuiModes::cancel();
      break;
    case TRIAD2_SELECTED:
      {
        FmTriad* t1 = dynamic_cast<FmTriad*>(FapEventManager::getFirstPermSelectedObject());
        FapEventManager::popPermSelection();
        FmTriad* t2 = dynamic_cast<FmTriad*>(FapEventManager::getFirstPermSelectedObject());
        FapCreateSensorCmd::createSensor(t1,t2);
        FapEventManager::permUnselectAll();
        FuiModes::cancel();
      }
      break;
    default:
      FuiModes::cancel();
      break;
    }
}


#ifdef USE_INVENTOR
void FapCreateSensorCmd::eventCB(void*, SoEventCallback* eventCallbackNode)
{
  const SoEvent* event = eventCallbackNode->getEvent();
  if (!event) return;
  if (!event->isOfType(SoMouseButtonEvent::getClassTypeId())) return;

  if (SoMouseButtonEvent::isButtonPressEvent(event,SoMouseButtonEvent::BUTTON1))
  {
    SoHandleEventAction* evHaAction = eventCallbackNode->getAction();

    std::vector<FdObject*> selectedObjects;
    FdSelector::getSelectedObjects(selectedObjects);

    // Build array of interesting types
    std::vector<int> types(6,FdTriad::getClassTypeID());
    types[1] = FdSimpleJoint::getClassTypeID();
    types[2] = FdLinJoint::getClassTypeID();
    types[3] = FdCamJoint::getClassTypeID();
    types[4] = FdAxialSprDa::getClassTypeID();
    types[5] = FdStrainRosette::getClassTypeID();

    long int  indexToInterestingPP    = -1;
    bool      wasASelectedObjInPPList = false;
    FdObject* pickedObject = FdPickFilter::getInterestingPObj(&evHaAction->getPickedPointList(),
							      selectedObjects, // This is to select objects behind the already selected one
							      types,true, // Filter variables
							      indexToInterestingPP,wasASelectedObjInPPList); // Variables returning values
    if (pickedObject)
      FapEventManager::permTotalSelect(pickedObject->getFmOwner());
    else
      FapEventManager::permUnselectAll();
  }
  else if (!SoMouseButtonEvent::isButtonReleaseEvent(event,SoMouseButtonEvent::BUTTON1))
    return;

  eventCallbackNode->setHandled();
}
#else
void FapCreateSensorCmd::eventCB(void*, SoEventCallback*) {}
#endif


void FapCreateSensorCmd::createSensor(FmIsMeasuredBase* obj)
{
  if (!obj) return;

  FmSensorBase* sens = obj->getSimpleSensor(true);

  // If we are dealing with a control output object, we have to bypass
  // its sensor and use a sensor on the auto-created engine associated with it
  if (obj->isOfType(FmcOutput::getClassTypeID()))
  {
    FmEngine* engine = static_cast<FmcOutput*>(obj)->getEngine();
    if (engine) sens = engine->getSimpleSensor(true);
  }

  ListUI <<"Creating "<< sens->getUserDescription() <<"\n";

  if (FapCreateSensorCmd::instance()->myEngine)
    FapCreateSensorCmd::instance()->myEngine->setSensor(sens,FapCreateSensorCmd::instance()->myArg);
}


void FapCreateSensorCmd::createSensor(FmTriad* t1, FmTriad* t2)
{
  if (!t1 || !t2 || t1 == t2)
  {
    ListUI <<"ERROR: Relative sensors should be used on different objects.\n";
    ListUI <<"       Could not create relative sensor.\n";
    return;
  }

  FmSensorBase* sens = t1->getRelativeSensor(t2,true);
  ListUI <<"Creating "<< sens->getUserDescription() <<"\n";

  if (FapCreateSensorCmd::instance()->myEngine)
    FapCreateSensorCmd::instance()->myEngine->setSensor(sens,FapCreateSensorCmd::instance()->myArg);
}
