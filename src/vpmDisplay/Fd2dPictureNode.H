// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_2D_PICTURE_NODE_H
#define FD_2D_PICTURE_NODE_H

///////////////////
//
//        This node was made by
//  Morten from Norsk Simulator Service
//           4.Dec.1996
//
/////////////////

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class Fd2dPictureNode : public SoShape
{
  SO_NODE_HEADER(Fd2dPictureNode);

public:
  static void init();

  Fd2dPictureNode();

  // Dummy overloading of write() to avoid any output to file.
  virtual void write(SoWriteAction*) {}

  SoSFVec2f position; //!> Set window screen coordinates
  SoSFVec2f scale;    //!> Scalefactors for logo
  SoSFBool  isOn;     //!> Turn logo gfx on/off

  //! Set the picture to be used. Needs to bee in OGL CS
  void setPixmapData(unsigned char* pixels, int width, int height);
  //! Utility method to flip normal pictures into OGL CS.
  static void flipBuffer(unsigned char* buffer, int width, int height);

protected:
  virtual ~Fd2dPictureNode() {}

  virtual void GLRender(SoGLRenderAction* action);
  virtual SbBool affectsState() const { return FALSE; }
  virtual void computeBBox(SoAction* action, SbBox3f& box, SbVec3f& center);
  virtual void generatePrimitives(SoAction*) {}

private:
  unsigned char* myPixeldata;
  int myPicturewidth;
  int myPictureheight;
};


#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
