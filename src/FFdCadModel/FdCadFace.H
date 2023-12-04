// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCADFACE_H
#define FDCADFACE_H

#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/fields/SoMFNode.h>

#include "FFdCadModel/FdCadEdge.H"
#include "FFaLib/FFaContainers/FFaByteArray.H"

class FdCadEntityInfo;

class FdCadFace : public SoIndexedFaceSet
{
  SO_NODE_HEADER(FdCadFace);

public:
  FdCadFace();
  static void initClass();

  void setGeometryInfo(FdCadEntityInfo* info);
  FdCadEntityInfo* getGeometryInfo();

  std::vector<FdCadEdge*> myEdges;
  FFaByteArray myCadId;

private :
  virtual ~FdCadFace();

  FdCadEntityInfo* myGeometryInfo;
};

#endif
