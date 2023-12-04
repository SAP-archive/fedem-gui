// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLevelOfDetail.h>
#include <Inventor/nodes/SoMaterial.h>

#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdPipeSurfaceKit.H"


SO_KIT_SOURCE(FdPipeArcKit); 

SoLightModel * FdPipeArcKit::ourLineLightModel = 0;

void FdPipeArcKit::init()
{
   SO_KIT_INIT_CLASS(FdPipeArcKit, SoBaseKit, "BaseKit");
   ourLineLightModel = new SoLightModel;
   ourLineLightModel->model.setValue(SoLightModel::BASE_COLOR);


} 

//    Constructor


FdPipeArcKit::FdPipeArcKit()
{
   SO_KIT_CONSTRUCTOR(FdPipeArcKit); 
   isBuiltIn = TRUE;


 SO_KIT_ADD_CATALOG_ENTRY( rootSep,         SoSeparator,     TRUE, this, \x0, TRUE);
   SO_KIT_ADD_CATALOG_ENTRY( levelOfDetail,   SoLevelOfDetail, TRUE, rootSep,          \x0, TRUE);
     SO_KIT_ADD_CATALOG_ENTRY( fullSep,         SoSeparator,     TRUE, levelOfDetail, \x0, TRUE);
       SO_KIT_ADD_CATALOG_ENTRY( fFaceLineSw,     SoSwitch,        TRUE, fullSep,       \x0, TRUE);
         SO_KIT_ADD_CATALOG_ENTRY( fFaceSep,        SoSeparator,     TRUE, fFaceLineSw,   \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( fFaces,          SoIndexedFaceSet,TRUE, fFaceSep,      \x0, TRUE); 
         SO_KIT_ADD_CATALOG_ENTRY( fLineSep,        SoSeparator,     TRUE, fFaceLineSw,   \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( fLineMaterial,   SoMaterial,      TRUE, fLineSep,      \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( fLLightModel,    SoLightModel,    TRUE, fLineSep,      \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( fLines,          SoIndexedLineSet,TRUE, fLineSep,      \x0, TRUE); 
     SO_KIT_ADD_CATALOG_ENTRY( simpleSep,       SoSeparator,     TRUE, levelOfDetail, \x0, TRUE);
       SO_KIT_ADD_CATALOG_ENTRY( sFaceLineSw,     SoSwitch,        TRUE, simpleSep,     \x0, TRUE);
         SO_KIT_ADD_CATALOG_ENTRY( sFaceSep,        SoSeparator,     TRUE, sFaceLineSw,   \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( sFaces,          SoIndexedFaceSet,TRUE, sFaceSep,      \x0, TRUE); 
         SO_KIT_ADD_CATALOG_ENTRY( sLineSep,        SoSeparator,     TRUE, sFaceLineSw,   \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( sLineMaterial,   SoMaterial,      TRUE, sLineSep,      \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( sLLightModel,    SoLightModel,    TRUE, sLineSep,      \x0, TRUE); 
           SO_KIT_ADD_CATALOG_ENTRY( sLines,          SoIndexedLineSet,TRUE, sLineSep,      \x0, TRUE);           
     SO_KIT_ADD_CATALOG_ENTRY( cLineSep,        SoSeparator,     TRUE, levelOfDetail, \x0, TRUE);
       SO_KIT_ADD_CATALOG_ENTRY( cLineMaterial,   SoMaterial,      TRUE, fLineSep,      \x0, TRUE); 
       SO_KIT_ADD_CATALOG_ENTRY( cLine,           SoLineSet,       TRUE, cLineSep,      \x0, TRUE);       
      

   SO_KIT_INIT_INSTANCE();
   
//   this->setPart("sLLightModel", ourLineLightModel);
 //  this->setPart("fLLightModel", ourLineLightModel);
   SO_GET_PART(this, "sLines", SoIndexedLineSet);
   SO_GET_PART(this, "fLines", SoIndexedLineSet);
   ((SoLevelOfDetail*)(this->levelOfDetail.getValue()))->screenArea.set1Value(0, 6000);
   ((SoLevelOfDetail*)(this->levelOfDetail.getValue()))->screenArea.set1Value(1, 1000);
   ((SoSwitch *) (this->fFaceLineSw.getValue()))->whichChild.setValue(SO_SWITCH_ALL);
   ((SoSwitch *) (this->sFaceLineSw.getValue()))->whichChild.setValue(SO_SWITCH_ALL);
    SoSwitch *sw = (SoSwitch *)(this->getAnyPart("fFaceLineSw", true));
    sw->whichChild.setValue(SO_SWITCH_ALL);
    sw = (SoSwitch *)(this->getAnyPart("sFaceLineSw", true));
    sw->whichChild.setValue(SO_SWITCH_ALL);
 
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdPipeArcKit::~FdPipeArcKit()
{

}


////////////////////////////////////////////////////////////////////////////////////////

SO_KIT_SOURCE(FdPipeSurfaceKit); 

void FdPipeSurfaceKit::init()
{
   SO_KIT_INIT_CLASS(FdPipeSurfaceKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdPipeSurfaceKit::FdPipeSurfaceKit()
{
   SO_KIT_CONSTRUCTOR(FdPipeSurfaceKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_ENTRY(      material, SoMaterial,    TRUE, this, \x0, TRUE );
   SO_KIT_ADD_CATALOG_LIST_ENTRY( pipeList, SoSeparator,       TRUE, this, \x0, SoSeparator, TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(      backPt,   FdBackPointer, TRUE, this, \x0, TRUE );
 
   SO_KIT_INIT_INSTANCE();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdPipeSurfaceKit::~FdPipeSurfaceKit()
{

}




