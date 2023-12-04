// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_TURB_WIND_H
#define FUI_TURB_WIND_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"


class FuiTurbWind : public virtual FFuTopLevelShell
{
  Fmd_HEADER_INIT();

public:
  FuiTurbWind();
  virtual ~FuiTurbWind() {}

  static FuiTurbWind* create(int xpos = 100, int ypos = 100,
                             int width = 100, int height = 100,
                             const char* title= "Turbulent Wind Definition",
                             const char* name = "FuiTurbWind");

  virtual void setValues(double hubHeight, double gridSize,
                         double timeInc, double duration,
                         const char* outputPath) = 0;

protected:
  std::string turbsim_exe;
  std::string templateDir;
};

#endif
