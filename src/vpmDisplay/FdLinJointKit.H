// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDLINJOINTKIT_H
#define FDLINJOINTKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdLinJointKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdLinJointKit); 

  // Defines fields for the new parts in the catalog


 
  SO_KIT_CATALOG_ENTRY_HEADER(masterList);
  SO_KIT_CATALOG_ENTRY_HEADER(lineSymbol);
  SO_KIT_CATALOG_ENTRY_HEADER(slave);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:

  // Constructor
  FdLinJointKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~FdLinJointKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
