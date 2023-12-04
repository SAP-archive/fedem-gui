// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCTRLGRIDKIT_H
#define FDCTRLGRIDKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 



#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdCtrlGridKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCtrlGridKit);  

  // Defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(gridSep);
  SO_KIT_CATALOG_ENTRY_HEADER(appearance);
  SO_KIT_CATALOG_ENTRY_HEADER(style);
  SO_KIT_CATALOG_ENTRY_HEADER(coords);
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(lines);
 

public:

  // Constructor
  FdCtrlGridKit(); 

  SoINTERNAL public:
  static void init(); 

protected: 

  // Destructor
  virtual ~FdCtrlGridKit();

};


#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif



