// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPWORKSPACECMDS_H
#define FAPWORKSPACECMDS_H
#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class FapWorkSpaceCmds: public FapCmdsBase
{
// Operations
private:
  static void init();

  static void cascade();
  static void tile();
  static void tabs();
  static void subWins();
  
// Attributes
private:
 friend class FFaInitialisation<FapWorkSpaceCmds>;
};

static FFaInitialisation<FapWorkSpaceCmds> FapWorkSpaceCmds_Init;
/////////////////////////////////////////////////////////////////////////////

#endif




