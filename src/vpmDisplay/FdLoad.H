// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDLOAD_H
#define FDLOAD_H

#include "vpmDisplay/FdBase.H"

class FmLoad;


class FdLoad : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdLoad(FmLoad* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

protected:
  virtual ~FdLoad();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
