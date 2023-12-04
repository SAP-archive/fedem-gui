// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDAXIALSPRDA_H
#define FDAXIALSPRDA_H

#include "vpmDisplay/FdBase.H"

class FmIsControlledBase;
class FmTriad;


class FdAxialSprDa : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdAxialSprDa(FmIsControlledBase* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

  FmTriad* findClosestTriad(const SbVec3f& pointOnObject);

protected:
  virtual ~FdAxialSprDa();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
