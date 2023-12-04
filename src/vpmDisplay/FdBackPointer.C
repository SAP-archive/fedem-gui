// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/actions/SoCallbackAction.h>
#include "vpmDisplay/FdBackPointer.H"

/**********************************************************************
 *
 * Class constructor, destructor and initalizing 
 *
 **********************************************************************/

SO_NODE_SOURCE(FdBackPointer);

void FdBackPointer::init()
{ 
  SO_NODE_INIT_CLASS(FdBackPointer, SoNode, "Node");
}


FdBackPointer::FdBackPointer()
 {
   SO_NODE_CONSTRUCTOR(FdBackPointer);
   structPt = 0;
 }


FdBackPointer::FdBackPointer(FdObject *pt)
{
  SO_NODE_CONSTRUCTOR(FdBackPointer);
  structPt = pt; 
}


FdBackPointer::~FdBackPointer()
{
  
}



/**********************************************************************
 *
 * Other class methods
 *
 **********************************************************************/


FdObject * FdBackPointer::getPointer()
{
  return structPt;
}


void FdBackPointer::setPointer(FdObject * pt)
{
  structPt = pt;
}


void
FdBackPointer::write(SoWriteAction *)//writeAction)
{
  // This is a dummy function made to avoid any output when this node
  // is writing itself to a file.
  //  writeAction;
}








