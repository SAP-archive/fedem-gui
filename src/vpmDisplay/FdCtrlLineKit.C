// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransform.h>

#include "vpmDisplay/FdAppearanceKit.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdCtrlLineKit.H"
#include "vpmDisplay/FdSymbolKit.H"


SO_KIT_SOURCE(FdCtrlLineKit); 


void FdCtrlLineKit::init()
{
   SO_KIT_INIT_CLASS(FdCtrlLineKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdCtrlLineKit::FdCtrlLineKit()
{
   SO_KIT_CONSTRUCTOR(FdCtrlLineKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_ENTRY(lineSep,     SoSeparator,     TRUE, this, \x0 ,TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(appearance,  FdAppearanceKit, TRUE, lineSep, \x0 ,TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(symbol,      FdSymbolKit,     TRUE, lineSep, \x0 ,TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(points,      SoPointSet,      TRUE, lineSep, \x0 ,TRUE);
   SO_KIT_ADD_CATALOG_ENTRY(backPt,      FdBackPointer ,  TRUE, lineSep, \x0 ,TRUE );
 
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdCtrlLineKit::~FdCtrlLineKit()
{
}
