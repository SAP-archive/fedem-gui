// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_AIRFOIL_DEFINITION_H
#define FUI_AIRFOIL_DEFINITION_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"


class FuiAirfoilDefinition : virtual public FFuTopLevelShell
{
  Fmd_HEADER_INIT();

public:
  FuiAirfoilDefinition();
  virtual ~FuiAirfoilDefinition() {}

  static FuiAirfoilDefinition* create(int xpos = 100, int ypos = 100,
				      int width = 100, int height = 100,
				      const char* title= "Airfoil Browser",
				      const char* name = "FuiAirfoilDefinition");
};

#endif
