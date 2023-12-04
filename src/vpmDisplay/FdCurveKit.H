// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCURVEKIT_H
#define FDCURVEKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdCurveKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCurveKit);  

  // Defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(sep);
  SO_KIT_CATALOG_ENTRY_HEADER(style);
  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(coords);
  SO_KIT_CATALOG_ENTRY_HEADER(curve);

public:

  // Constructor
  FdCurveKit(); 

  SoINTERNAL public:
  static void init(); 

protected: 

  // Destructor
  virtual ~FdCurveKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif



