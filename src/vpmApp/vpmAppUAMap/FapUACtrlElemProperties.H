// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_CTRL_ELEM_PROPERTIES_H
#define FAP_UA_CTRL_ELEM_PROPERTIES_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/FapEventManager.H"

class FmModelMemberBase;
class FuiCtrlElemProperties;


class FapUACtrlElemProperties : public FapUAExistenceHandler,
				public FapUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FapUACtrlElemProperties(FuiCtrlElemProperties* ui);
  virtual ~FapUACtrlElemProperties() {}

protected:
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

private:
  void onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
			      const std::vector<FFaViewItem*>& selectedSinceLast,
			      const std::vector<FFaViewItem*>& unselectedSinceLast);

  virtual FFuaUIValues* createValuesObject();

  FuiCtrlElemProperties* myUI;
  FmModelMemberBase*     mySelectedFmItem;

  FapPermSelChangedReceiver<FapUACtrlElemProperties> signalConnector;
  friend class FapPermSelChangedReceiver<FapUACtrlElemProperties>;
};

#endif
