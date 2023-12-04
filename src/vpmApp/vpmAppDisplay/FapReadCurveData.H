// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_READ_CURVE_DATA_H
#define FAP_READ_CURVE_DATA_H

#include <vector>

class FmCurveSet;


namespace Fap
{
  //! \brief Global function reading a set of curves into an array.
  size_t readCurveData(const std::vector< FmCurveSet* >& curves,
                       std::vector< std::vector<double> >& values,
                       double startT, double stopT);
}

#endif
