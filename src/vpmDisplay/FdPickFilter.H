// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_PICK_FILTER_H
#define FD_PICK_FILTER_H

#include <vector>

class FdObject;
class FdPart;
class FaVec3;
class SoPath;
class SoPickedPointList;
class SoCoordinate3;
class SoVertexProperty;
class SoVRMLCoordinate;
class SoMFVec3f;


class FdPickFilter
{
public:
  static FdObject* getInterestingPObj(const SoPickedPointList* ppl,
				      // This is to select objects behind the already selected one:
				      const std::vector<FdObject*>& selectedObjects,
				      // Filter variables:
				      const std::vector<int>& types,
				      bool typesIsInteresting,
				      // Variables returning values:
				      long& indexToInterestingPP,
				      bool& wasASelectedObjInPPList);

  static FdObject* getCyceledInterestingPObj(const SoPickedPointList* ppl,
					     // Filter variables:
					     const std::vector<int>& types,
					     bool typesIsInteresting,
					     // Variables returning values:
					     long& indexToInterestingPP);

  static FdObject* findFdObject(SoPath* path);

  static FdPart* findFirstPartHit(int& pplistIndex, const SoPickedPointList& ppl, FdObject* partToFind = NULL);
  static FdPart* findNodeHit(int& nodeID, FaVec3& nodePos, const SoPickedPointList& ppl, FdObject* partToFind);

  static SoCoordinate3*    findLastCoordNode (SoPath* path);
  static SoVertexProperty* findLastVxPropNode(SoPath* path);
  static SoVRMLCoordinate* findLastVRMLCoordNode(SoPath* path);
  static SoMFVec3f*        findLastVertexes(SoPath* path);
};

#endif
