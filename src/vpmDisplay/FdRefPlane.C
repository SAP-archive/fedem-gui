// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdRefPlane.H"
#include "vpmDisplay/FdSymbolDefs.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdExtraGraphics.H"
#include "vpmDisplay/FdRefPlaneKit.H"
#include "vpmDisplay/FdMechanismKit.H"
#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdDB.H"
#include "vpmDisplay/FdConverter.H"
#include "vpmDB/FmRefPlane.H"

#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoDrawStyle.h>


/**********************************************************************
 *
 * CLASS FdRefPlane
 *
 **********************************************************************/

Fmd_SOURCE_INIT(FDREFPLANE,FdRefPlane,FdObject);

FdRefPlane::FdRefPlane(FmRefPlane * pt) : FdObject()
{
  Fmd_CONSTRUCTOR_INIT(FdRefPlane);

  itsFmOwner = pt;
  FdBackPointer * bp_pointer;

  itsKit = new FdRefPlaneKit;
  itsKit->ref();

  //set up backpointer
  
  bp_pointer = SO_GET_PART(itsKit,"backPt",FdBackPointer);
  bp_pointer->setPointer(this);

  this->highlightBoxId = NULL;
}


FdRefPlane::~FdRefPlane()
{
  this->fdDisconnect();
  itsKit->unref();
}


SoNodeKitListPart* FdRefPlane::getListSw() const
{
  return SO_GET_PART(FdDB::getMechanismKit(),"refPlaneListSw",SoNodeKitListPart);
}


bool FdRefPlane::updateFdTopology(bool)
{ 
  return this->updateFdCS();
}


bool FdRefPlane::updateFdApperance()
{
  FmRefPlane * refPlane = (FmRefPlane*)itsFmOwner;
   
  //Plane Appearance:

  SoMaterial* material = SO_GET_PART(itsKit,"planeMaterial",SoMaterial);

  material->diffuseColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->ambientColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->emissiveColor.setValue(SbVec3f(0,0,0));
  material->transparency.setValue((float)refPlane->getTransparency());
 
  // Frame Appearance:

  material = SO_GET_PART(itsKit,"lineMaterial",SoMaterial);

  material->diffuseColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->ambientColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->specularColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->emissiveColor.setValue(SbVec3f(0,0,0));

  SoDrawStyle *drawStyle = SO_GET_PART(itsKit,"frameStyle",SoDrawStyle);   
  drawStyle->lineWidth.setValue(0);

  // CsSymbol Appearance :

  material = SO_GET_PART(itsKit,"csAppearance.material",SoMaterial);

  material->diffuseColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->ambientColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->specularColor.setValue(FdConverter::toSbVec3f(refPlane->getRGBColor()));
  material->emissiveColor.setValue(SbVec3f(0,0,0));

  drawStyle = SO_GET_PART(itsKit,"csStyle",SoDrawStyle);   
  drawStyle->lineWidth.setValue(0);
 
  return true;
}


bool FdRefPlane::updateFdCS()
{
  SoTransform* transform = SO_GET_PART(itsKit,"planeTransform",SoTransform);
  transform->setMatrix(FdConverter::toSbMatrix(((FmRefPlane*)itsFmOwner)->getLocalCS())); 
  return true;
}  


bool FdRefPlane::updateFdDetails()
{ 
  // Make the refplane:

  float x,y;
  
  x = (float)((FmRefPlane*)itsFmOwner)->getWidth();
  y = (float)((FmRefPlane*)itsFmOwner)->getHeight();
  
  //SoDrawStyle * ds = SO_GET_PART(itsKit,"drawStyle", SoDrawStyle);

  //if(((FmRefPlane*)itsFmOwner)->isVisible())
  // ds->style.setValue(SoDrawStyle::LINES); 
  // else 
  //   ds->style.setValue(SoDrawStyle::INVISIBLE); 

  // Setting plane size and shape:

  SoScale * planeScale =  SO_GET_PART(itsKit,"planeSize", SoScale);  
  planeScale->scaleFactor.setValue(x,y,1);

  SoCoordinate3 * coords =  SO_GET_PART(itsKit,"planeCoords",SoCoordinate3);  
  coords->point.set1Value(0,-0.5,-0.5,0);
  coords->point.set1Value(1,-0.5,0.5,0);
  coords->point.set1Value(2,0.5,0.5,0);			  
  coords->point.set1Value(3,0.5,-0.5,0);

  SoIndexedFaceSet * plane = SO_GET_PART(itsKit,"planeShape",SoIndexedFaceSet);
  plane->coordIndex.set1Value(0,0);
  plane->coordIndex.set1Value(1,1);
  plane->coordIndex.set1Value(2,2);
  plane->coordIndex.set1Value(3,3);
  plane->coordIndex.set1Value(4,SO_END_FACE_INDEX);

  SoIndexedLineSet * frame = SO_GET_PART(itsKit,"frameShape",SoIndexedLineSet);
  frame->coordIndex.set1Value(0,0);
  frame->coordIndex.set1Value(1,1);
  frame->coordIndex.set1Value(2,2);
  frame->coordIndex.set1Value(3,3);
  frame->coordIndex.set1Value(4,0);
  frame->coordIndex.set1Value(5,SO_END_FACE_INDEX);

  // Setting cs arrow symbol:
  
  SoTranslation * csTrans = SO_GET_PART(itsKit, "csTranslation",SoTranslation);
  csTrans->translation.setValue(-0.45f*x,-0.45f*y,0);

  itsKit->setPart("csSymbol",FdSymbolDefs::getSymbol(FdSymbolDefs::REFCS));
  itsKit->setPart("csSymbol.scale",NULL);
  SoTransform* csScale = SO_GET_PART(itsKit,"csSymbol.scale", SoTransform);  
  csScale->scaleFactor.setValue(0.1f*x,0.1f*y,1);

  return true;
}


void FdRefPlane::showHighlight()
{
  if(!FdDB::isUsingLineHighlight())
    {
      if (this->highlightBoxId)
        {
          FdExtraGraphics::removeBBox(this->highlightBoxId);
          this->highlightBoxId = NULL;
        }
      this->highlightBoxId = FdExtraGraphics::showBBox(this->itsKit);
    }
  else
    {
      SoMaterial *lineMaterial   = SO_GET_PART(this->itsKit, "lineMaterial", SoMaterial);
      SoMaterial *planeMaterial  = SO_GET_PART(this->itsKit, "planeMaterial", SoMaterial);
      SoMaterial *symbolMaterial = SO_GET_PART(this->itsKit, "csAppearance.material", SoMaterial);
      
      FdSymbolDefs::makeMaterialHighlight(lineMaterial);
      FdSymbolDefs::makeMaterialHighlight(planeMaterial);
      FdSymbolDefs::makeMaterialHighlight(symbolMaterial);
    }
}

void FdRefPlane::hideHighlight()
{
  if(this->highlightBoxId){
    FdExtraGraphics::removeBBox(this->highlightBoxId);    
    this->highlightBoxId = NULL;
  }
  
  this->updateFdApperance();
}
