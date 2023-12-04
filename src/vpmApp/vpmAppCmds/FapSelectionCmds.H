// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_SELECTION_CMDS_H
#define FAP_SELECTION_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaDynCalls/FFaSwitchBoard.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"
#include <vector>
#include <list>

class FFaViewItem;
class FmModelMemberBase;


class FapSelectionCmds : public FapCmdsBase
{
  static void init();
  static void getFwdSensitivity(bool& sensitivity);
  static void getBwdSensitivity(bool& sensitivity);
  static void getHlpSensitivity(bool& sensitivity);
  static void backward();
  static void forward();
  static void help();

private:
  static void setSelection();
  static void onModelMemberDisconnected(FmModelMemberBase* item);
  static void onPermSelectionChanged(std::vector<FFaViewItem*> selection,
				     std::vector<FFaViewItem*> added,
				     std::vector<FFaViewItem*> removed);

  class SignalConnector : public FFaSwitchBoardConnector
  {
  public:
    SignalConnector();
    virtual ~SignalConnector() {}
  };

  static SignalConnector signalConnector;

  typedef std::vector<FFaViewItem*> FFaViewItems;
  typedef std::list<FFaViewItems>   FFaViewItemList;

  static FFaViewItemList           ourSelectionHistory;
  static FFaViewItemList::iterator ourSelectionPt;

  static bool ourIAmSelecting;
  static bool ourSelectionIsEmpty;

  friend class FFaInitialisation<FapSelectionCmds>;
};

static FFaInitialisation<FapSelectionCmds> FapSelectionCmds_Init;

#endif
