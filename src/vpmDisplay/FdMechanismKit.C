// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdMechanismKit.H"
#include "vpmDisplay/FdTriadSwKit.H"
#include "vpmDisplay/FdLinJointKit.H"
#include "vpmDisplay/FdSimpleJointKit.H"
#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdSprDaTransformKit.H"
#include "vpmDisplay/FdLoadTransformKit.H"
#include "vpmDisplay/FdRefPlaneKit.H"
#include "vpmDisplay/FdSeaStateKit.H"
#include "vpmDisplay/FdCamJointKit.H"
#include "vpmDisplay/FdFEModelKit.H"
#include "vpmDisplay/FdStrainRosetteKit.H"
#include "vpmDisplay/FdPipeSurfaceKit.H"

#include <Inventor/nodes/SoSwitch.h>


SO_KIT_SOURCE(FdMechanismKit);


void FdMechanismKit::init()
{
  SO_KIT_INIT_CLASS(FdMechanismKit, SoBaseKit, "BaseKit");
}


// Constructor

FdMechanismKit::FdMechanismKit()
{
  SO_KIT_CONSTRUCTOR(FdMechanismKit);

  isBuiltIn = true;

  SO_KIT_ADD_CATALOG_LIST_ENTRY(refPlaneListSw, SoSwitch, true, this, \x0, FdRefPlaneKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(seaStateListSw, SoSwitch, true, this, \x0, FdSeaStateKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(triadListSw,    SoSwitch, true, this, \x0, FdTriadSwKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(simpleJointListSw, SoSwitch, true, this, \x0, FdSimpleJointKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(linJointListSw,    SoSwitch, true, this, \x0, FdLinJointKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(camJointListSw,    SoSwitch, true, this, \x0, FdCamJointKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(pipeSurfaceListSw, SoSwitch, true, this, \x0, FdPipeSurfaceKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(sprDaListSw, SoSwitch, true, this, \x0, FdSprDaTransformKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(loadListSw,   SoSwitch, true, this, \x0, FdLoadTransformKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(HPListSw, SoSwitch, true, this, \x0, FdSprDaTransformKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(sensorListSw, SoSwitch, true, this, \x0, FdSprDaTransformKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(stickerListSw, SoSwitch, true, this, \x0, FdTransformKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(rosetteListSw, SoSwitch, true, this, \x0, FdStrainRosetteKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(tireListSw, SoSwitch, true, this, \x0, FdFEModelKit, true);

  SO_KIT_ADD_CATALOG_LIST_ENTRY(partListSw, SoSwitch, true, this, \x0, FdFEModelKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(beamListSw, SoSwitch, true, this, \x0, FdFEModelKit, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(uelmListSw, SoSwitch, true, this, \x0, FdFEModelKit, true);

  SO_KIT_INIT_INSTANCE();

  SO_GET_PART(this,"pipeSurfaceListSw",SoNodeKitListPart)->containerSet("whichChild -3");
}


// Destructor (necessary since inline destructor is too complex)

FdMechanismKit::~FdMechanismKit()
{
}
