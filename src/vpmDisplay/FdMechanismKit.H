// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_MECHANISM_KIT_H
#define FD_MECHANISM_KIT_H

#include <Inventor/nodekits/SoBaseKit.h>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdMechanismKit : public SoBaseKit
{
  SO_KIT_HEADER(FdMechanismKit);

  // Defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(refPlaneListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(seaStateListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(triadListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(simpleJointListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(linJointListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(camJointListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(pipeSurfaceListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(freeJointListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(sprDaListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(loadListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(HPListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(sensorListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(stickerListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(tireListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(rosetteListSw);

  SO_KIT_CATALOG_ENTRY_HEADER(partListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(beamListSw);
  SO_KIT_CATALOG_ENTRY_HEADER(uelmListSw);

public:
  FdMechanismKit();

  SoINTERNAL public:
  static void init();

private:
  virtual ~FdMechanismKit();
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
