// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdPrismJoint.H"
#include "vpmDB/FmPrismJoint.H"

 
/**********************************************************************
 *
 * CLASS FdPrismJoint
 *
 **********************************************************************/

Fmd_SOURCE_INIT(FDPRISMJOINT,FdPrismJoint,FdLinJoint);

FdPrismJoint::FdPrismJoint(FmPrismJoint * pt) : FdLinJoint(pt)
{
  Fmd_CONSTRUCTOR_INIT(FdPrismJoint);
}

FdPrismJoint::~FdPrismJoint()
{

}
