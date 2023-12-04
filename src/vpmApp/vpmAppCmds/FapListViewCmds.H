// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_LISTVIEW_CMDS_H
#define FAP_LISTVIEW_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class FapUAItemsListView;


class FapListViewCmds : public FapCmdsBase
{
private:
  static void init();

  static void sortListViewByID();
  static void sortListViewByName();
  static void ensureListViewSelectedVisible();

  static void getSortListViewSensitivity(bool& isSensitive);
  static FapUAItemsListView* getPoppedUpLV();

  friend class FFaInitialisation<FapListViewCmds>;
};

static FFaInitialisation<FapListViewCmds> FapListViewCmds_Init;

#endif
