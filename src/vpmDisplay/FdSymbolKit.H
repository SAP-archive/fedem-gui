// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSYMBOLKIT_H
#define FDSYMBOLKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdSymbolKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdSymbolKit);  

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(style);
  SO_KIT_CATALOG_ENTRY_HEADER(scale);
  SO_KIT_CATALOG_ENTRY_HEADER(coords);
  SO_KIT_CATALOG_ENTRY_HEADER(axis1);
  SO_KIT_CATALOG_ENTRY_HEADER(axis2);
  SO_KIT_CATALOG_ENTRY_HEADER(axis3);
  SO_KIT_CATALOG_ENTRY_HEADER(nonAxis);

public:

  // Constructor
  FdSymbolKit(); 

  SoINTERNAL public:
  static void init(); 

protected: 

  // Destructor
  virtual ~FdSymbolKit();

};


#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif



