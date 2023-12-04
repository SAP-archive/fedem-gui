// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiTurbWind.H"
#include "vpmPM/FpPM.H"


Fmd_SOURCE_INIT(FUI_TURBWIND,FuiTurbWind,FFuTopLevelShell);


FuiTurbWind::FuiTurbWind()
{
  Fmd_CONSTRUCTOR_INIT(FuiTurbWind);

  turbsim_exe = FpPM::getFullFedemPath("TurbSim");
  templateDir = FpPM::getFullFedemPath("Templates");
}
