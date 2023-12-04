// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDLOADDIRENGINE_H
#define FDLOADDIRENGINE_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

// This engine takes two separate points given
// in two separate refrence frames, computes
// the global rotation that correspond to the direction
// between the points.


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class  FdLoadDirEngine : public SoEngine 
{
  SO_ENGINE_HEADER(FdLoadDirEngine);
  
public:
  
  // Inputs:

  SoMFMatrix attackSpace;
  SoSFVec3f  attackCoord;
  SoMFMatrix firstSpace;
  SoSFVec3f  firstCoord;
  SoMFMatrix secondSpace;
  SoSFVec3f  secondCoord;

  
  // Output:
  SoEngineOutput  translation;    // (SoSFVec3f)
  SoEngineOutput  rotation;       // (SoSFRotation)

  
  // Initialization
  static void init();
  
  // Constructor
  FdLoadDirEngine();
  
protected:
  // Destructor
  virtual ~FdLoadDirEngine();
  
  // Evaluation method
  virtual void evaluate();
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
