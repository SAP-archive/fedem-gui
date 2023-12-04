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
#include <Inventor/nodes/SoIndexedNurbsCurve.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoNurbsCurve.h>
#include <Inventor/nodes/SoCoordinate4.h>

#include "vpmDisplay/FdCurveKit.H"
#include "vpmDisplay/FdBackPointer.H"


SO_KIT_SOURCE(FdCurveKit); 


void FdCurveKit::init()
{
   SO_KIT_INIT_CLASS(FdCurveKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdCurveKit::FdCurveKit()
{
   SO_KIT_CONSTRUCTOR(FdCurveKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_ENTRY(sep,     SoSeparator,        FALSE, this, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(style,   SoDrawStyle,        TRUE,  sep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(material,SoMaterial,         TRUE,  sep, \x0 ,TRUE );   
   SO_KIT_ADD_CATALOG_ENTRY(coords,  SoCoordinate4,      TRUE,  sep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(curve,   SoNurbsCurve,TRUE,  sep, \x0 ,TRUE );
 
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdCurveKit::~FdCurveKit()
{
}
