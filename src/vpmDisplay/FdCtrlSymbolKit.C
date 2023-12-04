// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoPointSet.h>

#include <Inventor/nodes/SoFaceSet.h>

#include "vpmDisplay/FdCtrlSymbolKit.H"


SO_KIT_SOURCE(FdCtrlSymbolKit); 


void FdCtrlSymbolKit::init()
{
   SO_KIT_INIT_CLASS(FdCtrlSymbolKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdCtrlSymbolKit::FdCtrlSymbolKit()
{
   SO_KIT_CONSTRUCTOR(FdCtrlSymbolKit); 
   isBuiltIn = TRUE;
 
   SO_KIT_ADD_CATALOG_ENTRY(style,   SoDrawStyle ,    TRUE,
                            this,\x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(scale,   SoTransform,     TRUE,
                            this, \x0 ,TRUE );

   SO_KIT_ADD_CATALOG_ENTRY(bodySep, SoSeparator,TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(coords,  SoCoordinate3,   TRUE,
                            bodySep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(line,   SoIndexedLineSet,TRUE,
                            bodySep, \x0 ,TRUE );

   SO_KIT_ADD_CATALOG_ENTRY(inPortSep, SoSeparator,TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(outPortSep, SoSeparator,TRUE,
                            this, \x0 ,TRUE );
  
   //Texture 
   SO_KIT_ADD_CATALOG_ENTRY(faceSep, SoSeparator, TRUE,
			       this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(faceMaterial, SoMaterial, TRUE,
                            faceSep,\x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(faceCoord,SoCoordinate3 , TRUE,
                            faceSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(elemFaceSet, SoFaceSet, TRUE,
			    faceSep, \x0 ,TRUE );
   
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdCtrlSymbolKit::~FdCtrlSymbolKit()
{
}
