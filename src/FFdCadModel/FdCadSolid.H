// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCADSOLID_H
#define FDCADSOLID_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFNode.h>
#include "FFaLib/FFaAlgebra/FFaTensor3.H"
#include "FFaLib/FFaAlgebra/FFaVec3.H"


class FdCadSolid : public SoSeparator
{
  SO_NODE_HEADER(FdCadSolid);

public:
  FdCadSolid();
  static void initClass();

  double getDensity() const { return myDensity; }
  void   setDensity(double dens) { myDensity = dens; }

  double getMass() const { return myDensity*myVolume; }
  void setVolume(double volume) { myVolume = volume; }

  void getCenterOfVolume(FaVec3& cv)       { cv = myCoV; }
  void setCenterOfVolume(const FaVec3& cg) { myCoV = cg; }

  void getInertia(FFaTensor3& I) { I = myDensity*myVI; }
  void setVInertia(const FFaTensor3& vI) { myVI = vI; }

  SoSFNode mySolidWire;

private:
  virtual ~FdCadSolid() {};

  double myVolume;
  FaVec3 myCoV;
  FFaTensor3 myVI; //<! Ixx, Iyy, Izz, Ixy, Ixz, Iyz
  double myDensity;
};


#endif
