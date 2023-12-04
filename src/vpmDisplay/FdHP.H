// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDHP_H
#define FDHP_H

#include "vpmDisplay/FdBase.H"

class FmHPBase;


class FdHP : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdHP(FmHPBase* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

protected:
  virtual ~FdHP();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
