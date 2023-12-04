// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_ANIMATION_CONTROL_H
#define FAP_UA_ANIMATION_CONTROL_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "vpmApp/FapEventManager.H"

class FuiAnimationControl;


class FapUAAnimationControl : public FapUAExistenceHandler, public FapUADataHandler, public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAAnimationControl(FuiAnimationControl* ui);
  virtual ~FapUAAnimationControl() {}

private:
  // from datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  // from finishhandler
  virtual void finishUI();

  // slots from EventManager
  void onActiveAnimationChanged(FmAnimation* newActive, FmAnimation* prevActive);

private:
  FuiAnimationControl* ui;

  FapActiveAnimationChangedReceiver<FapUAAnimationControl> signalConnector;
  friend class FapActiveAnimationChangedReceiver<FapUAAnimationControl>;
};

#endif
