// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSPRDAPLACER_H
#define FDSPRDAPLACER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFVec3f.h>


// Two separate refrence frames, computes
// the translation rotation and scale
// to place a symbol between the to refrence frames 


#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdSprDaPlacer : public SoEngine 
{
  SO_ENGINE_HEADER(FdSprDaPlacer);
  
public:
  
  // Inputs:
  SoMFMatrix firstSpace;
  SoMFMatrix secondSpace;


  
  // Output:
  SoEngineOutput  translation;       // (SoSFVec3f)
  SoEngineOutput rotation;           //(SoSFRotation)
  SoEngineOutput scaleFactor;        //(SoSFVec3f)
  
  // Initialization
  static void init();
  
  // Constructor
  FdSprDaPlacer();
  
protected:
  // Destructor
  virtual ~FdSprDaPlacer();
  
  // Evaluation method
  virtual void evaluate();
};


#ifdef win32
#include <SoWinEnterScope.h>
#endif


#endif
