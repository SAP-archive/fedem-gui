// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_CREATE_SENSOR_CMD_H
#define FAP_CREATE_SENSOR_CMD_H

#include "vpmApp/FapEventManager.H"
#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include "FapCmdsBase.H"

class FmIsMeasuredBase;
class FmEngine;
class FmTriad;
class FFaViewItem;
class SoEventCallback;

class FapCreateSensorCmd : public FapCmdsBase,
			   public FFaSingelton<FapCreateSensorCmd>
{
public:
  FapCreateSensorCmd() : permSignalConnector(this) { myEngine = 0; myArg = 0; }

  void createSensor(unsigned int iArg = 0);

  static void enterMode();
  static void cancelMode();
  static void done();

private:
  void onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
			      const std::vector<FFaViewItem*>& selectedSinceLast,
			      const std::vector<FFaViewItem*>& unselectedSinceLast);

  static void createSensor(FmIsMeasuredBase* obj);
  static void createSensor(FmTriad* t1, FmTriad* t2);

  static void setState(int newState);
  static void eventCB(void*, SoEventCallback* eventCallbackNode);

  FmEngine* myEngine;
  unsigned int myArg;
  static int myState;

  FapPermSelChangedReceiver<FapCreateSensorCmd> permSignalConnector;
  friend class FapPermSelChangedReceiver<FapCreateSensorCmd>;
};

#endif
