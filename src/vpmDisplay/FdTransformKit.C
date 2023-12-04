// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransform.h>

#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdAppearanceKit.H"
#include "vpmDisplay/FdBackPointer.H"

SO_KIT_SOURCE(FdTransformKit); 


void FdTransformKit::init()
{
   SO_KIT_INIT_CLASS(FdTransformKit, SoBaseKit, "BaseKit");
} 


FdTransformKit::FdTransformKit()
{
   SO_KIT_CONSTRUCTOR(FdTransformKit); 
   isBuiltIn = TRUE;
   
   SO_KIT_ADD_CATALOG_ENTRY(transSep,   SoSeparator,    FALSE, this, \x0 ,    TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(firstTrans, SoTransform,    FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(secondTrans,SoTransform,    FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(appearance, FdAppearanceKit,FALSE, transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(backPt,     FdBackPointer,  TRUE,  transSep, \x0 ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(symbol,     FdSymbolKit,    TRUE,  transSep, \x0 ,TRUE );
 
   SO_KIT_INIT_INSTANCE();
   
}
 


FdTransformKit::~FdTransformKit()
{
}
