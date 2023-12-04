// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef _FAPSOLVERID_H_
#define _FAPSOLVERID_H_

namespace FapSolverID
{
  // Numbers used to identify the running sub-processes
  enum {
    FAP_DYN_SOLVER  =  1,
    FAP_STRESS      =  2,
    FAP_REDUCER     =  3,
    FAP_MODES       =  4,
    FAP_FPP         =  5,
    FAP_GAGE        =  6,
    FAP_FEFATIGUE   =  7,
    FAP_DC_FPPHCOPY = 30,
    FAP_DC_FATFE    = 31,
    FAP_DC_FEFCOM   = 32,
    FAP_DC_FEF2FRS  = 33
  };
};

#endif
