// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDFREEJOINT_H
#define FDFREEJOINT_H

#include "vpmDisplay/FdSimpleJoint.H"

class FmFreeJoint;


class FdFreeJoint : public FdSimpleJoint
{
  Fmd_HEADER_INIT();

public:
  FdFreeJoint(FmFreeJoint* pt);

protected:
  virtual ~FdFreeJoint();
};

#endif
