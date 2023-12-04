// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>

#include "vpmDisplay/FdCtrlElemKit.H"
#include "vpmDisplay/FdCtrlLineKit.H"
#include "vpmDisplay/FdCtrlKit.H"

SO_KIT_SOURCE(FdCtrlKit);

void FdCtrlKit::init()
{
   SO_KIT_INIT_CLASS(FdCtrlKit, SoBaseKit, "BaseKit");
} 


FdCtrlKit::FdCtrlKit()
{
   SO_KIT_CONSTRUCTOR(FdCtrlKit); 
   isBuiltIn = TRUE;

   SO_KIT_ADD_CATALOG_LIST_ENTRY(elemList, SoSeparator, TRUE,
				 this, \x0 ,FdCtrlElemKit, TRUE );
   
   SO_KIT_ADD_CATALOG_LIST_ENTRY(lineList, SoSeparator, TRUE,
   				 this, \x0 ,FdCtrlLineKit, TRUE );

  

   SO_KIT_INIT_INSTANCE();
}
 


FdCtrlKit::~FdCtrlKit()
{
}
