// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdLoadDirEngine.H"

SO_ENGINE_SOURCE(FdLoadDirEngine);


void FdLoadDirEngine::init()
{
  SO_ENGINE_INIT_CLASS(FdLoadDirEngine, SoEngine, "Engine");
}


FdLoadDirEngine::FdLoadDirEngine()
{
  // Do standard constructor stuff
  SO_ENGINE_CONSTRUCTOR(FdLoadDirEngine);
  
  // Define input fields and its default values
  SO_ENGINE_ADD_INPUT(attackSpace,  (1,0,0,0,
				     0,1,0,0,
				     0,0,1,0,
				     0,0,0,1));
  SO_ENGINE_ADD_INPUT(attackCoord, (-1,0,0));
  
  SO_ENGINE_ADD_INPUT(firstSpace,  (1,0,0,0,
				    0,1,0,0,
				    0,0,1,0,
				    0,0,0,1));
  SO_ENGINE_ADD_INPUT(firstCoord, (-1,0,0));

  SO_ENGINE_ADD_INPUT(secondSpace, (1,0,0,0,
				    0,1,0,0,
				    0,0,1,0,
				    0,0,0,1));
  SO_ENGINE_ADD_INPUT(secondCoord,(1,0,0));

  // Define the outputs, specifying their types

  SO_ENGINE_ADD_OUTPUT(rotation, SoSFRotation);
  SO_ENGINE_ADD_OUTPUT(translation, SoSFVec3f);

}


FdLoadDirEngine::~FdLoadDirEngine()
{
}


void FdLoadDirEngine::evaluate()
{

  int numMatrixesAttackSpace;
  int numMatrixesFirstSpace;
  int numMatrixesSecondSpace;
  int i;

  SbMatrix attackMatrix;
  SbMatrix firstMatrix;
  SbMatrix secondMatrix;
  
  SbVec3f trans,Vec1,Vec2;
  
  // Figure out how many input values we have

  numMatrixesAttackSpace = attackSpace.getNum();
  numMatrixesFirstSpace  = firstSpace.getNum();
  numMatrixesSecondSpace = secondSpace.getNum();

 
  // Calculate total transformation matrixes:


  attackMatrix.makeIdentity();
  for (i = 0 ; i < numMatrixesAttackSpace; i++)
    {
      attackMatrix = attackSpace[i] * attackMatrix ; 
    }

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

  // Calculate the global coords, and output them
  // to the output field:

  attackMatrix.multVecMatrix(attackCoord.getValue(),trans);
  firstMatrix.multVecMatrix(firstCoord.getValue(),Vec1); 
  secondMatrix.multVecMatrix(secondCoord.getValue(),Vec2);

  Vec1 = Vec2 - Vec1;
  SbRotation rot(SbVec3f(-1,0,0),Vec1);

  SO_ENGINE_OUTPUT(rotation, SoSFRotation,setValue(rot));
  SO_ENGINE_OUTPUT(translation, SoSFVec3f,setValue(trans)); 
}

