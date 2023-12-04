// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_FUNCTION_DOMAIN_H
#define FUI_FUNCTION_DOMAIN_H

#include <utility>


struct FuaFunctionDomain
{
  std::pair<double,double> X;
  double dX;
  char autoInc;

  FuaFunctionDomain(double x0 = 0.0, double x1 = 5.0,
                    double dx = 0.01, char a = -1)
    : X({x0,x1}), dX(dx), autoInc(a) {}
};

#endif
