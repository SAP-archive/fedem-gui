// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSTICKER_H
#define FDSTICKER_H

#include "vpmDisplay/FdBase.H"

class FmSticker;


class FdSticker : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdSticker(FmSticker* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();
  virtual bool updateFdCS();

  virtual SbVec3f findSnapPoint(const SbVec3f& pointOnObject,
				const SbMatrix& objToWorld,
				SoDetail* pickDetail = 0,
				SoPickedPoint* pPoint = 0);

protected:
  virtual ~FdSticker();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
