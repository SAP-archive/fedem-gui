// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*****************************************************************
 * CLASS: FdBackPointer
 * AUTHOR: Jens LIEN
 * LAST MODIFIED: 16 nov 1995
 *
 * DESCRIPTION: Open Inventor node with pointer to an instance of 
 * FdObject or inherited classes.
 *****************************************************************/

#ifndef FDBACKPOINTER_H
#define FDBACKPOINTER_H

#include <Inventor/nodes/SoSubNode.h>

class FdObject;

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdBackPointer : public SoNode
{
  SO_NODE_HEADER(FdBackPointer);

public:
  static void init();

  FdBackPointer();
  FdBackPointer(FdObject*);

  FdObject* getPointer();
  void setPointer(FdObject*);

  // Dummy overloading of write() to avoid any output to file
  virtual void write(SoWriteAction* writeAction);

private:
  virtual ~FdBackPointer();

  FdObject* structPt;
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
