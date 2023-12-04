// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_TIRE_H
#define FD_TIRE_H

#include "vpmDisplay/FdBase.H"
#include <array>

typedef std::array<float,3> FdColor;

class FmTire;
class FdFEModel;


class FdTire : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdTire(FmTire*);

  virtual bool updateFdAll(bool updateChildrenDisplay = true);
  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

  void setColor(const FdColor& color);

protected:
  virtual ~FdTire();

  virtual SoNodeKitListPart* getListSw() const;

  virtual void showHighlight();
  virtual void hideHighlight();

  void*      highlightBoxId;
  FdFEModel* myFEKit;
  FdColor    myColor;
};

#endif
