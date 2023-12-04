// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoGroup.h>

#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdTriadSwKit.H"


SO_KIT_SOURCE(FdTriadSwKit); 


void FdTriadSwKit::init()
{
   SO_KIT_INIT_CLASS(FdTriadSwKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdTriadSwKit::FdTriadSwKit()
{
   SO_KIT_CONSTRUCTOR(FdTriadSwKit); 
   isBuiltIn = TRUE;
   
   SO_KIT_ADD_CATALOG_LIST_ENTRY(triadSw, SoSwitch,         FALSE,
				 this, \x0 ,FdTransformKit,TRUE );

   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdTriadSwKit::~FdTriadSwKit()
{
}
