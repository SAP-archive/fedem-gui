// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDMULTIPLYTRANSFORMS_H
#define FDMULTIPLYTRANSFORMS_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

// Two separate refrence frames, computes
// the translation rotation and scale
// to place a symbol between the to refrence frames 

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdMultiplyTransforms : public SoEngine 
{
  SO_ENGINE_HEADER(FdMultiplyTransforms);
public:
  // Inputs:

  SoSFVec3f trans1;
  SoSFRotation rot1;
  SoSFVec3f trans2;
  SoSFRotation rot2;
  
  // Output:

  SoEngineOutput translation;       // (SoSFVec3f)
  SoEngineOutput rotation;           //(SoSFRotation)
  
  // Initialization

  static void init();
  
  // Constructor

  FdMultiplyTransforms();
  
protected:
  // Destructor

  virtual ~FdMultiplyTransforms();
  
  // Evaluation method

  virtual void evaluate();
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif
