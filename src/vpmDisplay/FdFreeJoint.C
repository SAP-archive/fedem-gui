// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdFreeJoint.H"
#include "vpmDB/FmFreeJoint.H"


Fmd_SOURCE_INIT(FDFREEJOINT,FdFreeJoint,FdSimpleJoint);


FdFreeJoint::FdFreeJoint(FmFreeJoint* pt) : FdSimpleJoint(pt)
{
  Fmd_CONSTRUCTOR_INIT(FdFreeJoint);
}


FdFreeJoint::~FdFreeJoint()
{
}
