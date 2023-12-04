// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdMultiplyTransforms.H"
#include <Inventor/SbLinear.h>

SO_ENGINE_SOURCE(FdMultiplyTransforms);


void FdMultiplyTransforms::init()
{
  SO_ENGINE_INIT_CLASS(FdMultiplyTransforms, SoEngine, "Engine");
}


FdMultiplyTransforms::FdMultiplyTransforms()
{
  // Do standard constructor stuff
  SO_ENGINE_CONSTRUCTOR(FdMultiplyTransforms);
  
  // Define input field and its default value
   
  SO_ENGINE_ADD_INPUT(trans1, (0,0,0));
  SO_ENGINE_ADD_INPUT(trans2, (0,0,0));
  
  SO_ENGINE_ADD_INPUT(rot1, (0,0,0,0));
  SO_ENGINE_ADD_INPUT(rot2, (0,0,0,0));

  // Define the outputs, specifying their types

  SO_ENGINE_ADD_OUTPUT(translation, SoSFVec3f);
  SO_ENGINE_ADD_OUTPUT(rotation,SoSFRotation );

  rot1.setValue(SbRotation::identity());
}


FdMultiplyTransforms::~FdMultiplyTransforms()
{
}


void FdMultiplyTransforms::evaluate()
{
 
  SbRotation rotRes;
  SbVec3f    transRes;

  SbRotation dummy1;
  SbVec3f    dummy2;

  // Calculate the Transformation:
  
  SbMatrix mx1;
  SbMatrix mx2; 
  SbMatrix mxRes;

  mx1.makeIdentity();
  mx1.setTransform(trans1.getValue(), rot1.getValue(), SbVec3f(1,1,1));
  mx2.setTransform(trans2.getValue(), rot2.getValue(), SbVec3f(1,1,1));

  mxRes = mx2*mx1;
  mxRes.getTransform(transRes, rotRes, dummy2, dummy1);

  // and output to the output fields:
 
  SO_ENGINE_OUTPUT(translation, SoSFVec3f,    setValue(transRes));
  SO_ENGINE_OUTPUT(rotation,    SoSFRotation, setValue(rotRes));
}

