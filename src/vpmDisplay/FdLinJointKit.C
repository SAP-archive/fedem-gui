// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodes/SoSwitch.h>


#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdLinJointKit.H"
#include "vpmDisplay/FdSprDaTransformKit.H"

SO_KIT_SOURCE(FdLinJointKit); 


void FdLinJointKit::init()
{
   SO_KIT_INIT_CLASS(FdLinJointKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdLinJointKit::FdLinJointKit()
{
   SO_KIT_CONSTRUCTOR(FdLinJointKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_LIST_ENTRY(masterList,SoGroup ,TRUE,
				 this, \x0  ,FdTransformKit, TRUE );

   SO_KIT_ADD_CATALOG_ENTRY(lineSymbol,FdSprDaTransformKit ,TRUE,
			    this, \x0 ,TRUE );

   SO_KIT_ADD_CATALOG_ENTRY(slave ,    FdTransformKit ,TRUE,
			    this, \x0 ,TRUE );
   
   SO_KIT_ADD_CATALOG_ENTRY(backPt ,   FdBackPointer ,TRUE,
			    this, \x0 ,TRUE );
   
 
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdLinJointKit::~FdLinJointKit()
{

}

