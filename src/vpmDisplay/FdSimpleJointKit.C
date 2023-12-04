// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdSimpleJointKit.H"
#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdSprDaTransformKit.H"
#include "vpmDisplay/FdBackPointer.H"


SO_KIT_SOURCE(FdSimpleJointKit);


void FdSimpleJointKit::init()
{
  SO_KIT_INIT_CLASS(FdSimpleJointKit, SoBaseKit, "BaseKit");
}


// Constructor

FdSimpleJointKit::FdSimpleJointKit()
{
  SO_KIT_CONSTRUCTOR(FdSimpleJointKit);

  isBuiltIn = true;

  SO_KIT_ADD_CATALOG_ENTRY(joint,  FdTransformKit, true, this, \x0, true);
  SO_KIT_ADD_CATALOG_ENTRY(master, FdTransformKit, true, this, \x0, true);
  SO_KIT_ADD_CATALOG_ENTRY(slave,  FdTransformKit, true, this, \x0, true);
  SO_KIT_ADD_CATALOG_ENTRY(lineM,  FdSprDaTransformKit, true, this, \x0, true);
  SO_KIT_ADD_CATALOG_ENTRY(lineS,  FdSprDaTransformKit, true, this, \x0, true);
  SO_KIT_ADD_CATALOG_ENTRY(backPt, FdBackPointer, true, this, \x0 ,true);

  SO_KIT_INIT_INSTANCE();
}


// Destructor (necessary since inline destructor is too complex)

FdSimpleJointKit::~FdSimpleJointKit()
{
}
