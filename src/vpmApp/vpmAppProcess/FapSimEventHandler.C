// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapGraphCmds.H"

#include "vpmPM/FpModelRDBHandler.H"
#include "vpmPM/FpPM.H"

#include "vpmUI/Fui.H"

#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmDB.H"

#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "FFaLib/FFaString/FFaStringExt.H"


FmSimulationEvent* FapSimEventHandler::ourActiveEvent = 0;


bool FapSimEventHandler::activate(FmSimulationEvent* selectedEvent,
				  bool closeRDB, bool reOpenRDB)
{
  if (selectedEvent == ourActiveEvent) return false;

  if (closeRDB)
  {
    // Renew the result extractor retaining only the reducer files, if any
    FpModelRDBHandler::RDBRelease();

    // Close all views that are result-dependent
    FapGraphCmds::killAllGraphViews();
    Fui::resultFileBrowserUI(false);
  }

  // Now we can actually do the event switch
  bool notify = closeRDB && !selectedEvent;
  if (ourActiveEvent) ourActiveEvent->activate(false,notify);
  if (selectedEvent)  selectedEvent->activate(true,closeRDB);
  ourActiveEvent = selectedEvent;

  if (closeRDB && reOpenRDB)
  {
    // Open the result database associated with selected event
    FpModelRDBHandler::RDBOpen(FapSimEventHandler::getActiveRSD(),
			       FmDB::getMechanismObject());
    // Note that we don't update the initial RSD object on this Open,
    // unless it's the first time we open this event in current session.
    // Thus, all sub-tasks remain intact on disk for all events
    // until the next Save, SaveAs or Close action.
    if (ourActiveEvent && !ourActiveEvent->isTouched())
      ourActiveEvent->getResultStatusData(false)->copy(ourActiveEvent->getResultStatusData());
    if (ourActiveEvent)
      ourActiveEvent->onChanged(); // for updating list view pixmap
  }

  if (closeRDB)
    FpPM::updateGuiTitle(); // the event ID is printed in the window frame

  return true;
}


int FapSimEventHandler::getActiveEventID()
{
  return ourActiveEvent ? ourActiveEvent->getID() : 0;
}


FmResultStatusData* FapSimEventHandler::getActiveRSD(bool current)
{
  if (ourActiveEvent)
    return ourActiveEvent->getResultStatusData(current);

  FmMechanism* mech = FmDB::getMechanismObject(false);
  return mech ? mech->getResultStatusData(current) : 0;
}


/*!
  Checks if any of the events have results in their RSD object.
  \note We do not check for consistency between the RSD objects and
  the contents on disk here. That would bee too costly since this method is
  typically used to update command sensitivities in the GUI, etc.
  This method will not be accurate if files are added or deleted manually.
*/

bool FapSimEventHandler::hasResults(bool checkMasterEventToo)
{
  // Checking the master event first
  FmMechanism* mech = FmDB::getMechanismObject(false);
  if (mech && checkMasterEventToo)
    if (mech->getResultStatusData()->hasFileNames("frs"))
      return true;

  // Checking each event, until one with results is found
  std::vector<FmSimulationEvent*> events;
  FmDB::getAllSimulationEvents(events);
  for (size_t i = 0; i < events.size(); i++)
    if (events[i]->getResultStatusData()->hasFileNames("frs"))
      return true;

  return false;
}


/*!
  Closes the results database and perform disk clean up.
  All results created after the last Save will be deleted.
*/

void FapSimEventHandler::RDBClose(bool pruneEmptyDirs)
{
  // Close the result extractor first.
  // To ensure no frs-files that are going to be deleted are open.
  FpModelRDBHandler::RDBRelease(true);

  // Next, close the events, but only those that have been solved or activated
  // during this session. The other events, if any, should not be touched here.
  std::vector<FmSimulationEvent*> events;
  FmDB::getAllSimulationEvents(events);
  for (size_t i = 0; i < events.size(); i++)
    if (events[i]->isTouched())
      FpModelRDBHandler::RDBClose(events[i]->getResultStatusData(true),
				  events[i]->getResultStatusData(false),
				  pruneEmptyDirs, false);

  // Finally, close the master event
  FmMechanism* mech = FmDB::getMechanismObject();
  FpModelRDBHandler::RDBClose(mech->getResultStatusData(true),
			      mech->getResultStatusData(false),
			      pruneEmptyDirs, false);
}


/*!
  Syncronizes the RSD with the contents on disk for all events.
  Only the latest results will pe preserved. The rest will be deleted.
*/

void FapSimEventHandler::RDBSave(bool pruneEmptyDirs)
{
  FmMechanism* mech = FmDB::getMechanismObject();

  std::vector<FmSimulationEvent*> events;
  FmDB::getAllSimulationEvents(events);
  for (size_t i = 0; i < events.size(); i++)
  {
    // Syncronize the RSD with contents on disk for running non-active event(s)
    if (events[i] != ourActiveEvent)
      if (FapSolutionProcessManager::instance()->isEventRunning(events[i]))
	FpModelRDBHandler::RDBSync(events[i]->getResultStatusData(),mech);

    FpModelRDBHandler::RDBSave(events[i]->getResultStatusData(true),
			       events[i]->getResultStatusData(false),
			       pruneEmptyDirs);
    events[i]->onChanged(); // for updating list view pixmap
  }

  FpModelRDBHandler::RDBSave(mech->getResultStatusData(true),
			     mech->getResultStatusData(false),
			     pruneEmptyDirs);
}


/*!
  Saves the results database for all events to a new locations.
  The RSD will be syncronized with the latest results found on disk.
*/

void FapSimEventHandler::RDBSaveAs(const std::string& RDBPath, bool discardResults)
{
  FmMechanism* mech = FmDB::getMechanismObject();

  std::vector<FmSimulationEvent*> events;
  FmDB::getAllSimulationEvents(events);
  for (size_t i = 0; i < events.size(); i++)
  {
    if (discardResults)
      FpModelRDBHandler::RDBIncrement(events[i]->getResultStatusData(),
				      mech,false);

    FpModelRDBHandler::RDBSaveAs(RDBPath,events[i]->getResultStatusData(true),
				 events[i]->getResultStatusData(false),mech,
				 FFaNumStr("event_%03d",events[i]->getID()));
    events[i]->onChanged(); // for updating list view pixmap
  }

  if (discardResults)
    FpModelRDBHandler::RDBIncrement(mech->getResultStatusData(),mech,false);

  FpModelRDBHandler::RDBSaveAs(RDBPath,mech->getResultStatusData(true),
			       mech->getResultStatusData(false),mech);
}


/*!
  Increments the task version number for all events (optionally for the
  master event too), and renews the result extractor. This is like deleting
  the results, but retaining them physically on disk until next Save or Close.
*/

void FapSimEventHandler::RDBIncrement(bool doMasterEventToo)
{
  FmMechanism* mech = FmDB::getMechanismObject();

  std::vector<FmSimulationEvent*> events;
  FmDB::getAllSimulationEvents(events);
  for (size_t i = 0; i < events.size(); i++)
  {
    FpModelRDBHandler::RDBIncrement(events[i]->getResultStatusData(),mech,false);
    events[i]->onChanged(); // for updating list view pixmap
  }

  if (doMasterEventToo)
    FpModelRDBHandler::RDBIncrement(mech->getResultStatusData(),mech,true);
  else if (ourActiveEvent) // master event is retained while another is active
    FpModelRDBHandler::RDBRelease(); // so only renew the result extractor here
}
