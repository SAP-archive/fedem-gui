// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_SELECTOR_H
#define FD_SELECTOR_H

#include "vpmDisplay/FaDOF.H"
#include <vector>

class FdObject;
class FdLink;
class FaVec3;


class FdSelector
{
public:
  static void getSelectedObjects(std::vector<FdObject*>& toBeFilled);

  static void smartMoveSelection(const FaVec3& firstPoint,
				 const FaVec3& secondPoint,
				 const FaDOF& dof);

  static FaDOF getDegOfFreedom();

  static void selectExpanded(FdObject* object);
  static void deselectExpandedLast();

private:
  static void expandSelectLink(FdLink* link);
  static void expandDeselectLink(FdLink* link);
};

#endif
