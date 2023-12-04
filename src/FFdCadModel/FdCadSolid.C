// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFdCadModel/FdCadSolid.H"


SO_NODE_SOURCE(FdCadSolid);

void FdCadSolid::initClass()
{
  SO_NODE_INIT_CLASS(FdCadSolid, SoSeparator, "Separator");
}

FdCadSolid::FdCadSolid()
{
  SO_NODE_CONSTRUCTOR(FdCadSolid);
  SO_NODE_ADD_FIELD(mySolidWire, (NULL));
}
