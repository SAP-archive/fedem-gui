// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoNormal.h>

#include "vpmDisplay/FdCtrlSymbolKit.H"
#include "vpmDisplay/FdCtrlSymDef.H"

SoMaterial* FdCtrlSymDef::defaultMaterial = NULL;
SoMaterial* FdCtrlSymDef::backMaterial = NULL;
SoMaterial* FdCtrlSymDef::highlightMaterial = NULL;

SoSeparator* FdCtrlSymDef::outPortSymbol = NULL;
SoSeparator* FdCtrlSymDef::inPortSymbol = NULL;


void FdCtrlSymDef::init()
{
  defaultMaterial = new SoMaterial;
  defaultMaterial->ref();
  defaultMaterial->diffuseColor.setValue(0,0,0);
  defaultMaterial->ambientColor.setValue(0,0,0);
  defaultMaterial->specularColor.setValue(0,0,0);
  defaultMaterial->emissiveColor.setValue(0,0,0);

  backMaterial = new SoMaterial;
  backMaterial->ref();
  backMaterial->diffuseColor.setValue(1,1,1);
  backMaterial->ambientColor.setValue(1,1,1);
  backMaterial->specularColor.setValue(1,1,1);
  backMaterial->emissiveColor.setValue(1,1,1);
  backMaterial->transparency.setValue(1);

  highlightMaterial = new SoMaterial;
  highlightMaterial->ref();
  highlightMaterial->diffuseColor.setValue(1,0,0);
  highlightMaterial->ambientColor.setValue(1,0,0);
  highlightMaterial->specularColor.setValue(1,0,0);
  highlightMaterial->emissiveColor.setValue(1,0,0);

  inPortSymbol = FdCtrlSymDef::createPortSymbol(true);
  inPortSymbol->ref();
  outPortSymbol = FdCtrlSymDef::createPortSymbol(false);
  outPortSymbol->ref();
}


// Standard symbol for elements with 3 potrts.

FdCtrlSymbolKit *FdCtrlSymDef::std3pSym()
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[4][3] = { { 0.5,  0.5, 0.0},   //0  Body square
				      { 0.5, -0.5, 0.0},   //1
				      {-0.5, -0.5, 0.0},   //2
				      {-0.5,  0.5, 0.0}}; //15  

  static int32_t lineIndex[5] = {0,1,2,3,0};
  
  return FdCtrlSymDef::createSymbol((float*)CoordsVal,4,
                                    (int32_t*)lineIndex,5,
                                    X,Y,
                                    2,1); 
}

FdCtrlSymbolKit *FdCtrlSymDef::adderSym()
{
  static float CoordsVal[][3] = { {  0.000*0.4, 1.000*0.4, 0.0},  // 0 Body
				    {  0.500*0.4, 0.866*0.4, 0.0},  // 1
				    {  0.866*0.4, 0.500*0.4, 0.0},
				    {  1.000*0.4, 0.000*0.4, 0.0},
				    {  0.866*0.4,-0.500*0.4, 0.0}, 
				    {  0.500*0.4,-0.866*0.4, 0.0}, 
				    {  0.000*0.4,-1.000*0.4, 0.0}, 
				    { -0.500*0.4,-0.866*0.4, 0.0},
				    { -0.866*0.4,-0.500*0.4, 0.0},
				    { -1.000*0.4, 0.000*0.4, 0.0},
				    { -0.866*0.4, 0.500*0.4, 0.0},
				    { -0.500*0.4, 0.866*0.4, 0.0},
				    {  0.000*0.4, 1.000*0.4, 0.0}, // 12

				    { -0.35,  0.33, 0.0}, // 13  Upper
				    { -0.35,  0.47, 0.0}, // 14  plus sign
				    { -0.42,  0.40, 0.0}, // 15 
				    { -0.28,  0.40, 0.0}, // 16 
 				    
				    { -0.35, -0.33, 0.0}, // 17 Lower
				    { -0.35, -0.47, 0.0}, // 18 plus sign
				    { -0.42, -0.40, 0.0}, // 19  
				    { -0.28, -0.40, 0.0}, // 20
 
                                    { -0.5,  0.25,  0.0}, // 21 Touching upper port 
                                    { -0.5, -0.25,  0.0},// 22 Touching lower port 
                                    {  0.5,  0,     0}};

  static int32_t lineIndex[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12, -1,
				   13, 14, -1, 15, 16, -1,
				   17, 18, -1, 19, 20, -1 ,
                                    8, 22, -1, 10, 21, -1, 3,23  };

   return FdCtrlSymDef::createSymbol((float*)CoordsVal,24,
                                     (int32_t*)lineIndex,34,
                                     0.4,0.4,
                                     2,1); 
}

FdCtrlSymbolKit *FdCtrlSymDef::comparatorSym()
{
  static float CoordsVal[][3] = { {  0.000*0.4, 1.000*0.4, 0.0},  // 0 Body
				    {  0.500*0.4, 0.866*0.4, 0.0},  // 1
				    {  0.866*0.4, 0.500*0.4, 0.0},
                                    {  1.000*0.4, 0.000*0.4, 0.0},  // 3
				    {  0.866*0.4,-0.500*0.4, 0.0}, 
				    {  0.500*0.4,-0.866*0.4, 0.0}, 
                                    {  0.000*0.4,-1.000*0.4, 0.0}, // 6
				    { -0.500*0.4,-0.866*0.4, 0.0},
				    { -0.866*0.4,-0.500*0.4, 0.0},
				    { -1.000*0.4, 0.000*0.4, 0.0},
				    { -0.866*0.4, 0.500*0.4, 0.0},
				    { -0.500*0.4, 0.866*0.4, 0.0},
				    {  0.000*0.4, 1.000*0.4, 0.0}, // 12

				    { -0.35,  0.33, 0.0}, // 13  Upper
				    { -0.35,  0.47, 0.0}, // 14  plus sign
				    { -0.42,  0.40, 0.0}, // 15 
				    { -0.28,  0.40, 0.0}, // 16 
				    
				    { -0.42, -0.40, 0.0}, // 17  Lower
				    { -0.28, -0.40, 0.0}, // 18  minus sign
                                      
                                    { -0.5,  0.25,  0.0}, // 19 Touching upper port 
                                    { -0.5, -0.25,  0.0},// 20 Touching lower port 
                                    {  0.5,  0,     0}};
 
  static int32_t lineIndex[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12, -1,
				   13, 14, -1, 15, 16, -1,
				   17, 18, -1 ,
                                    8, 20, -1, 10, 19, -1, 3, 21 };

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,22,
                                    (int32_t*)lineIndex, 31,
                                    0.4,0.4,
                                    2,1); 
}

/*!
  Standard symbol for elements with one in- and one outport.
*/

FdCtrlSymbolKit *FdCtrlSymDef::std2pSym()
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[4][3] = {{ 0.5,  0.5, 0.0},   //0 Body
				   { 0.5, -0.5, 0.0},   //1
				   {-0.5, -0.5, 0.0},   //2
				   {-0.5,  0.5, 0.0}};//10

  static int32_t lineIndex[5] = {0,1,2,3,0};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,4,
                                    (int32_t*)lineIndex,5,
                                    X,Y,
                                    1,1); 
}


FdCtrlSymbolKit * FdCtrlSymDef::createSymbol(const float* coords ,int numCoords,
                                             const int32_t *lineIndex, int numIndex,
                                             float XWidth, float YWidth, 
                                             int nInPorts,int nOutPorts)
{
  FdCtrlSymbolKit *elemBody = new FdCtrlSymbolKit;

  // Set coordinates :
  float * coordRunner = (float*)coords;
  SoCoordinate3 *CSCoord = new SoCoordinate3;
  for (int cn = 0; cn < numCoords; cn++, coordRunner += 3)
    CSCoord->point.set1Value(cn,coordRunner[0],coordRunner[1],coordRunner[2]);
  elemBody->setPart("coords",CSCoord);

  // Make shape Set indexes   

  SoIndexedLineSet *line = new SoIndexedLineSet;
  line->coordIndex.setValues(0,numIndex,lineIndex);
  elemBody->setPart("line", line);
   
  // Define the square's spatial coordinates

  SoCoordinate3 *fCoord = new SoCoordinate3;
  fCoord->point.set1Value(0, SbVec3f( XWidth,  YWidth, -0.1));
  fCoord->point.set1Value(1, SbVec3f( XWidth, -YWidth, -0.1));
  fCoord->point.set1Value(2, SbVec3f(-XWidth, -YWidth, -0.1));
  fCoord->point.set1Value(3, SbVec3f(-XWidth,  YWidth, -0.1));
  elemBody->setPart("faceCoord", fCoord);
  
  // Define a FaceSet

  SoFaceSet *faceSet = new SoFaceSet;
  faceSet->numVertices.set1Value(0, 4);
  elemBody->setPart("elemFaceSet",faceSet);
  elemBody->setPart("faceMaterial",backMaterial);
  
  float verticalportSpacing = 0.25;
  int numPortsPerSide = (nInPorts/2);

  float transform = verticalportSpacing*numPortsPerSide;
  SoSeparator * sep =  SO_GET_PART(elemBody,"inPortSep",SoSeparator);

  int i;
  for ( i = 0; i < nInPorts; i++)
    {
      SoTransform * xf = new SoTransform;
      xf->translation.setValue(SbVec3f(0,transform,0));
      transform = -((nInPorts == 2) ? verticalportSpacing*2 : verticalportSpacing);
      sep->addChild(xf);
      sep->addChild(FdCtrlSymDef::inPortSymbol);
    }

  numPortsPerSide = ((nOutPorts -1)/2);
  transform = verticalportSpacing*numPortsPerSide;
 
  sep =  SO_GET_PART(elemBody,"outPortSep",SoSeparator);

  for ( i = 0; i < nOutPorts; i++)
    {
      SoTransform * xf = new SoTransform;
      xf->translation.setValue(SbVec3f(0,transform,0));
      transform = -((nOutPorts==2) ? verticalportSpacing*2 : verticalportSpacing);
      sep->addChild(xf);
      sep->addChild(FdCtrlSymDef::outPortSymbol);
    }
  
  return elemBody;  
}


SoSeparator* FdCtrlSymDef::createPortSymbol(bool inPort)
{
  static float CoordsInp[5][3] = {{-0.5 ,  0.0,  0.0}, //0 inport
				  {-0.75 , 0.0,  0.0}, //1
				  {-0.675, 0.075,0.0}, //2
				  {-0.675,-0.075,0.0}, //3
				  {-0.6  , 0.0,  0.0}};//4

  static float CoordsOut[5][3] = {{ 0.5 , 0.0,  0.0}, //0 outport
                                  { 0.75, 0.0,  0.0}, //1
				  { 0.6 , 0.05, 0.0}, //2
				  { 0.6 ,-0.05, 0.0}, //3
				  { 0.65, 0.0,  0.0}};//4

  static int32_t lineIndex[6] = {0,4,3,1,2,4};

  SoSeparator* port = new SoSeparator;

  // Set coordinates
  SoCoordinate3* CSCoord = new SoCoordinate3;
  CSCoord->point.setValues(0,5, inPort ? CoordsInp : CoordsOut);
  port->addChild(CSCoord);

  // Make shape set indices
  SoIndexedLineSet* line = new SoIndexedLineSet;
  line->coordIndex.setValues(0,6,lineIndex);
  port->addChild(line);

  return port;
}


/*!
 ***********************************************************************
 *   Output symbol with one in-port.
 ***********************************************************************
 */
  

FdCtrlSymbolKit *FdCtrlSymDef::outputSym()	
{
  static float X = 0.5;
  static float Y = 0.5;




  static float CoordsVal[16][3] = {{ -.5,     .375,    0.},      //0 Body
				   { 0.0,     .375,    0.},      //1  
				   {.1,       0.35,    0.},      //2
				   {.175,     0.3,     0.},      //3
				   {.225,     0.2,     0.},      //4
				   {.25,      0.1,     0.},      //5
				   {.25,      0.,      0.},      //6
				   {.25,     -0.1,     0.},      //7
				   {.225,    -0.2,     0.},      //8
				   {.175,    -0.3,     0.},      //9
				   {.1,      -0.35,    0.},      //10
				   { 0.0,    -.375,    0.},      //11  
				   {-.5,     -.375,    0.},      //12

				   {.0,    .125,    0.},   //13
				   {.0,   -.125,    0.},   //14
				   {.125,  0.,      0.}};  //15



  static int32_t lineIndex[19] = {0,1,2,3,4,5,6,7,8,9,10,11,12,0,-1,
				 13,14,15,13};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,16,
                                    (int32_t*)lineIndex,19,
                                    X,Y,
                                    1,0); 
}


/*!
 ***********************************************************************
 *   Input symbol with one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::inputSym()	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[16][3] = {{ -.25,    0.,     0.},      //0 Box Body
				   { -.25,   .1,      0.},      //1  
				   { -.225,  .2,      0.},      //2  
				   { -.175,  .3,      0.},      //3  
				   { -.1,    .35,     0.},      //4  
				   { 0.0,    .375,    0.},      //5
				   {.5,      .375,    0.},      //6
				   {.5,     -.375,    0.},      //7 
				   {0.0,    -.375,    0.},      //8
				   { -.1,   -.35,     0.},      //9  
				   { -.175, -.3,      0.},      //10  
				   { -.225, -.2,      0.},      //11  
				   { -.25,  -.1,      0.},      //12  

				   {0.125, 0.,       0.},   //13
				   {.0,    .125,     0.},   //14
				   {.0,   -.125,    0.}};   //15



  static int32_t lineIndex[19] = {0,1,2,3,4,5,6,7,8,9,10,11,12,0,-1,
				 13,14,15,13};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,16,
                                    (int32_t*)lineIndex,19,
                                    X,Y,
                                    0,1); 
}




/*!
 ***********************************************************************
 * Dead Zone symbol with one in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::deadZoneSym()	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[12][3] = {{ 0.5,   0.5, 0.0},     //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3

				   {-.375,   0.,      0.},   //4 Cross
				   {.375,    0.,      0.},   //5
				   {0.,     -.375,    0.},   //6
				   {0.,      .375,    0.},   //7

				   {-.375,  -.375,    0.},   //8 Symbol
				   {-.125,    0.,     0.},   //9
				   { .125,    0.,     0.},   //10
				   {.375,    .375,    0.}};   //11


  static int32_t lineIndex[16] = {0,1,2,3,0,-1,
				 4,5,-1,
				 6,7,-1,
				 8,9,10,11};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,12,
                                    (int32_t*)lineIndex,16,
                                    X,Y,
                                    1,1); 
}


/*
 ***********************************************************************
 * Amplifier/Gain symbol with one in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::amplifierSym()
{
  static float CoordsVal[3][3] = {  {  -.5,  -.5,     0.},  	// 0 Body
				    {  -.5,   .5 ,    0.},  	// 1  
				    {  .5,     0.,     0.}   };  //2
 
  static int32_t lineIndex[4] = { 0,1,2,0 };

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,3,
                                    (int32_t*)lineIndex, 4,
                                    0.5,0.5,
                                    1,1); 
}


/*!
 ***********************************************************************
 *   Sample & Hold symbol with one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::sampleHoldSym()	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[18][3] = {{ 0.5,  0.5, 0.0},      //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3

				   {-.5,     .0,     0.},   //4 Symbol
				   {-.25,    .0,     0.},   //5

				   {-.25,    .125,     0.},   //6
				   {-.25,   -.125,     0.},   //7

				   {-.125,   .125,     0.},   //8
				   {-.125,  -.125,     0.},   //9

				   { .0,     .0,       0.},  //10
				   { .125,   .0,       0.},  //11

				   { .25,    .0,       0.},  //12
				   { .375,   .0,       0.},  //13

				   { .0,    .375,     0.},  //14
				   { .2,    .375,     0.},  //15
				   { .1,    .125,       0.},  //16
				   { .1,    .375,     0.}}; //17


  static int32_t lineIndex[26] = {0,1,2,3,0,-1,
				 4,5,-1,
				 6,7,-1,
				 8,9,-1,
				 10,11,-1,
				 12,13,-1,
				 14,15,-1,
				 16,17};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,18,
                                    (int32_t*)lineIndex,26,
                                    X,Y,
                                    1,1); 
}




/*!
 ***********************************************************************
 *   LimDerivator symbol with one in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::limDerivatorSym()	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[22][3] = {{ 0.5,  0.5, 0.0},      //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3

				   {-.375,   .0,     0.},   //4 Symbol
				   { .375,   .0,     0.},   //5

				   {-.375,   .125,     0.},   //6
				   {-.125,   .125,     0.},   //7
				   {-.25,    .375,     0.},   //8

				   { .0,     .375,    0.},   //9
				   { .0,     .185,    0.},  //10
				   { .06,    .125,    0.},  //11
				   { .19,    .125,    0.},  //12
				   { .25,    .185,    0.},  //13
				   { .25,    .375,    0.},  //14

				   {-.375,  -.375,     0.},  //15
				   {-.125,  -.375,     0.},  //16
				   {-.25,   -.125,     0.},  //17

				   { .03,   -.2,      0.},  //18
				   { .22,   -.2,      0.},  //19
				   { .125,  -.375,    0.},  //20
				   { .125,  -.125,    0.}}; //21


  static int32_t lineIndex[31] = {0,1,2,3,0,-1,
				 4,5,-1,
				 6,7,8,6,-1,
				 9,10,11,12,13,14,-1,
				 15,16,17,15,-1,
				 18,19,-1,
				 20,21};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,22,
                                    (int32_t*)lineIndex,31,
                                    X,Y,
                                    1,1); 
}


/*!
 ***********************************************************************
 *   Logical Switch symbol with one in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::logicalSwitchSym()	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[19][3] = {{ 0.5,  0.5, 0.0},      //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3

				   {-.5,      .375,   0.},   //4 Symbol
				   {-.125,    .375,   0.},   //5
				   {.25,     0.,      0.},   //6
				   {.5,      0.,      0.},   //7

				   {-.5,     .0,      0.},   //8
				   {-.25,    .0,      0.},   //9

				   {-.25,   -.125,      0.},  //10
				   {-.25,    .125,      0.},  //11

				   {-.5,    -.375,      0.},  //12
				   {-.125,  -.375,      0.},  //13

				   {0.0,     .0,      0.},   //14
				   {0.0,     .06,     0.},   //15
				   {0.02,    .125,    0.},   //16
				   {0.065,   .19,     0.},   //17
				   {0.125,   .25,     0.}};  //18



  static int32_t lineIndex[25] = {0,1,2,3,0,-1,
				 4,5,6,7,-1,
				 8,9,-1,
				 10,11,-1,
				 12,13,-1,
				 14,15,16,17,18};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,19,
                                    (int32_t*)lineIndex,25,
                                    X,Y,
                                    1,1); 
}


/*!
 ***********************************************************************
 * Hysteresis (Backlash) symbol with one in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::hysteresisSym()	// Backlash	
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[14][3] = {{ 0.5,  0.5, 0.0},      //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3

				   {-.375,   0.,      0.},   //4 Cross
				   {.375,    0.,      0.},   //5
				   {0.,     -.375,    0.},   //6
				   {0.,      .375,    0.},   //7

				   {-.375,  -.375,    0.},   //8 Symbol
				   {-.125,    .25,    0.},   //9
				   {.31,      .25,    0.},   //10

				   {-.31,   -.25,     0.},   //11
				   {.125,   -.25,     0.},   //12
				   {.375,    .375,    0.}};   //13


  static int32_t lineIndex[19] = {0,1,2,3,0,-1,
				 4,5,-1,
				 6,7,-1,
				 8,9,10,-1,
				 11,12,13};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,14,
                                    (int32_t*)lineIndex,19,
                                    X,Y,
                                    1,1); 
}

/*!
 ***********************************************************************
 * Multiplier symbol with two in- and one outport.
 ***********************************************************************
 */

FdCtrlSymbolKit *FdCtrlSymDef::multiplierSym()
{
  static float CoordsVal[24][3] = { {  0.000*0.4, 1.000*0.4, 0.0},  // 0 Body
				    {  0.500*0.4, 0.866*0.4, 0.0},  // 1
				    {  0.866*0.4, 0.500*0.4, 0.0},
				    {  1.000*0.4, 0.000*0.4, 0.0},
				    {  0.866*0.4,-0.500*0.4, 0.0}, 
				    {  0.500*0.4,-0.866*0.4, 0.0}, 
				    {  0.000*0.4,-1.000*0.4, 0.0}, 
				    { -0.500*0.4,-0.866*0.4, 0.0},
				    { -0.866*0.4,-0.500*0.4, 0.0},
				    { -1.000*0.4, 0.000*0.4, 0.0},
				    { -0.866*0.4, 0.500*0.4, 0.0},
				    { -0.500*0.4, 0.866*0.4, 0.0},
				    {  0.000*0.4, 1.000*0.4, 0.0}, // 12
 
                                    { -0.125,  0.125,  0.0}, // 13  
                                    { -0.125,  0.0,    0.0}, // 14  
                                    { -0.125, -0.125,  0.0}, // 15  

                                    {  0.0,   0.125,   0.0}, // 16  
                                    {  0.0,  -0.125,   0.0}, // 17  

                                    {  0.125,  0.125,  0.0}, // 18  
                                    {  0.125,  0.0,    0.0}, // 19  
                                    {  0.125, -0.125,  0.0}, // 20  

                                    { -0.5,  0.25,  0.0}, // 21 Touching upper port 
                                    { -0.5, -0.25,  0.0}, // 22 Touching lower port 
                                    {  0.5,  0,     0}};  // 23

  static int32_t lineIndex[34] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,-1,
				    13,20,-1,
				    14,19,-1,
				    15,18,-1,
				    16,17,-1,
                                    8, 22, -1, 10, 21, -1, 3,23  };

   return FdCtrlSymDef::createSymbol((float*)CoordsVal,24,
                                     (int32_t*)lineIndex,34,
                                     0.4,0.4,
                                     2,1); 
}


/*
 ***********************************************************************
 * Limitation (Saturation) symbol with one in- and one outport.
 ***********************************************************************
 */
  

FdCtrlSymbolKit *FdCtrlSymDef::limitationSym()	// Saturation
{
  static float X = 0.5;
  static float Y = 0.5;

  static float CoordsVal[12][3] = {{ 0.5,  0.5, 0.0},      //0 Box Body
				   { 0.5, -0.5, 0.0},      //1  
				   {-0.5, -0.5, 0.0},      //2
				   {-0.5,  0.5, 0.0},      //3
				   {-.375,   0.,      0.},   //4 Symbol
				   {.375,    0.,      0.},   //5
				   {0.,     -.375,    0.},   //6
				   {0.,      .375,    0.},   //7
				   {-.375,  -.25,     0.},   //8
				   {-.125,  -.25,     0.},   //9
				   {.125,    .25,     0.},   //10
				   {.375,    .25,     0.}};   //11
  static int32_t lineIndex[16] = {0,1,2,3,0,-1,
				 4,5,-1,
				 6,7,-1,
				 8,9,10,11};

  return FdCtrlSymDef::createSymbol((float*)CoordsVal,12,
                                    (int32_t*)lineIndex,16,
                                    X,Y,
                                    1,1); 
}
