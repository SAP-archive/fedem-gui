// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoPointSet.h>

#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdBackPointer.H"


SO_KIT_SOURCE(FdSymbolKit); 


void FdSymbolKit::init()
{
   SO_KIT_INIT_CLASS(FdSymbolKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdSymbolKit::FdSymbolKit()
{
   SO_KIT_CONSTRUCTOR(FdSymbolKit); 
   isBuiltIn = TRUE;
 
   SO_KIT_ADD_CATALOG_ENTRY(style,   SoDrawStyle ,    TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(scale,   SoTransform,     TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(coords,  SoCoordinate3,   TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(axis1,   SoIndexedLineSet,TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(axis2,   SoIndexedLineSet,TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(axis3,   SoIndexedLineSet,TRUE,
                            this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(nonAxis, SoIndexedLineSet,TRUE,
                            this, \x0 ,TRUE );

 
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdSymbolKit::~FdSymbolKit()
{
}
