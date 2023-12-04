// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdSprDaPlacer.H"
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

SO_ENGINE_SOURCE(FdSprDaPlacer);


void FdSprDaPlacer::init()
{
  SO_ENGINE_INIT_CLASS(FdSprDaPlacer, SoEngine, "Engine");
}


FdSprDaPlacer::FdSprDaPlacer()
{
  // Do standard constructor stuff
  SO_ENGINE_CONSTRUCTOR(FdSprDaPlacer);
  
  // Define input field and its default value
   
  SO_ENGINE_ADD_INPUT(firstSpace,  (1,0,0,0,
				    0,1,0,0,
				    0,0,1,0,
				    0,0,0,1));
 
  SO_ENGINE_ADD_INPUT(secondSpace, (1,0,0,0,
				    0,1,0,0,
				    0,0,1,0,
				    0,0,0,1));
 

  // Define the outputs, specifying their types

  SO_ENGINE_ADD_OUTPUT(translation, SoSFVec3f);
  SO_ENGINE_ADD_OUTPUT(rotation,SoSFRotation );
  SO_ENGINE_ADD_OUTPUT(scaleFactor, SoSFVec3f);
}


FdSprDaPlacer::~FdSprDaPlacer()
{
}


void FdSprDaPlacer::evaluate()
{
  SbRotation symbolRotation = SbRotation::identity();
 
  int numMatrixesFirstSpace;
  int numMatrixesSecondSpace;
  int i;

  SbMatrix firstMatrix;
  SbMatrix secondMatrix;
  
  SbVec3f firstPoint;
  SbVec3f secondPoint;
  SbVec3f symbolDirection;
  
  float length;
  // Figure out how many input values we have

  numMatrixesFirstSpace  = firstSpace.getNum();
  numMatrixesSecondSpace = secondSpace.getNum();

  // Calculate total transformation matrixes:
  
  firstMatrix.makeIdentity();
  for (i = 0 ; i < numMatrixesFirstSpace; i++)
    {
      firstMatrix = firstSpace[i] * firstMatrix ; 
    }

  secondMatrix.makeIdentity();
  for (i = 0 ; i < numMatrixesSecondSpace; i++)
    {
      secondMatrix = secondSpace[i] * secondMatrix; 
    }

  // Get translation part of matrixes:

  firstPoint.setValue(firstMatrix[3][0],firstMatrix[3][1],firstMatrix[3][2]);
  secondPoint.setValue(secondMatrix[3][0],secondMatrix[3][1],secondMatrix[3][2]);

  // Compute std::vector for symbol
  symbolDirection = secondPoint - firstPoint;
  length = symbolDirection.length();
  if(length)
    {
      // Compute rotation for symbol
      symbolRotation = SbRotation(SbVec3f(1,0,0),symbolDirection);
    }
  else
    {
      // Length is zero 
      length = 1.0e-7f; 
    }
  // Calculate the Transformtion, and output it to the output fields:

  SO_ENGINE_OUTPUT(translation, SoSFVec3f,setValue(firstPoint));
  SO_ENGINE_OUTPUT(rotation,SoSFRotation,setValue(symbolRotation));
  SO_ENGINE_OUTPUT(scaleFactor, SoSFVec3f,setValue(length,1,1));
}
