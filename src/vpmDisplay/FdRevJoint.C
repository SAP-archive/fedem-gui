// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdRevJoint.H"
#include "vpmDB/FmRevJoint.H"

/**********************************************************************
 *
 * CLASS FdRevJoint
 *
 **********************************************************************/

 Fmd_SOURCE_INIT(FDREVJOINT,FdRevJoint,FdSimpleJoint);

FdRevJoint::FdRevJoint(FmRevJoint * pt) : FdSimpleJoint(pt)
{
  Fmd_CONSTRUCTOR_INIT(FdRevJoint);
}

FdRevJoint::~FdRevJoint()
{

}
