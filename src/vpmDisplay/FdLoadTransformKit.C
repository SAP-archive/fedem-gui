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
#include <Inventor/nodekits/SoSubKit.h>
#ifndef SO_KIT_ADD_FIELD
#define SO_KIT_ADD_FIELD(fieldName,defValue)                                  \
    SO_NODE_ADD_FIELD(fieldName,defValue)
#endif

#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdLoadTransformKit.H"


SO_KIT_SOURCE(FdLoadTransformKit); 


void FdLoadTransformKit::init()
{
   SO_KIT_INIT_CLASS(FdLoadTransformKit,FdTransformKit , "FdTransformKit");
} 

//    Constructor

FdLoadTransformKit::FdLoadTransformKit()
{
   SO_KIT_CONSTRUCTOR(FdLoadTransformKit); 
   isBuiltIn = TRUE;
 
   SO_KIT_ADD_FIELD(attackCoord, (0,0,0));
   SO_KIT_ADD_FIELD(firstCoord, (1,0,0));
   SO_KIT_ADD_FIELD(secondCoord, (-1,0,0));  

   SO_KIT_INIT_INSTANCE();
   
   placerEngine = new FdLoadDirEngine;
   attackMxMaker = new SoComposeMatrix;
   matrixMaker1 = new SoComposeMatrix;
   matrixMaker2 = new SoComposeMatrix;

   attackTransCat = new SoConcatenate(SoMFVec3f::getClassTypeId());
   attackRotCat    = new SoConcatenate(SoMFRotation::getClassTypeId());
   attackScaleCat  = new SoConcatenate(SoMFVec3f::getClassTypeId());
   attackScaleOriCat = new SoConcatenate(SoMFRotation::getClassTypeId());
   attackCenterCat = new SoConcatenate(SoMFVec3f::getClassTypeId());
  
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
   attackMxMaker->ref();
   matrixMaker1->ref();
   matrixMaker2->ref();

   attackTransCat->ref();
   attackRotCat->ref();   
   attackScaleCat->ref(); 
   attackScaleOriCat->ref();
   attackCenterCat->ref(); 
   
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

FdLoadTransformKit::~FdLoadTransformKit()
{
  placerEngine->unref();
  attackMxMaker->unref();
  matrixMaker1->unref();
  matrixMaker2->unref();

  attackTransCat->unref();
  attackRotCat->unref();   
  attackScaleCat->unref(); 
  attackScaleOriCat->unref();
  attackCenterCat->unref(); 
  
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

void FdLoadTransformKit::setUp()

{
  SoTransform * trans;
  // Set up input connections of the engine:  

  placerEngine->firstCoord.connectFrom(&firstCoord);
  placerEngine->secondCoord.connectFrom(&secondCoord);
  placerEngine->attackCoord.connectFrom(&attackCoord);

  placerEngine->firstSpace.connectFrom(&matrixMaker1->matrix);
  placerEngine->secondSpace.connectFrom(&matrixMaker2->matrix);
  placerEngine->attackSpace.connectFrom(&attackMxMaker->matrix);


  // Set up concatenation engines for input creation to 
  // the matrix makers

  attackMxMaker->translation.connectFrom(attackTransCat->output);
  attackMxMaker->rotation.connectFrom(attackRotCat->output);
  attackMxMaker->scaleFactor.connectFrom(attackScaleCat->output);
  attackMxMaker->scaleOrientation.connectFrom(attackScaleOriCat->output);
  attackMxMaker->center.connectFrom(attackCenterCat->output);

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
  trans = SO_GET_PART(this, "secondTrans",SoTransform);

  trans->rotation.connectFrom(&placerEngine->rotation);
  trans->translation.connectFrom(&placerEngine->translation);

}

void FdLoadTransformKit::connectAttackSpace(SoTransform* global, SoTransform* local)
{
  if (global)
    {
      this->attackTransCat->input[0]->connectFrom(&global->translation);
      this->attackRotCat->input[0]->connectFrom(&global->rotation);
      this->attackScaleCat->input[0]->connectFrom(&global->scaleFactor);
      this->attackScaleOriCat->input[0]->connectFrom(&global->scaleOrientation);
      this->attackCenterCat->input[0]->connectFrom(&global->center);
    }

  if (local)
    {
      this->attackTransCat->input[1]->connectFrom(&local->translation);
      this->attackRotCat->input[1]->connectFrom(&local->rotation);
      this->attackScaleCat->input[1]->connectFrom(&local->scaleFactor);
      this->attackScaleOriCat->input[1]->connectFrom(&local->scaleOrientation);
      this->attackCenterCat->input[1]->connectFrom(&local->center);
    }

}

void FdLoadTransformKit::disConnectAttackSpace()
{
  this->attackTransCat->input[0]->disconnect();
  this->attackTransCat->input[1]->disconnect();
  
  this->attackRotCat->input[0]->disconnect();
  this->attackRotCat->input[1]->disconnect();
  
  this->attackScaleCat->input[0]->disconnect();
  this->attackScaleCat->input[1]->disconnect();
  
  this->attackScaleOriCat->input[0]->disconnect();
  this->attackScaleOriCat->input[1]->disconnect();
  
  this->attackCenterCat->input[0]->disconnect();
  this->attackCenterCat->input[1]->disconnect();  
}

void FdLoadTransformKit::connectFirstSpace(SoTransform* global, SoTransform* local)
{
  if (global)
    {
      this->transCat1->input[0]->connectFrom(&global->translation);
      this->rotCat1->input[0]->connectFrom(&global->rotation);
      this->scaleCat1->input[0]->connectFrom(&global->scaleFactor);
      this->scaleOriCat1->input[0]->connectFrom(&global->scaleOrientation);
      this->centerCat1->input[0]->connectFrom(&global->center);
    }

  if (local)
    {
      this->transCat1->input[1]->connectFrom(&local->translation);
      this->rotCat1->input[1]->connectFrom(&local->rotation);
      this->scaleCat1->input[1]->connectFrom(&local->scaleFactor);
      this->scaleOriCat1->input[1]->connectFrom(&local->scaleOrientation);
      this->centerCat1->input[1]->connectFrom(&local->center);
    }

}

void FdLoadTransformKit::disConnectFirstSpace()
{
  this->transCat1->input[0]->disconnect();
  this->transCat1->input[1]->disconnect();
  
  this->rotCat1->input[0]->disconnect();
  this->rotCat1->input[1]->disconnect();
  
  this->scaleCat1->input[0]->disconnect();
  this->scaleCat1->input[1]->disconnect();
  
  this->scaleOriCat1->input[0]->disconnect();
  this->scaleOriCat1->input[1]->disconnect();
  
  this->centerCat1->input[0]->disconnect();
  this->centerCat1->input[1]->disconnect();  
}

void FdLoadTransformKit::connectSecondSpace(SoTransform* global, SoTransform* local)
{
  if (global)
    {
      this->transCat2->input[0]->connectFrom(&global->translation);
      this->rotCat2->input[0]->connectFrom(&global->rotation);
      this->scaleCat2->input[0]->connectFrom(&global->scaleFactor);
      this->scaleOriCat2->input[0]->connectFrom(&global->scaleOrientation);
      this->centerCat2->input[0]->connectFrom(&global->center);
    }

  if (local)
    {
      this->transCat2->input[1]->connectFrom(&local->translation);
      this->rotCat2->input[1]->connectFrom(&local->rotation);
      this->scaleCat2->input[1]->connectFrom(&local->scaleFactor);
      this->scaleOriCat2->input[1]->connectFrom(&local->scaleOrientation);
      this->centerCat2->input[1]->connectFrom(&local->center);
    }

}
void FdLoadTransformKit::disConnectSecondSpace()
{
  this->transCat2->input[0]->disconnect();
  this->transCat2->input[1]->disconnect();
  
  this->rotCat2->input[0]->disconnect();
  this->rotCat2->input[1]->disconnect();
  
  this->scaleCat2->input[0]->disconnect();
  this->scaleCat2->input[1]->disconnect();
  
  this->scaleOriCat2->input[0]->disconnect();
  this->scaleOriCat2->input[1]->disconnect();
  
  this->centerCat2->input[0]->disconnect();
  this->centerCat2->input[1]->disconnect();  
}
