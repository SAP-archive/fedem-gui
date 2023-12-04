// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDPIPESURFACEKIT_H
#define FDPIPESURFACEKIT_H
#include <Inventor/nodekits/SoBaseKit.h> 

class SoLightModel;

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdPipeArcKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdPipeArcKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER( rootSep       );
  SO_KIT_CATALOG_ENTRY_HEADER( levelOfDetail );
  SO_KIT_CATALOG_ENTRY_HEADER( fullSep       );
  SO_KIT_CATALOG_ENTRY_HEADER( fFaceLineSw   );
  SO_KIT_CATALOG_ENTRY_HEADER( fFaceSep      ); 
  SO_KIT_CATALOG_ENTRY_HEADER( fFaces        ); 
  SO_KIT_CATALOG_ENTRY_HEADER( fLineSep      );
  SO_KIT_CATALOG_ENTRY_HEADER( fLineMaterial );
  SO_KIT_CATALOG_ENTRY_HEADER( fLLightModel  ); 
  SO_KIT_CATALOG_ENTRY_HEADER( fLines        ); 
  SO_KIT_CATALOG_ENTRY_HEADER( simpleSep     );
  SO_KIT_CATALOG_ENTRY_HEADER( sFaceLineSw   );
  SO_KIT_CATALOG_ENTRY_HEADER( sFaceSep      ); 
  SO_KIT_CATALOG_ENTRY_HEADER( sFaces        ); 
  SO_KIT_CATALOG_ENTRY_HEADER( sLineSep      ); 
  SO_KIT_CATALOG_ENTRY_HEADER( sLineMaterial );
  SO_KIT_CATALOG_ENTRY_HEADER( sLLightModel  ); 
  SO_KIT_CATALOG_ENTRY_HEADER( sLines        );           
  SO_KIT_CATALOG_ENTRY_HEADER( cLineSep      );
  SO_KIT_CATALOG_ENTRY_HEADER( cLineMaterial );
  SO_KIT_CATALOG_ENTRY_HEADER( cLine         );     
public:

  // Constructor
  FdPipeArcKit(); 

  SoINTERNAL public:
  static void init(); 

private: 
  static SoLightModel * ourLineLightModel;

  // Destructor
  virtual ~FdPipeArcKit();

};


class FdPipeSurfaceKit : public SoBaseKit 
{ 
  SO_KIT_HEADER(FdPipeSurfaceKit); 

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(pipeList);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:

  // Constructor
  FdPipeSurfaceKit(); 

  SoINTERNAL public:
  static void init(); 

private: 

  // Destructor
  virtual ~FdPipeSurfaceKit();

};


#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
