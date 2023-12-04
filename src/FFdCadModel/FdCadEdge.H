// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCADEDGE_H
#define FDCADEDGE_H

#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/fields/SoMFNode.h>

#include "FFaLib/FFaContainers/FFaByteArray.H"
class FdCadEntityInfo;

class FdCadEdge : public SoIndexedLineSet
{
  SO_NODE_HEADER(FdCadFace);

public:
  FdCadEdge();
  static void initClass();

  void setGeometryInfo(FdCadEntityInfo* info);
  FdCadEntityInfo * getGeometryInfo();

  SoMFNode faces;
  FFaByteArray myCadId;
private :
  virtual ~FdCadEdge();

  FdCadEntityInfo * myGeometryInfo;
};

#endif
