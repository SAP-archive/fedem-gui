// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_CONVERTER_H
#define FD_CONVERTER_H

#include <Inventor/SbVec3f.h>
#include <Inventor/SbMatrix.h>
#include "FFaLib/FFaAlgebra/FFaVec3.H"
#include "FFaLib/FFaAlgebra/FFaMat34.H"

#include <array>


/*!
  \namespace FdConverter
  \brief Static methods to convert between FT vectors/matrices
  and Inventor vectors/matrices are put into this namespace.
*/

namespace FdConverter
{
  //! Converts std::array<float,3> to SbVec3f
  inline SbVec3f toSbVec3f(const std::array<float,3>& v) {
    return SbVec3f(v[0], v[1], v[2]);
  }

  //! Converts FaVec3 to SbVec3f
  inline SbVec3f toSbVec3f(const FaVec3& v) {
    return SbVec3f((float)v[0], (float)v[1], (float)v[2]);
  }

  //! Converts SbVec3f to FaVec3
  inline FaVec3 toFaVec3(const SbVec3f& v) {
    return FaVec3(v[0], v[1], v[2]);
  }

  //! Converts FaMat34 to SbMatrix
  inline SbMatrix toSbMatrix(const FaMat34& m) {
    return SbMatrix((float)m[0][0], (float)m[0][1], (float)m[0][2], 0.0f,
                    (float)m[1][0], (float)m[1][1], (float)m[1][2], 0.0f,
                    (float)m[2][0], (float)m[2][1], (float)m[2][2], 0.0f,
                    (float)m[3][0], (float)m[3][1], (float)m[3][2], 1.0f);
  }

  //! Converts SbMatrix to FaMat34
  inline FaMat34 toFaMat34(const SbMatrix& m) {
    return FaMat34(FaVec3(m[0][0], m[0][1], m[0][2]),
                   FaVec3(m[1][0], m[1][1], m[1][2]),
                   FaVec3(m[2][0], m[2][1], m[2][2]),
                   FaVec3(m[3][0], m[3][1], m[3][2]));
  }
}

#endif
