// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFdCadModel/FdCadFace.H"
#include "FFdCadModel/FdCadInfo.H"

SO_NODE_SOURCE(FdCadFace);

void FdCadFace::initClass()
{
  SO_NODE_INIT_CLASS(FdCadFace, SoIndexedFaceSet, "IndexedFaceSet");
}

FdCadFace::FdCadFace()
{
  SO_NODE_CONSTRUCTOR(FdCadFace);
  myGeometryInfo = 0;
}

FdCadFace::~FdCadFace()
{
  delete myGeometryInfo;
}

void FdCadFace::setGeometryInfo(FdCadEntityInfo* info)
{
  delete myGeometryInfo;
  myGeometryInfo = info;
}

FdCadEntityInfo* FdCadFace::getGeometryInfo()
{
  return myGeometryInfo;
}
