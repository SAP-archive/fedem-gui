// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSIMPLEJOINTKIT_H
#define FDSIMPLEJOINTKIT_H

#include <Inventor/nodekits/SoBaseKit.h> 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdSimpleJointKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdSimpleJointKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(joint);
  SO_KIT_CATALOG_ENTRY_HEADER(master);
  SO_KIT_CATALOG_ENTRY_HEADER(slave);
  SO_KIT_CATALOG_ENTRY_HEADER(lineM);
  SO_KIT_CATALOG_ENTRY_HEADER(lineS);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:
  FdSimpleJointKit();

  SoINTERNAL public:
  static void init();

private: 
  virtual ~FdSimpleJointKit();
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
