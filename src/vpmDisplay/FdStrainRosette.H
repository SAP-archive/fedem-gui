// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSTRAINROSETTE_H
#define FDSTRAINROSETTE_H

#include "vpmDisplay/FdBase.H"

class FmStrainRosette;


class FdStrainRosette : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdStrainRosette(FmStrainRosette*);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();
  virtual bool updateFdCS();

protected:
  virtual ~FdStrainRosette();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
