// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodes/SoComplexity.h>


#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdCamJointKit.H"
#include "vpmDisplay/FdCurveKit.H"

SO_KIT_SOURCE(FdCamJointKit); 

SoComplexity * FdCamJointKit::ourCurveCompexity = 0;

void FdCamJointKit::init()
{
   SO_KIT_INIT_CLASS(FdCamJointKit, SoBaseKit, "BaseKit");
   ourCurveCompexity = new SoComplexity;
   ourCurveCompexity->type = SoComplexity::SCREEN_SPACE;
   ourCurveCompexity->value = 1;
   ourCurveCompexity->ref();
} 

//    Constructor

FdCamJointKit::FdCamJointKit()
{
   SO_KIT_CONSTRUCTOR(FdCamJointKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_LIST_ENTRY(masterList,SoGroup,     TRUE, this,\x0, FdTransformKit, TRUE ); 

   SO_KIT_ADD_CATALOG_ENTRY(     curves,    SoSeparator,      FALSE,this,\x0, TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(     detailLevel, SoComplexity,    TRUE, curves, \x0, TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(     camTrans,  SoTransform,      TRUE, curves, \x0, TRUE );
   SO_KIT_ADD_CATALOG_LIST_ENTRY(curveList, SoGroup,          TRUE, curves, \x0, FdCurveKit,     TRUE );

   SO_KIT_ADD_CATALOG_ENTRY(     slave ,    FdTransformKit, TRUE, this,\x0, TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(     backPt ,   FdBackPointer,  TRUE, this,\x0, TRUE );
 
   SO_KIT_INIT_INSTANCE();

   this->setPart("detailLevel", ourCurveCompexity);
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdCamJointKit::~FdCamJointKit()
{

}

