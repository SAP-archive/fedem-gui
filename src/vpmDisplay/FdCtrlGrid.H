// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_CTRL_GRID_H
#define FD_CTRL_GRID_H

class SbVec3f;
class FdCtrlGridKit;


class FdCtrlGrid
{
public:
  static void addGrid();
  static void removeGrid();

  static void setGridMaterial(float r, float g, float b);

  static void setGridSize(float sizeX, float sizeY);
  static float getGridSizeX() { return gridSizeX; }
  static float getGridSizeY() { return gridSizeY; }

  static bool getGridState() { return isGridOn; }
  static void setGridState(bool state);

  static bool getSnapState() { return isSnapOn; }
  static void setSnapState(bool s) { isSnapOn = s; }

  static void setSnapDistance(float X, float Y);
  static float getSnapDistanceX() { return snapDistanceX; }
  static float getSnapDistanceY() { return snapDistanceY; }

  static void snapToNearestPoint(SbVec3f& vec);

private:
  static void drawGrid();

  static FdCtrlGridKit* gridNode;

  static bool isGridOn;

  static float gridWidth;
  static float gridHeight;

  static float gridSizeX;
  static float gridSizeY;

  static bool  isSnapOn;

  static float snapDistanceX;
  static float snapDistanceY;

  static float red;
  static float green;
  static float blue;
};

#endif
