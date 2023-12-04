// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FP_RDB_EXTRACTOR_MANAGER_H
#define FP_RDB_EXTRACTOR_MANAGER_H

#include <string>
#include <vector>
#include <set>

#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include "FFaLib/FFaDynCalls/FFaSwitchBoard.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FpExtractor;
class FFrExtractor;
class FFaListViewItem;
class FmModelMemberBase;


struct FpRDBListViewFilter
{
  const char* name;
  bool freezeTopLevelItem;
  bool showModelPermSelectionAsTopLevelItem;
  FFaDynCB2<FFaListViewItem*,bool&> verifyItemCB;
  FpRDBListViewFilter(const char* s) : name(s) {
    freezeTopLevelItem = showModelPermSelectionAsTopLevelItem = false;
  }
};

////////////////////////////////////////////////////////////////////////////////

class FpRDBExtractorManager : public FFaSingelton<FpRDBExtractorManager>,
                              public FFaSwitchBoardConnector
{
public:
  FpRDBExtractorManager();
  virtual ~FpRDBExtractorManager();

  enum { // Signals, not emmited for posExtr
    NEW_MODELEXTRACTOR,
    MODELEXTRACTOR_DELETED,
    MODELEXTRACTOR_ABOUT_TO_DELETE,
    MODELEXTRACTOR_HEADER_CHANGED,
    MODELEXTRACTOR_DATA_CHANGED,
    POSEXTRACTOR_DELETED,
    POSEXTRACTOR_ABOUT_TO_DELETE,
    POSEXTRACTOR_HEADER_CHANGED
  };

  void createModelExtractor();
  void renewExtractors(const std::set<std::string>& keep = std::set<std::string>());
  void clearExtractors();

  FFrExtractor* getModelExtractor();
  FFrExtractor* getPossibilityExtractor();

  std::vector<std::string> getPredefPosFiles();

  const FpRDBListViewFilter* getRDBListViewFilter() const { return &lvFilter; }

  bool hasResults(FmModelMemberBase* obj) const;

private:
  // Callbacks
  void onModelExtractorHeaderChanged(const FFrExtractor* extr);
  void onModelExtractorDataChanged(const FFrExtractor* extr);
  void onPosExtractorHeaderChanged(const FFrExtractor* extr);

  void verifySolverItem(FFaListViewItem* item, bool& valid);

private:
  FpExtractor* modelExtr;
  FpExtractor* posExtr;

  FpRDBListViewFilter lvFilter;
};


//////////////////////////////////////////////////////////////////////

template <class T>
class FpRDBHeaderChangedReceiver : public FFaSwitchBoardConnector
{
public:
  FpRDBHeaderChangedReceiver(T* owner) : myOwner(owner)
  {
    FFaSwitchBoard::connect(FpRDBExtractorManager::instance(),
			    FpRDBExtractorManager::MODELEXTRACTOR_HEADER_CHANGED,
			    FFaSlot1M(FpRDBHeaderChangedReceiver<T>,this,onRDBHeaderChanged,FFrExtractor*));
    FFaSwitchBoard::connect(FpRDBExtractorManager::instance(),
			    FpRDBExtractorManager::MODELEXTRACTOR_DELETED,
			    FFaSlot0M(FpRDBHeaderChangedReceiver<T>,this,onRDBHeaderChangedVoid));
  }
  virtual ~FpRDBHeaderChangedReceiver() {}

private:
  void onRDBHeaderChangedVoid() { myOwner->onRDBHeaderChanged(NULL); }
  void onRDBHeaderChanged(FFrExtractor* ex) { myOwner->onRDBHeaderChanged(ex); }

  T* myOwner;
};

#endif
