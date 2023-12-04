// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_APPEARANCE_H
#define FAP_UA_APPEARANCE_H

#include <vector>
#include <string>

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "vpmApp/FapEventManager.H"

class FuiAppearance;
class FFaViewItem;
class FmIsRenderedBase;


class FapUAAppearance : public FapUAExistenceHandler, public FapUADataHandler, public FapUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAAppearance(FuiAppearance* ui);
  virtual ~FapUAAppearance() {}

private:
  // slots from EventManager
  void onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
			      const std::vector<FFaViewItem*>& selectedSinceLast,
			      const std::vector<FFaViewItem*>& unselectedSinceLast);

protected:
  virtual void finishUI();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

private:
  virtual FFuaUIValues* createValuesObject();

protected:
  FuiAppearance* myAppearanceUI;
  FmIsRenderedBase* myCurrentObj;
  std::vector<std::string> myRefPlaneLODText;
  std::vector<std::string> myLinkLODText;
  std::vector<std::string> myLinesLODText;
  std::vector<std::string> myGenPPolyLODText;
  std::vector<std::string> myGenPLinesLODText;
  std::vector<std::string> myCadGenPLinesLODText;

private:
  FapPermSelChangedReceiver<FapUAAppearance> signalConnector;
  friend class FapPermSelChangedReceiver<FapUAAppearance>;
};

#endif
