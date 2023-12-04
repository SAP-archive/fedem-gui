// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCTRLKIT_H
#define FDCTRLKIT_H

#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdCtrlKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCtrlKit); 
 
  SO_KIT_CATALOG_ENTRY_HEADER(elemList);
 
  SO_KIT_CATALOG_ENTRY_HEADER(lineList);
 
public:

  // Constructor
  FdCtrlKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~FdCtrlKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
