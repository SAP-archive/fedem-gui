// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FA_DOF_H
#define FA_DOF_H

#include "FFaLib/FFaAlgebra/FFaVec3.H"
#include <iostream>


class FaDOF
{
public:
  enum { RIGID,
	 REV,
	 BALL,
	 PRISM,
	 CYL,
	 FREE };

  FaDOF(int t = FREE) { type = t; direction.z(1.0); }
  FaDOF(const FaVec3& c, const FaVec3& d, int t);

  FaDOF& copy(const FaDOF& dof, int t = -1);
  FaDOF  compound(const FaDOF& dof, double tolerance = 0.0);
  FaVec3 normalVector(const FaVec3& v) const;
  FaVec3 tangentVector(const FaVec3& p1, const FaVec3& p2) const;
  double rotationAngle(const FaVec3& p1, const FaVec3& p2) const;

  int getType() const { return type; }
  const FaVec3& getCenter() const    { return center; }
  const FaVec3& getDirection() const { return direction; }

  void setCenter(const FaVec3& c)    { center = c; }
  void setDirection(const FaVec3& d) { direction = d; }

  friend std::ostream& operator<<(std::ostream& os, const FaDOF& dof);

private:
  int    type;
  FaVec3 center;
  FaVec3 direction;
};

#endif
