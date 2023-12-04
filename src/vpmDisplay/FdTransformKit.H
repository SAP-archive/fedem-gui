// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDTRANSFORMKIT_H
#define FDTRANSFORMKIT_H

#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdTransformKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdTransformKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(transSep);
  SO_KIT_CATALOG_ENTRY_HEADER(firstTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(secondTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(appearance);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);
  SO_KIT_CATALOG_ENTRY_HEADER(symbol);

public:

  // Constructor
  FdTransformKit(); 

  SoINTERNAL public:
  static void init(); 

protected: 

  // Destructor
  virtual ~FdTransformKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
