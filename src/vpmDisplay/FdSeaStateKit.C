// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoShapeHints.h>

#include "vpmDisplay/FdSeaStateKit.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdAppearanceKit.H"
#include "vpmDisplay/FdSymbolKit.H"

SO_KIT_SOURCE(FdSeaStateKit);


void FdSeaStateKit::init()
{
  SO_KIT_INIT_CLASS(FdSeaStateKit, SoBaseKit, "BaseKit");
}


FdSeaStateKit::FdSeaStateKit()
{
  SO_KIT_CONSTRUCTOR(FdSeaStateKit);

  isBuiltIn = TRUE;

  SO_KIT_ADD_CATALOG_ENTRY(Sep,            SoSeparator ,     FALSE, this,\x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeTransform, SoTransform,      FALSE, Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeSep,       SoSeparator ,     FALSE, Sep, \x0, TRUE);

  SO_KIT_ADD_CATALOG_ENTRY(shapeHint,      SoShapeHints,     FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeSize,      SoScale,          FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeCoords,    SoCoordinate3,    FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeMaterial,  SoMaterial,       FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape,     SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape2,    SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape3,    SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape4,    SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape5,    SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(planeShape6,    SoIndexedFaceSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(frameStyle,     SoDrawStyle,      FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(lineMaterial,   SoMaterial,       FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(lightModel,     SoLightModel,     TRUE,  planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(frameShape,     SoIndexedLineSet, FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(wireSep,        SoSeparator,      FALSE, planeSep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(topPlaneSep,    SoSeparator,      FALSE, planeSep, \x0, TRUE);

  SO_KIT_ADD_CATALOG_ENTRY(csStyle,        SoDrawStyle,      FALSE, Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(csTranslation,  SoTranslation,    FALSE, Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(csAppearance,   FdAppearanceKit,  FALSE, Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(csLightModel,   SoLightModel,     TRUE,  Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(csSymbol,       FdSymbolKit ,     FALSE, Sep, \x0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(backPt,         FdBackPointer ,   FALSE, Sep, \x0, TRUE);

  SO_KIT_INIT_INSTANCE();

  SoLightModel* lm = (SoLightModel*)(this->getPart("lightModel", true));
  if (lm) lm->model.setValue(SoLightModel::PHONG);

  lm = (SoLightModel*)(this->getPart("csLightModel", true));
  if (lm) lm->model.setValue(SoLightModel::PHONG);
}
