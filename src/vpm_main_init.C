// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/FapInit.H"
#include "FFrLib/FFrReadOpInit.H"
#include "FFaLib/FFaOperation/FFaBasicOperations.H"


struct OperationInit
{
  static void init()
  {
    FFr::initReadOps();
    FFa::initBasicOps();
  }
};

static FFaInitialisation<OperationInit> oper_init;
