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
#include "vpmDisplay/FdSprDaTransformKit.H"

SO_KIT_SOURCE(FdSprDaTransformKit); 


void FdSprDaTransformKit::init()
{
   SO_KIT_INIT_CLASS(FdSprDaTransformKit,FdTransformKit , "FdTransformKit");
} 

//    Constructor

FdSprDaTransformKit::FdSprDaTransformKit()
{
   SO_KIT_CONSTRUCTOR(FdSprDaTransformKit); 
   isBuiltIn = TRUE;
    
   SO_KIT_INIT_INSTANCE();
   
   placerEngine = new FdSprDaPlacer;
   matrixMaker1 = new SoComposeMatrix;
   matrixMaker2 = new SoComposeMatrix;
   
   transCat1   = new SoConcatenate(SoMFVec3f::getClassTypeId());
   rotCat1     = new SoConcatenate(SoMFRotation::getClassTypeId());
   scaleCat1   = new SoConcatenate(SoMFVec3f::getClassTypeId());
   scaleOriCat1= new SoConcatenate(SoMFRotation::getClassTypeId());
   centerCat1  = new SoConcatenate(SoMFVec3f::getClassTypeId());
   
   transCat2   = new SoConcatenate(SoMFVec3f::getClassTypeId());
   rotCat2     = new SoConcatenate(SoMFRotation::getClassTypeId());
   scaleCat2   = new SoConcatenate(SoMFVec3f::getClassTypeId());
   scaleOriCat2= new SoConcatenate(SoMFRotation::getClassTypeId());
   centerCat2  = new SoConcatenate(SoMFVec3f::getClassTypeId());
 
   placerEngine->ref();
   matrixMaker1->ref();
   matrixMaker2->ref();
   
   transCat1->ref();
   rotCat1->ref();
   scaleCat1->ref();
   scaleOriCat1->ref();
   centerCat1->ref();
   
   transCat2->ref();
   rotCat2->ref();
   scaleCat2->ref();
   scaleOriCat2->ref();
   centerCat2->ref();
   
   setUp();
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdSprDaTransformKit::~FdSprDaTransformKit()
{
  placerEngine->unref();
  matrixMaker1->unref();
  matrixMaker2->unref();
  
  transCat1->unref();
  rotCat1->unref();
  scaleCat1->unref();
  scaleOriCat1->unref();
  centerCat1->unref();
  
  transCat2->unref();
  rotCat2->unref();
  scaleCat2->unref();
  scaleOriCat2->unref();
  centerCat2->unref();
}

void FdSprDaTransformKit::connectFirstSpace(SoTransform* global, SoTransform* local)
{
  
  this->transCat1->input[0]->connectFrom(&global->translation);
  this->transCat1->input[1]->connectFrom(&local->translation);

  this->rotCat1->input[0]->connectFrom(&global->rotation);
  this->rotCat1->input[1]->connectFrom(&local->rotation);

  this->scaleCat1->input[0]->connectFrom(&global->scaleFactor);
  this->scaleCat1->input[1]->connectFrom(&local->scaleFactor);
 
  this->scaleOriCat1->input[0]->connectFrom(&global->scaleOrientation);
  this->scaleOriCat1->input[1]->connectFrom(&local->scaleOrientation);

  this->centerCat1->input[0]->connectFrom(&global->center);
  this->centerCat1->input[1]->connectFrom(&local->center);
 
}

void FdSprDaTransformKit::connectSecondSpace(SoTransform* global, SoTransform* local)
{

  this->transCat2->input[0]->connectFrom(&global->translation);
  this->transCat2->input[1]->connectFrom(&local->translation);

  this->rotCat2->input[0]->connectFrom(&global->rotation);
  this->rotCat2->input[1]->connectFrom(&local->rotation);

  this->scaleCat2->input[0]->connectFrom(&global->scaleFactor);
  this->scaleCat2->input[1]->connectFrom(&local->scaleFactor);
 
  this->scaleOriCat2->input[0]->connectFrom(&global->scaleOrientation);
  this->scaleOriCat2->input[1]->connectFrom(&local->scaleOrientation);

  this->centerCat2->input[0]->connectFrom(&global->center);
  this->centerCat2->input[1]->connectFrom(&local->center);
 
}



void FdSprDaTransformKit::setUp()

{
  SoTransform * trans;
  // Set up input connections of the engine:  

  placerEngine->firstSpace.connectFrom(&matrixMaker1->matrix);
  placerEngine->secondSpace.connectFrom(&matrixMaker2->matrix);

  // Set up concatenation engines for input creation to 
  // the matrix makers

  matrixMaker1->translation.connectFrom(transCat1->output);
  matrixMaker1->rotation.connectFrom(rotCat1->output);
  matrixMaker1->scaleFactor.connectFrom(scaleCat1->output);
  matrixMaker1->scaleOrientation.connectFrom(scaleOriCat1->output);
  matrixMaker1->center.connectFrom(centerCat1->output);
  
  matrixMaker2->translation.connectFrom(transCat2->output);
  matrixMaker2->rotation.connectFrom(rotCat2->output);
  matrixMaker2->scaleFactor.connectFrom(scaleCat2->output);
  matrixMaker2->scaleOrientation.connectFrom(scaleOriCat2->output);
  matrixMaker2->center.connectFrom(centerCat2->output);
  

  // Set up output connection
  trans = SO_GET_PART(this, "firstTrans",SoTransform);
  trans->translation.connectFrom(&placerEngine->translation);
  trans->rotation.connectFrom(&placerEngine->rotation);
  trans->scaleFactor.connectFrom(&placerEngine->scaleFactor);

}
