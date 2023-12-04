// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDREFPLANE_H
#define FDREFPLANE_H

#include "vpmDisplay/FdBase.H"

class FmRefPlane;


class FdRefPlane : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdRefPlane(FmRefPlane* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();
  virtual bool updateFdCS();

protected:
  virtual ~FdRefPlane();

  virtual SoNodeKitListPart* getListSw() const;

  virtual void showHighlight();
  virtual void hideHighlight();

  void* highlightBoxId;
};

#endif
