// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
 * CLASS: FdCtrlLine
 * AUTHOR: Magnus Svanberg
 **********************************************************************/

#ifndef FD_CTRL_LINE_H
#define FD_CTRL_LINE_H

#include "vpmDisplay/FdCtrlObject.H"

#include <Inventor/SbVec3f.h>

#include <vector>

class FmCtrlLine;


class FdCtrlLine : public FdCtrlObject
{
  Fmd_HEADER_INIT();

public:
  FdCtrlLine(FmCtrlLine* pt);

  virtual bool updateFdAll(bool updateChildrenDisplay = true);
  virtual bool updateFdTopology(bool = true) { return true; }
  virtual bool updateFdDetails();

  void drawLine();
  bool manipLine(int detail, const SbVec3f& transVec);
  void addLinePoint1(const SoPickedPoint* pickedPoint);
  void addLinePoint2(const SbVec3f& transVec);
  void removeLinePoint(int pointNr);
  SbVec3f getCoordinate(int coordIndex);
  int pickedLineDetail(const SbVec3f& pointCoord, long partIndex);
  int getNumberOfSegments() const;

protected:
  virtual ~FdCtrlLine();

  virtual SoNodeKitListPart* getListSw() const;

private:
  int calcLineNr;
  int direction;
  int unDefLine;
  SbVec3f coordVec;
  bool pickedLineVertical;
  std::vector<double> lengthArray;
};

#endif
