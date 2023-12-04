// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFdCadModel/FdCadSolidWire.H"


SO_NODE_SOURCE(FdCadSolidWire);

void FdCadSolidWire::initClass()
{
  SO_NODE_INIT_CLASS(FdCadSolidWire, SoSeparator, "Separator");
}

FdCadSolidWire::FdCadSolidWire()
{
  SO_NODE_CONSTRUCTOR(FdCadSolidWire);
  SO_NODE_ADD_FIELD(mySolid, (0));
}


