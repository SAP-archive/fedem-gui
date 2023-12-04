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
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include "vpmDisplay/FdCtrlGridKit.H"
#include "vpmDisplay/FdAppearanceKit.H"


SO_KIT_SOURCE(FdCtrlGridKit); 


void FdCtrlGridKit::init()
{
   SO_KIT_INIT_CLASS(FdCtrlGridKit, SoBaseKit, "BaseKit");
} 

//    Constructor

FdCtrlGridKit::FdCtrlGridKit()
{
   SO_KIT_CONSTRUCTOR(FdCtrlGridKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_ENTRY(gridSep,   SoSeparator,       TRUE, this,  \x0   ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(appearance, FdAppearanceKit,  TRUE, gridSep, \x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(style,      SoDrawStyle,      TRUE, gridSep, \x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(coords,     SoCoordinate3,    TRUE, gridSep, \x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(lightModel, SoLightModel,    TRUE, gridSep, \x0  ,TRUE );
   SO_KIT_ADD_CATALOG_ENTRY(lines,      SoIndexedLineSet, TRUE, gridSep, \x0  ,TRUE );
 
   SO_KIT_INIT_INSTANCE();

   SoLightModel* lm = (SoLightModel*)(this->getPart("lightModel", true));
   if (lm)
     lm->model.setValue(SoLightModel::BASE_COLOR);
}
 
// Destructor (necessary since inline destructor is too
// complex) 
// Use: public 

FdCtrlGridKit::~FdCtrlGridKit()
{
}
