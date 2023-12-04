// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCADSOLIDWIRE_H
#define FDCADSOLIDWIRE_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFNode.h>


class FdCadSolidWire : public SoSeparator
{
  SO_NODE_HEADER(FdCadSolidWire);

public:
  FdCadSolidWire();
  static void initClass();

  SoSFNode mySolid;

private:
  virtual ~FdCadSolidWire() {}
};

#endif
