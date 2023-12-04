// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDPRISMJOINT_H
#define FDPRISMJOINT_H

#include "vpmDisplay/FdLinJoint.H"

class FmPrismJoint;


class FdPrismJoint : public FdLinJoint
{
  Fmd_HEADER_INIT();

public:
  FdPrismJoint(FmPrismJoint*);

protected:
  virtual ~FdPrismJoint();
};

#endif
