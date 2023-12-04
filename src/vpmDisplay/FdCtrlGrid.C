// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdCtrlGrid.H"
#include "vpmDisplay/FdCtrlGridKit.H"
#include "vpmDisplay/FdCtrlDB.H"

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <cmath>


//Grid variables
FdCtrlGridKit* FdCtrlGrid::gridNode = NULL;

float FdCtrlGrid::gridWidth  = 100.0f;
float FdCtrlGrid::gridHeight = 100.0f; //Grid area

bool  FdCtrlGrid::isGridOn  = false;
float FdCtrlGrid::gridSizeX = 1.0f; //Square size
float FdCtrlGrid::gridSizeY = 1.0f;

//Snap variables
bool  FdCtrlGrid::isSnapOn      = false;
float FdCtrlGrid::snapDistanceX = 0.25f; // Note! Make sure default values
float FdCtrlGrid::snapDistanceY = 0.25f; // divide equally to gridSize

//Grid color
float FdCtrlGrid::red   = 0.5f;
float FdCtrlGrid::green = 0.5f;
float FdCtrlGrid::blue  = 0.5f;


/////////////////////////////
//   Grid
////////////////////////////

void FdCtrlGrid::addGrid() //Adds a gridnode to the scengraph
{
  if (isGridOn)
    removeGrid();

  gridNode = new FdCtrlGridKit;
  gridNode->ref();

  FdCtrlDB::getCtrlExtraGraphicsRoot()->addChild(gridNode);

  drawGrid();

  isGridOn = true;
}

void FdCtrlGrid::removeGrid() //Remove the gridnode to the scengraph
{
  if (isGridOn)
    FdCtrlDB::getCtrlExtraGraphicsRoot()->removeChild(gridNode);

  isGridOn = false;
}

void FdCtrlGrid::setGridMaterial(float r, float g, float b)
{
  red   = fabsf(r) < 1.0f ? fabsf(r) : 1.0f;
  green = fabsf(g) < 1.0f ? fabsf(g) : 1.0f;
  blue  = fabsf(b) < 1.0f ? fabsf(b) : 1.0f;
}

//Means the size off one square in the grid.
void FdCtrlGrid::setGridSize(float sizeX, float sizeY)
{
  gridSizeX = fabsf(sizeX);
  gridSizeY = fabsf(sizeY);

  if (isGridOn)
    addGrid();
}

void FdCtrlGrid::setGridState(bool state)
{
  if (state)
    addGrid();
  else
    removeGrid();
}

void FdCtrlGrid::drawGrid()
{
  // Calculate number of rows and columns, that make the middle of
  // the grid equal with the midpoint of the scene

  int numX = (int)(gridWidth/gridSizeX) + 1;
  int numY = (int)(gridHeight/gridSizeY)+ 1;
  float sizeX = numX * gridSizeX; //Adjusted grid width
  float sizeY = numY * gridSizeY; //Adjusted grid higth

  int i, j, k, l = 0;

  SoMaterial *mat = SO_GET_PART(gridNode,"appearance.material", SoMaterial);
  mat->diffuseColor.setValue( red, green, blue);
  mat->ambientColor.setValue( red, green, blue);
  mat->specularColor.setValue(red, green, blue);

  SoDrawStyle *style = SO_GET_PART(gridNode,"appearance.style", SoDrawStyle);
  style->style.setValue(SoDrawStyle::LINES);
  style->lineWidth.setValue(1);
  style->linePattern.setValue(0xf0f0);
  
  SoCoordinate3 *coord = SO_GET_PART(gridNode,"coords", SoCoordinate3);
  SoIndexedLineSet *line = SO_GET_PART(gridNode,"lines", SoIndexedLineSet);

  const float z = 0.0f; // The grid lies in the (z=0)-plane

  //Draw the horisontal lines in the grid
  float coordX = sizeX;
  float coordY = sizeY;
  
  for(i = 0;i < (numY) ;i++)
    {
      j = 4*i;
      
      int32_t index[5] = {j,j+1,j+2,j+3,-1};
      
      coord->point.set1Value(j,   -coordX,  coordY, z);
      coord->point.set1Value(j+1,  coordX,  coordY, z);
      coordY -= gridSizeY;
      coord->point.set1Value(j+2,  coordX,  coordY, z);
      coord->point.set1Value(j+3, -coordX,  coordY, z);
      coordY -= gridSizeY;
      
      line->coordIndex.setValues(j, 5, index);
    }
  
  //Draw the vertical lines in the grid
  coordX = sizeX;
  coordY = sizeY;
  
  for(k = i; k < (numX+i+1); k++)
    {
      l = 4*k;
      
      int32_t index[5] = {l, l+1, l+2, l+3, -1};
      
      coord->point.set1Value(l,   -coordX, -coordY, z);
      coord->point.set1Value(l+1, -coordX,  coordY, z);
      coordX -= gridSizeX;
      coord->point.set1Value(l+2, -coordX,  coordY, z);
      coord->point.set1Value(l+3, -coordX, -coordY, z);
      coordX -= gridSizeX;
      
      line->coordIndex.setValues(l, 5, index);
    }
  
  //Frame around the grid.
  int32_t index[6] = {l+4, l+5, l+6, l+7, l+8, -1};
  
  coord->point.set1Value(l+4,  sizeX, -sizeY, z);
  coord->point.set1Value(l+5,  sizeX,  sizeY, z);
  coord->point.set1Value(l+6, -sizeX,  sizeY, z);
  coord->point.set1Value(l+7, -sizeX, -sizeY, z);
  coord->point.set1Value(l+8,  sizeX, -sizeY, z);
  
  line->coordIndex.setValues(l, 6, index);
}


//////////////////
//   Snap
/////////////////

void FdCtrlGrid::setSnapDistance(float X, float Y)
{
  if (X == 0) X = 0.1f;
  if (Y == 0) Y = 0.1f;

  float numX = fabsf(gridSizeX/X);
  float numY = fabsf(gridSizeY/Y);

  //Adjusts the snapdistance so it relate to the grid size.
  if(numX >= 1)
    {  
      numX = floor(numX);
      snapDistanceX = gridSizeX/numX; 
    }

  else if(numX < 1)
    { 
      numX = 1/numX;
      int numGridX = (int)floor(numX);
      numX -= numGridX;

      if(numX != 0)
	{
	  numX = 1/numX; 
	  numX = floor(numX);
	  snapDistanceX = gridSizeX * (numGridX+ 1/numX);       
	}
      else
	{
	  snapDistanceX = gridSizeX * numGridX;
	}
    }


  if(numY >= 1)
    {
      numY = floor(numY);
      snapDistanceY = gridSizeY/numY;
    }
  else if(numY < 1)
    {
      numY = 1/numY;
      int numGridY = (int)floor(numY);
      numY -= numGridY;

      if(numY != 0)
	{
	  numY = 1/numY; 
	  numY = floor(numY);
	  snapDistanceY = gridSizeY * (numGridY + 1/numY);       
	}
      else
	{
	  snapDistanceY = gridSizeY * numGridY;
	}
    }
}


void FdCtrlGrid::snapToNearestPoint(SbVec3f& vec)
{
  if (!isSnapOn) return;

  int nX = (vec[0] > 0.0f ? 0.5f : -0.5f)*snapDistanceX + vec[0]/snapDistanceX;
  int nY = (vec[1] > 0.0f ? 0.5f : -0.5f)*snapDistanceY + vec[1]/snapDistanceY;
  vec[0] = nX * snapDistanceX;
  vec[1] = nY * snapDistanceY;
}
