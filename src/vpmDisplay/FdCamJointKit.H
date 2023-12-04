// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCAMJOINTKIT_H
#define FDCAMJOINTKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class SoComplexity;

class FdCamJointKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCamJointKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(masterList);

  SO_KIT_CATALOG_ENTRY_HEADER(curves);
  SO_KIT_CATALOG_ENTRY_HEADER(detailLevel);
  SO_KIT_CATALOG_ENTRY_HEADER(camTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(curveList);

  SO_KIT_CATALOG_ENTRY_HEADER(slave);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:

  // Constructor
  FdCamJointKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~FdCamJointKit();

  static SoComplexity * ourCurveCompexity;
};


#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
