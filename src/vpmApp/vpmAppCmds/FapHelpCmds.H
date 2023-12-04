// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_HELP_CMDS_H
#define FAP_HELP_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapHelpCmds : public FapCmdsBase
{
  static void init();
  static void about();

  friend class FFaInitialisation<FapHelpCmds>;
};

static FFaInitialisation<FapHelpCmds> FapHelpCmds_Init;

#endif
