// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_OUTPUT_LIST_CMDS_H
#define FAP_OUTPUT_LIST_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class FuiOutputList;


class FapOutputListCmds : public FapCmdsBase
{
private:
  static void init();

  static void clear();
  static void copy();
  static void selectAll();

  static void getClearSensitivity(bool& sensitivity);
  static void getCopySensitivity(bool& sensitivity);
  static void getSelectAllSensitivity(bool& sensitivity);

  static FuiOutputList* list();

  friend class FFaInitialisation<FapOutputListCmds>;
};

static FFaInitialisation<FapOutputListCmds> FapOutputListCmds_Init;

#endif
