// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSTRAINROSETTEKIT_H
#define FDSTRAINROSETTEKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdStrainRosetteKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdStrainRosetteKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(transSep);   
  SO_KIT_CATALOG_ENTRY_HEADER(firstTrans); 
  SO_KIT_CATALOG_ENTRY_HEADER(appearance); 
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);     
  SO_KIT_CATALOG_ENTRY_HEADER(elmCoords);  
  SO_KIT_CATALOG_ENTRY_HEADER(elmShape);   
  SO_KIT_CATALOG_ENTRY_HEADER(secondTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(smallSep);
  SO_KIT_CATALOG_ENTRY_HEADER(scale);      
  SO_KIT_CATALOG_ENTRY_HEADER(smallSymbol);
  SO_KIT_CATALOG_ENTRY_HEADER(largeSymbol);

public:

  FdStrainRosetteKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  virtual ~FdStrainRosetteKit();

};


#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif



