// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCTRLLINEKIT_H
#define FDCTRLLINEKIT_H

#include <Inventor/nodekits/SoBaseKit.h> 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdCtrlLineKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCtrlLineKit); 

  // Defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(lineSep);
  SO_KIT_CATALOG_ENTRY_HEADER(appearance);
  SO_KIT_CATALOG_ENTRY_HEADER(symbol);
  SO_KIT_CATALOG_ENTRY_HEADER(points);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:

  // Constructor
  FdCtrlLineKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~FdCtrlLineKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif
