// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>
#ifdef USE_SMALLCHANGE
#include <SmallChange/nodes/SmDepthBuffer.h>
#endif
#include "vpmDisplay/FdAppearanceKit.H"

SO_KIT_SOURCE(FdAppearanceKit);

void FdAppearanceKit::init()
{
  SO_KIT_INIT_CLASS(FdAppearanceKit, SoBaseKit, "BaseKit");
}

FdAppearanceKit::FdAppearanceKit()
{
  SO_KIT_CONSTRUCTOR(FdAppearanceKit);

  isBuiltIn = TRUE;

  SO_KIT_ADD_CATALOG_ENTRY(material, SoMaterial , FALSE, this, \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(style   , SoDrawStyle, FALSE, this, \x0 ,TRUE );
#ifdef USE_SMALLCHANGE
  SO_KIT_ADD_CATALOG_ENTRY(depth   , SmDepthBuffer, FALSE, this, \x0 ,TRUE );
#endif
  SO_KIT_INIT_INSTANCE();
}
