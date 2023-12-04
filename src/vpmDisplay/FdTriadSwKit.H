// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDTRIADSWKIT_H
#define FDTRIADSWKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdTriadSwKit : public SoBaseKit 
{ 
  SO_KIT_HEADER( FdTriadSwKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(triadSw); 
 

public:

  // Constructor
   FdTriadSwKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~ FdTriadSwKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif



