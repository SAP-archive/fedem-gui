// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>

#include "vpmDisplay/FdStrainRosetteKit.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdAppearanceKit.H"
#include "vpmDisplay/FdSymbolKit.H"

SO_KIT_SOURCE(FdStrainRosetteKit); 

void FdStrainRosetteKit::init()
{
   SO_KIT_INIT_CLASS(FdStrainRosetteKit, SoBaseKit, "BaseKit");
} 

FdStrainRosetteKit::FdStrainRosetteKit()
{
   SO_KIT_CONSTRUCTOR(FdStrainRosetteKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_ENTRY(transSep,   SoSeparator,    FALSE, this, \x0 ,    TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(firstTrans, SoTransform,    FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(appearance, FdAppearanceKit,FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(backPt,     FdBackPointer,  TRUE,  transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(elmCoords,  SoCoordinate3,   FALSE, transSep,\x0  , TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(elmShape,   SoIndexedLineSet, FALSE, transSep,\x0  , TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(secondTrans,SoTransform,    FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(smallSep,   SoSeparator,    FALSE, transSep, \x0 ,TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(scale,      SoScale,        FALSE, smallSep,\x0  , TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(smallSymbol,FdSymbolKit,    TRUE,  smallSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(largeSymbol,FdSymbolKit,    TRUE,  transSep, \x0 ,TRUE );

   SO_KIT_INIT_INSTANCE();
}
 
FdStrainRosetteKit::~FdStrainRosetteKit()
{
}
