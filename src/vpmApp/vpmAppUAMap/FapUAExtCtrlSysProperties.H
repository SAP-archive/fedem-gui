// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_EXT_CTRL_SYS_PROPERTIES_H
#define FAP_UA_EXT_CTRL_SYS_PROPERTIES_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/FapEventManager.H"

class FuiExtCtrlSysProperties;
class FuiQueryInputFieldValues;
class FmExternalCtrlSys;


class FapUAExtCtrlSysProperties : public FapUAExistenceHandler, public FapUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAExtCtrlSysProperties(FuiExtCtrlSysProperties* ui);
  virtual ~FapUAExtCtrlSysProperties() {}

private:
  void initVariables();

  // From signals
  void onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
			      const std::vector<FFaViewItem*>& selectedSinceLast,
			      const std::vector<FFaViewItem*>& unselectedSinceLast);

  // Reimpl from DataHandler
  virtual FFuaUIValues* createValuesObject();
  virtual void updateUIValues();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  // invoked when user pushes edit/new button
  void onEditOrCreateEngine(FuiQueryInputFieldValues& selectedRef);

private:
  FuiExtCtrlSysProperties* ui;
  FmExternalCtrlSys* dbexternal;

  // Private receivers
  FapPermSelChangedReceiver<FapUAExtCtrlSysProperties> selSignalConnector;
  friend class FapPermSelChangedReceiver<FapUAExtCtrlSysProperties>;
};

#endif
