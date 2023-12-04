// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdBeam.H"
#include "vpmDisplay/FdMechanismKit.H"
#include "vpmDB/FmBeam.H"

#include "vpmDisplay/FdDB.H"
#include "vpmDisplay/FdSymbolDefs.H"
#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdConverter.H"
#include "vpmDisplay/FdFEModelKit.H"
#include "vpmDisplay/FdFEGroupPart.H"
#include "FFdCadModel/FdCadHandler.H"

#include "vpmDB/FmDB.H"
#include "vpmDB/FmGlobalViewSettings.H"
#include "vpmDB/FmTurbine.H"
#include "vpmDB/FmRiser.H"
#include "vpmDB/FmJacket.H"
#include "vpmDB/FmSoilPile.H"
#include "vpmDB/FmBladeProperty.H"
#include "vpmDB/FmBeamProperty.H"

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoDrawStyle.h>


Fmd_SOURCE_INIT(FDBEAM,FdBeam,FdLink);


FdBeam::FdBeam(FmBeam* pt) : FdLink(pt)
{
  Fmd_CONSTRUCTOR_INIT(FdBeam);
}


SoNodeKitListPart* FdBeam::getListSw() const
{
  return SO_GET_PART(FdDB::getMechanismKit(),"beamListSw",SoNodeKitListPart);
}


bool FdBeam::updateBeamDetails(FmBeam* beam, FdCadHandler* cadHandler)
{
  // Delete old visualization (overrides CAD visualization!)
  cadHandler->deleteCadData();

  // Get visualize 3D attribute
  bool visualize3D = beam->myVisualize3D.getValue();
  int visualize3DParent = 1;
  FmBeam::Ints visualize3DAngles = beam->myVisualize3DAngles.getValue();

  // Get parent shaft and check if we're visualizing 3D there
  FmShaft* pShaft = dynamic_cast<FmShaft*>(beam->getParentAssembly());
  if (pShaft != NULL)
    visualize3DParent = pShaft->visualize3Dts.getValue();

  // Get parent blade and check if we're visualizing 3D there
  FmBlade* pBlade = dynamic_cast<FmBlade*>(beam->getParentAssembly());
  if (pBlade != NULL)
    visualize3DParent = pBlade->visualize3Dts.getValue();

  // Get parent tower and check if we're visualizing 3D there
  FmTower* pTower = dynamic_cast<FmTower*>(beam->getParentAssembly());
  if (pTower != NULL)
    visualize3DParent = pTower->visualize3Dts.getValue();

  // Get parent riser and check if we're visualizing 3D there
  FmRiser* pRiser = dynamic_cast<FmRiser*>(beam->getParentAssembly());
  if (pRiser != NULL) {
    visualize3DParent = pRiser->visualize3Dts.getValue();
    if (visualize3DParent != 1)
      visualize3DAngles = pRiser->visualize3DAngles.getValue();
  }

  // Get parent jacket and check if we're visualizing 3D there
  FmJacket* pJacket = dynamic_cast<FmJacket*>(beam->getParentAssembly());
  if (pJacket != NULL)
    visualize3DParent = pJacket->visualize3Dts.getValue();

  // Get parent soil pile and check if we're visualizing 3D there
  FmSoilPile* pSoilPile = dynamic_cast<FmSoilPile*>(beam->getParentAssembly());
  if (pSoilPile != NULL) {
    visualize3DParent = pSoilPile->visualize3Dts.getValue();
    if (visualize3DParent != 1)
      visualize3DAngles = pSoilPile->visualize3DAngles.getValue();
  }

  if (visualize3DParent == 0)
    visualize3D = false;
  else if (visualize3DParent == 2)
    visualize3D = true;

  // Get cross section data object
  FmBeamProperty* pCS = dynamic_cast<FmBeamProperty*>(beam->getProperty());
  FmBladeProperty* pBP = dynamic_cast<FmBladeProperty*>(beam->getProperty());

  if (visualize3D)
  {
    FmTriad* tr1 = beam->getFirstTriad();
    FmTriad* tr2 = beam->getSecondTriad();
    if (tr1 == NULL || tr2 == NULL)
      return false;

    if (pCS != NULL && pCS->Do.getValue() > 0.0 &&
	pCS->crossSectionType.getValue() == FmBeamProperty::PIPE)
    {
      // Create pipe visualization
      cadHandler->createBeamViz_Pipe(tr1->getLocalTranslation(beam),
				     tr2->getLocalTranslation(beam),
				     pCS->Do.getValue(), pCS->Di.getValue(),
				     visualize3DAngles.first, visualize3DAngles.second);

      // If tower, set color to grey
      if (pTower != NULL)
	beam->setRGBColor(0.5,0.5,0.5);
      return true;
    }
    else if (pBP != NULL)
    {
      // Create blade visualization
      FmBladeDesign* pDesign = dynamic_cast<FmBladeDesign*>(pBP->getParentAssembly());
      if (pDesign != NULL)
      {
	// This is not the way to get the neighboring properties. Strongly consider revising this (KMO).
	FmBladeProperty* pBPcurr = dynamic_cast<FmBladeProperty*>(pDesign->getBladeProperty(beam->getID()/2 + beam->getID()%2 -1));
	FmBladeProperty* pBPprev = dynamic_cast<FmBladeProperty*>(pDesign->getBladeProperty(beam->getID()/2 + beam->getID()%2 -2));
	FmBladeProperty* pBPnext = dynamic_cast<FmBladeProperty*>(pDesign->getBladeProperty(beam->getID()/2 + beam->getID()%2 ));
	if (pBPprev == NULL) pBPprev = pBPcurr;
	if (pBPnext == NULL) pBPnext = pBPcurr;
	if (pBPcurr != NULL)
	{
	  int segmentPart = (beam->getID()+1)%2; // 0=first beam-section of segment, 1=second
	  cadHandler->createBeamViz_Blade(tr1, tr2, pBPcurr, pBPprev, pBPnext, segmentPart);
	  beam->setRGBColor(0.5,0.5,0.5); // Set color to grey
	  return true;
	}
      }
    }
  }

  // If blade-segment, revert to default-color if 3D-visualization is off
  if (pBlade != NULL && pBP != NULL)
    beam->setRGBColor(FmDB::getActiveViewSettings()->getLinkDefaultColor(pBP->getID()));

  // If tower, revert to default-color if 3D-visualization is off
  else if (pTower != NULL && pCS != NULL)
    beam->setRGBColor(FmDB::getActiveViewSettings()->getLinkDefaultColor(pCS->getID()));

  return false;
}


bool FdBeam::updateFdDetails()
{
  FmBeam* beam = (FmBeam*)this->itsFmOwner;

  FdDB::setAutoRedraw(false);

  // Create a visualization of beam elements based on cross section data
  updateBeamDetails(beam,myCadHandler);

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
  else if (FmDB::getActiveViewSettings()->getSolidModeWithEdges()) {
    myFEKit->setDrawStyle(FdFEVisControl::SOLID_LINES);
    myFEKit->setLineDetail(FdFEVisControl::FULL);
  }
  else {
    myFEKit->setDrawStyle(FdFEVisControl::SOLID);
    myFEKit->setLineDetail(FdFEVisControl::OFF);
  }

  switch (beam->getModelType())
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

  switch(beam->getMeshType())
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

  myFEKit->show(beam->getModelType() != FmLink::OFF);
  myFEKit->setCoGCSToggle(false);
  myFEKit->setInternalCSToggle(false);

  FdDB::setAutoRedraw(true);

  this->updateSimplifiedViz();
  this->showCS(FmDB::getActiveViewSettings()->visibleBeamCS());

  return true;
}


void FdBeam::updateSimplifiedViz()
{
  FmBeam* beam = (FmBeam*)this->itsFmOwner;
  FmTriad* tr1 = beam->getFirstTriad();
  FmTriad* tr2 = beam->getSecondTriad();

  SoSwitch* csBeamSwitch = SO_GET_PART(itsKit, "beamCSSwitch", SoSwitch);
  csBeamSwitch->removeAllChildren();

  SoSeparator* cgSep = new SoSeparator();
  SoTransform* transform = new SoTransform();
  transform->setMatrix(FdConverter::toSbMatrix(beam->getPositionCG(false)));

  cgSep->addChild(transform);
  cgSep->addChild(FdSymbolDefs::getGlobalSymbolStyle());
  cgSep->addChild(FdSymbolDefs::getSymbol(FdSymbolDefs::COORD_SYST));

  csBeamSwitch->addChild(cgSep);
  csBeamSwitch->whichChild.setValue(SO_SWITCH_ALL);

  SoSwitch* spiderSwitch = SO_GET_PART(itsKit, "spiderSwitch", SoSwitch);
  spiderSwitch->removeAllChildren();

  if (tr1 && tr2) // To avoid crash when erasing model
  {
    SoSeparator* sep = new SoSeparator();
    SoCoordinate3* coords = new SoCoordinate3();
    SoIndexedLineSet* lines = new SoIndexedLineSet();

    spiderSwitch->addChild(sep);
    sep->addChild(coords);
    sep->addChild(FdSymbolDefs::getGlobalSymbolStyle());
    sep->addChild(lines);

    coords->point.set1Value(0, FdConverter::toSbVec3f(tr1->getLocalTranslation(beam)));
    coords->point.set1Value(1, FdConverter::toSbVec3f(tr2->getLocalTranslation(beam)));
    lines->coordIndex.set1Value(0, 0); // first triad
    lines->coordIndex.set1Value(1, 1); // second triad
    lines->coordIndex.set1Value(2,-1); // sep
  }

  if (IAmUsingGenPartVis || beam->getModelType() == FmLink::OFF || !tr1 || !tr2)
    spiderSwitch->whichChild.setValue(SO_SWITCH_NONE);
  else
    spiderSwitch->whichChild.setValue(SO_SWITCH_ALL);
}


void FdBeam::showHighlight()
{
  itsKit->setPart("symbolMaterial",FdSymbolDefs::getHighlightMaterial());

  SoSwitch* csBeamSwitch = SO_GET_PART(itsKit, "beamCSSwitch", SoSwitch);
  csBeamSwitch->whichChild.setValue(SO_SWITCH_ALL);

  myFEKit->highlight(true,FdFEVisControl::OUTLINE);
}


void FdBeam::hideHighlight()
{
  myFEKit->highlight(false);

  // Link coordinate system symbol color :

  this->itsKit->setPart("symbolMaterial",NULL);

  SoMaterial* symbolMaterial = SO_GET_PART(this->itsKit, "symbolMaterial", SoMaterial);
  SbVec3f RGBcolor = FdConverter::toSbVec3f(((FmLink*)this->itsFmOwner)->getRGBColor());

  symbolMaterial->diffuseColor.setValue(RGBcolor);
  symbolMaterial->ambientColor.setValue(RGBcolor);
  symbolMaterial->emissiveColor.setValue(RGBcolor);

  if (!FmDB::getActiveViewSettings()->visibleBeamCS()) {
    SoSwitch* csBeamSwitch = SO_GET_PART(itsKit, "beamCSSwitch", SoSwitch);
    csBeamSwitch->whichChild.setValue(SO_SWITCH_NONE);
  }
}


void FdBeam::showCS(bool doShow)
{
  SoSwitch* csSwitch = SO_GET_PART(itsKit, "beamCSSwitch", SoSwitch);
  csSwitch->whichChild.setValue(doShow || myFEKit->isHighlighted() ? SO_SWITCH_ALL : SO_SWITCH_NONE);
}
