// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_EXTRA_GRAPHICS_H
#define FD_EXTRA_GRAPHICS_H

#include <cstddef> // To ensure NULL is defined
#include <vector>
#include <array>

typedef std::array<float,3> FdColor;

class SoNode;
class SoSeparator;
class SoGroup;
class SbXfBox3f;
class FaVec3;
class FaMat34;
class FFa3DLocation;
class FFaGeometryBase;
class FFaCylinderGeometry;


class FdExtraGraphics
{
public:
  static void  init();
  static void* showBBox(SoNode* rootOfObjectToSurround);
  static void* showBBox(const FaVec3& min, const FaVec3& max, const FaMat34& where);
  static void  removeBBox(void* bBoxId);

  static void showDirection(const FaVec3& from, const FaVec3& direction);
  static void hideDirection();
  static void moveDirection(const FaVec3& newFromPoint);

  static void showLine(const FaVec3& from, const FaVec3& to,
                       const FdColor& color = {1,0,0});
  static void hideLine();

  static void showCS(const FaMat34& globalCS);
  static void hideCS();

  static void showDOFVisualizing(int DOF,
                                 const FaVec3& center, const FaVec3& direction,
                                 SoNode* rootOfObjToSuround = NULL);
  static void hideDOFVisualizing();

  static void show3DLocation(const FaMat34& posRefCS, const FaMat34& rotRefCS, const FFa3DLocation& loc);
  static void hide3DLocation();

  static void showCylinder(const FaMat34& matrix, const std::vector<FaVec3>& points, bool arcOnly = false);
  static void showCylinder(const FFaCylinderGeometry& cylinder, const FaMat34& matrix, bool highlight = false);
  static void hideCylinder();

  static void highlight(const FFaGeometryBase* geo, const FaMat34& m, bool onOff);

private:
  static SoSeparator* makeDOFVisualizing(int DOF,
                                         const FaVec3& center, const FaVec3& direction,
                                         SoNode* rootOfObjToSuround);
  static SoGroup*     makeCornerBoxGraph();
  static SoSeparator* getCornerBoxGraph(SbXfBox3f* bbox);
  static SoSeparator* makeDirectionVisualizing(const FaVec3& from, const FaVec3& direction);
  static SoGroup*     makeArrowGraph();
  static SoSeparator* makeLineVisualizing(const FaVec3& from, const FaVec3& to,
                                          const FdColor& color);
  static SoSeparator* makeCylinderVisualizing(const FFaCylinderGeometry& cylinder, const FaMat34& globalMatrix, bool highlight);

  static SoSeparator* DOFHighlightSep;
  static SoGroup*     cornerBox;
  static SoSeparator* directionSep;
  static SoSeparator* CSSep;
  static SoSeparator* lineSep;
  static SoSeparator* our3DLocationSep;
  static SoSeparator* cylSep;
};

#endif
