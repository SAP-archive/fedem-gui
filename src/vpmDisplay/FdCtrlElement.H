// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * CLASS: FdCtrlElement
 * AUTHOR: Magnus Svanberg
 * LAST MODIFIED: 25 feb. 1998
 *
 * DESCRIPTION
 * FdCtrlElement is derived from FdCtrlObject.
 * This class represents the elements in the scengraph.
 * All elements is of this type, the graphical difference between
 * elements lies in FdDetails().
 *
 * USAGE
 * Methods to manipulate the elements in the scengraph, ex. moving, rotate etc.
 ******************************************************************************/

#ifndef FD_CTRL_ELEMENT_H
#define FD_CTRL_ELEMENT_H

#include "vpmDisplay/FdCtrlObject.H"

class FmCtrlElementBase;


class FdCtrlElement : public FdCtrlObject
{
  Fmd_HEADER_INIT();

public:
  FdCtrlElement(FmCtrlElementBase*);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdCS();
  virtual bool updateFdDetails();

  void    moveObject(const SbVec3f& newTransVec, bool single);
  void    rotateObject();
  SbVec3f getElemTranslation() const;
  bool    isElementLeftRotated() const;

  enum Detail { NONE, INPUT, OUTPUT, BODY };

  void getElementDetail(const SbVec3f& globalPoint,
                        int& detailHit, int& portNumberHit);

private:
  void setElemText(const char* name, float textSize);

protected:
  virtual ~FdCtrlElement();

  virtual SoNodeKitListPart* getListSw() const;

private:
  void* myDescriptionId;
  void* myInfoStringId;
};

#endif
