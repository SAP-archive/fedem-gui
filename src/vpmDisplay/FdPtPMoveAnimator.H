// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_PTP_MOVE_ANIMATOR_H
#define FD_PTP_MOVE_ANIMATOR_H

#include <Inventor/SbVec3f.h>
#include <Inventor/SbRotation.h>
#include <Inventor/SbTime.h>

class FdObject;
class SoTransform;
class SoTimerSensor;
class SoSensor;
class SbMatrix;


class FdPtPMoveAnimator
{
public:
  FdPtPMoveAnimator(SoTransform* transF,
		    FdObject* object,
		    const SbVec3f& transl, // Translation of centerpoint. *NOT* incl. trans. from rot. link CS about an offset center.
		    const SbRotation& rot, // Rotation to "add" to the old
		    const SbVec3f& center,
		    const SbVec3f& oldGlobStickP,
		    bool addStickerYesOrNo = true,
		    SoTransform* transformBase = NULL);
  ~FdPtPMoveAnimator();

  void start();
  bool update();

  static void setAnimTime(float time) { animTime = time;}
  static void setAnimRate(float rate) { animRate = rate;}

private:
  FdObject*    objectToMove;
  SoTransform* transform;

  SbVec3f      centerPoint;
  SbVec3f      oldGlobStickPoint;
  bool         addSticker;

  SbMatrix*    baseMatrix;

  SbRotation   rotation;
  SbVec3f      translation;

  SbRotation   oldOrientation;
  SbVec3f      oldTranslation;

  SbRotation   currentRelRot;
  SbVec3f      oldLocalCenter;
  SbVec3f      newLocalCenter;

  SbRotation   totalOrientation;

  SbTime       startTime;
  static float animTime;
  static float animRate;

  SoTimerSensor* animationSensor;
};

#endif
