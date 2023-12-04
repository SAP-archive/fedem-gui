// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_AXIS_CROSS_H
#define FD_AXIS_CROSS_H

///////////////////
//
//        This node was made by
//  Morten Eriksen from Systems in Motion, <mortene@sim.no>
//           1997/2001
//
/////////////////

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/SbBox3f.h>
#include <Inventor/SbVec3f.h>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdAxisCross : public SoShape
{
  SO_NODE_HEADER(FdAxisCross);

public:
  enum {UPPERLEFT = 1, LOWERLEFT, UPPERRIGHT, LOWERRIGHT};

  static void init();

  FdAxisCross();

  // Dummy overloading of write() to avoid any output to file.
  virtual void write(SoWriteAction*) {}

  // Turn cross or gravity indicator on/off.
  SoSFBool isCrossOn;
  SoSFBool isGravityOn;
  // This is the direction of the gravity vector.
  SoSFVec3f gravityVector;
  // Width/height of pixel area allocated to the cross.
  SoSFUShort pixelArea;
  // Decides which corner of the window the cross is drawn to.
  SoSFEnum corner;
  // Set color values.
  SoSFColor crossColor;
  SoSFColor gravityColor;
  SoSFColor textColor;

protected:
  virtual ~FdAxisCross() {}

  virtual void GLRender(SoGLRenderAction* action);
  virtual void computeBBox(SoAction* action, SbBox3f& box, SbVec3f& center);
  virtual void generatePrimitives(SoAction* action);
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
