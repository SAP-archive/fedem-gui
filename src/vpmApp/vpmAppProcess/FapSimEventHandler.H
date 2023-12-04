// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_SIM_EVENT_HANDLER_H
#define FAP_SIM_EVENT_HANDLER_H

#include <string>

class FmSimulationEvent;
class FmResultStatusData;


class FapSimEventHandler
{
public:
  static bool activate(FmSimulationEvent* selectedEvent,
		       bool closeRDB = true, bool reOpenRDB = true);

  static int getActiveEventID();
  static FmSimulationEvent* getActiveEvent() { return ourActiveEvent; }
  static FmResultStatusData* getActiveRSD(bool current = true);

  static bool hasResults(bool checkMasterEventToo = true);
  static void RDBClose(bool pruneEmptyDir);
  static void RDBSave(bool pruneEmptyDir);
  static void RDBSaveAs(const std::string& RDBPath, bool keepResults);
  static void RDBIncrement(bool doMasterEventToo = true);

private:
  static FmSimulationEvent* ourActiveEvent;
};

#endif
