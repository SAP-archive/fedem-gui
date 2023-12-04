// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdUserDefinedElement.H"
#include "vpmDisplay/FdMechanismKit.H"
#include "vpmDB/FmUserDefinedElement.H"
#include "vpmDB/FmGlobalViewSettings.H"
#include "vpmDB/FmDB.H"

#include "vpmDisplay/FdDB.H"
#include "vpmDisplay/FdSymbolDefs.H"
#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdConverter.H"
#include "vpmDisplay/FdFEModelKit.H"
#include "FFdCadModel/FdCadHandler.H"

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoDrawStyle.h>


Fmd_SOURCE_INIT(FDUSERDEFINEDELEMENT,FdUserDefinedElement,FdLink);


FdUserDefinedElement::FdUserDefinedElement(FmUserDefinedElement* pt) : FdLink(pt)
{
  Fmd_CONSTRUCTOR_INIT(FdUserDefinedElement);
}


SoNodeKitListPart* FdUserDefinedElement::getListSw() const
{
  return SO_GET_PART(FdDB::getMechanismKit(),"uelmListSw",SoNodeKitListPart);
}


bool FdUserDefinedElement::updateFdDetails()
{
  FmUserDefinedElement* uelm = (FmUserDefinedElement*)this->itsFmOwner;

  FdDB::setAutoRedraw(false);

  // Select VRML or CAD visualization. Load the appropriate if not loaded already.

  if (myCadHandler->getCadComponent())
    IAmUsingGenPartVis = this->createCadViz();
  else
    IAmUsingGenPartVis = this->loadVrmlViz();

  if (IAmUsingGenPartVis)
    myFEKit->setVizMode(FdFEGroupPart::SPECIAL);
  else
    myFEKit->setVizMode(FdFEGroupPart::NORMAL);

  if (!FmDB::getActiveViewSettings()->getSolidMode()) {
    myFEKit->setDrawStyle(FdFEVisControl::LINES);
    myFEKit->setLineDetail(FdFEVisControl::FULL);
  }
  else if (FmDB::getActiveViewSettings()->getSolidModeWithEdges()){
    myFEKit->setDrawStyle(FdFEVisControl::SOLID_LINES);
    myFEKit->setLineDetail(FdFEVisControl::FULL);
  }
  else {
    myFEKit->setDrawStyle(FdFEVisControl::SOLID);
    myFEKit->setLineDetail(FdFEVisControl::OFF);
  }

  switch (uelm->getModelType())
  {
  case FmLink::FULL:
    myFEKit->setDrawDetail(FdFEVisControl::FULL);
    break;

  case FmLink::RED_FULL:
    myFEKit->setDrawDetail(FdFEVisControl::RED_FULL);
    break;

  case FmLink::SURFACE:
    myFEKit->setDrawDetail(FdFEVisControl::SURFACE);
    break;

  case FmLink::REDUCED:
    myFEKit->setDrawDetail(FdFEVisControl::OUTLINE);
    break;

  default:
    myFEKit->setDrawDetail(FdFEVisControl::OFF);
    break;
  }

  switch (uelm->getMeshType())
  {
  case FmLink::RED_FULL:
  case FmLink::FULL:
    myFEKit->setLineDetail(FdFEVisControl::FULL);
    break;

  case FmLink::SURFACE:
    myFEKit->setLineDetail(FdFEVisControl::SURFACE);
    break;

  case FmLink::REDUCED:
    myFEKit->setLineDetail(FdFEVisControl::OUTLINE);
    break;

  case FmLink::REDUCED_NO1D:
    myFEKit->setLineDetail(FdFEVisControl::OUTLINE_NO1D);
    break;

  case FmLink::SIMPLIFIED:
  default:
    myFEKit->setLineDetail(FdFEVisControl::OFF);
    break;
  }

  myFEKit->show(uelm->getModelType() != FmLink::OFF);
  myFEKit->setCoGCSToggle(false);
  myFEKit->setInternalCSToggle(false);

  FdDB::setAutoRedraw(true);

  this->updateSimplifiedViz();

  return true;
}


void FdUserDefinedElement::updateSimplifiedViz()
{
  this->showCS(FmDB::getActiveViewSettings()->visiblePartCS());

  SoSwitch* spiderSwitch = SO_GET_PART(itsKit, "spiderSwitch", SoSwitch);
  SoSwitch* cgSymbolSwitch = SO_GET_PART(itsKit, "cgSymbolSwitch", SoSwitch);

  spiderSwitch->removeAllChildren();
  cgSymbolSwitch->removeAllChildren();

  SoSeparator* cgSep = new SoSeparator();
  cgSymbolSwitch->addChild(cgSep);
  SoTransform* transform = new SoTransform();

  FmUserDefinedElement* uelm = (FmUserDefinedElement*)this->itsFmOwner;
  transform->setMatrix(FdConverter::toSbMatrix(uelm->getPositionCG(false)));

  cgSep->addChild(transform);
  cgSep->addChild(FdSymbolDefs::getGlobalSymbolStyle());
  cgSep->addChild(FdSymbolDefs::getSymbol(FdSymbolDefs::CENTER_OF_GRAVITY));

  SoSeparator* sep = new SoSeparator();
  SoCoordinate3* coords = new SoCoordinate3();
  SoIndexedLineSet* lines = new SoIndexedLineSet();

  spiderSwitch->addChild(sep);
  sep->addChild(coords);
  sep->addChild(FdSymbolDefs::getGlobalSymbolStyle());
  sep->addChild(lines);

  // Fetching triads
  std::vector<FmTriad*> triads;
  uelm->getTriads(triads);
  size_t i, numTriads = triads.size();

  // Calculating geometrical center
  FaVec3 center;
  for (i = 0; i < numTriads; i++)
    center += triads[i]->getLocalTranslation(uelm) / (double)numTriads;
  coords->point.set1Value(0, FdConverter::toSbVec3f(center));
  // Loop over triads again to set up coords and indices
  for (i = 0; i < numTriads; i++) {
    coords->point.set1Value(i+1, FdConverter::toSbVec3f(triads[i]->getLocalTranslation(uelm)));
    lines->coordIndex.set1Value(3*i+0, 0);  // center point
    lines->coordIndex.set1Value(3*i+1,i+1); // this point
    lines->coordIndex.set1Value(3*i+2,-1);  // sep
  }

  this->showCoGCS(FmDB::getActiveViewSettings()->visiblePartCoGCSs());

  if (IAmUsingGenPartVis || uelm->getModelType() == FmLink::OFF)
    spiderSwitch->whichChild.setValue(SO_SWITCH_NONE);
  else
    spiderSwitch->whichChild.setValue(SO_SWITCH_ALL);
}


void FdUserDefinedElement::showHighlight()
{
  itsKit->setPart("symbolMaterial",FdSymbolDefs::getHighlightMaterial());

  myFEKit->highlight(true,FdFEVisControl::OUTLINE);
}


void FdUserDefinedElement::hideHighlight()
{
  myFEKit->highlight(false);

  // Link coordinate system symbol color :

  this->itsKit->setPart("symbolMaterial",0);

  SoMaterial* symbolMaterial = SO_GET_PART(this->itsKit, "symbolMaterial", SoMaterial);
  SbVec3f RGBcolor = FdConverter::toSbVec3f(((FmLink*)this->itsFmOwner)->getRGBColor());

  symbolMaterial->diffuseColor.setValue(RGBcolor);
  symbolMaterial->ambientColor.setValue(RGBcolor);
  symbolMaterial->emissiveColor.setValue(RGBcolor);
}
