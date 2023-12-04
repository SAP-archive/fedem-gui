// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDCTRLSYMBOLKIT_H
#define FDCTRLSYMBOLKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdCtrlSymbolKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdCtrlSymbolKit);  

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(style);
  SO_KIT_CATALOG_ENTRY_HEADER(scale);
  SO_KIT_CATALOG_ENTRY_HEADER(bodySep);
  SO_KIT_CATALOG_ENTRY_HEADER(coords);
  SO_KIT_CATALOG_ENTRY_HEADER(line);
  SO_KIT_CATALOG_ENTRY_HEADER(inPortSep);
  SO_KIT_CATALOG_ENTRY_HEADER(outPortSep);
  
  SO_KIT_CATALOG_ENTRY_HEADER(faceSep);
  SO_KIT_CATALOG_ENTRY_HEADER(faceMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(faceCoord);
  SO_KIT_CATALOG_ENTRY_HEADER(elemFaceSet);




public:

  // Constructor
  FdCtrlSymbolKit(); 

  SoINTERNAL public:
  static void init(); 

protected: 

  // Destructor
  virtual ~FdCtrlSymbolKit();

};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif

