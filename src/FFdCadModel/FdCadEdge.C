// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFdCadModel/FdCadEdge.H"
#include "FFdCadModel/FdCadInfo.H"

SO_NODE_SOURCE(FdCadEdge);

void FdCadEdge::initClass()
{
  SO_NODE_INIT_CLASS(FdCadEdge, SoIndexedLineSet, "IndexedLineSet");
}

FdCadEdge::FdCadEdge()
{
  SO_NODE_CONSTRUCTOR(FdCadEdge);
  SO_NODE_ADD_FIELD(faces, (0));
  myGeometryInfo = 0;
}


FdCadEdge::~FdCadEdge()
{
  delete myGeometryInfo;
}

void FdCadEdge::setGeometryInfo(FdCadEntityInfo* info)
{
  delete myGeometryInfo;
  myGeometryInfo = info;
}

FdCadEntityInfo* FdCadEdge::getGeometryInfo()
{
  return myGeometryInfo;
}
