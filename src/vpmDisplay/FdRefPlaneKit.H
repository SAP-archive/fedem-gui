// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDREFPLANEKIT_H
#define FDREFPLANEKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdRefPlaneKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdRefPlaneKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(planeTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(planeSep);
  SO_KIT_CATALOG_ENTRY_HEADER(planeSize);
  SO_KIT_CATALOG_ENTRY_HEADER(planeCoords);
  SO_KIT_CATALOG_ENTRY_HEADER(planeMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(planeShape);
  SO_KIT_CATALOG_ENTRY_HEADER(frameStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(lineMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(frameShape);
  SO_KIT_CATALOG_ENTRY_HEADER(csStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(csTranslation);
  SO_KIT_CATALOG_ENTRY_HEADER(csAppearance);
  SO_KIT_CATALOG_ENTRY_HEADER(csLightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(csSymbol);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:

  FdRefPlaneKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  virtual ~FdRefPlaneKit();

};


#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif



