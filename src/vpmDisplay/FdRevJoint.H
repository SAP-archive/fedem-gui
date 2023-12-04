// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDREVJOINT_H
#define FDREVJOINT_H

#include "vpmDisplay/FdSimpleJoint.H"

class FmRevJoint;


class FdRevJoint : public FdSimpleJoint
{
  Fmd_HEADER_INIT();

public:
  FdRevJoint(FmRevJoint*);

protected:
  virtual ~FdRevJoint();
};

#endif
