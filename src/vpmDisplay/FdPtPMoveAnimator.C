// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdPtPMoveAnimator.H"
#include "vpmDisplay/FdSimpleJoint.H"
#include "vpmDisplay/FdPart.H"
#include "vpmDisplay/FdTriad.H"
#include "vpmDisplay/FdConverter.H"

#include "vpmDB/FmSticker.H"
#include "vpmDB/FmFreeJoint.H"
#include "vpmDB/FmPart.H"
#include "vpmDB/FmTriad.H"

#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoTransform.h>


float FdPtPMoveAnimator::animTime = 2.0f;   // Seconds the animation will last.
float FdPtPMoveAnimator::animRate = 0.017f; // Seconds between frames


static void sensorCB(void* anim, SoSensor*)
{
  FdPtPMoveAnimator* animator = (FdPtPMoveAnimator*)anim;
  if (animator->update())
    delete animator;
}


FdPtPMoveAnimator::FdPtPMoveAnimator(SoTransform* transf,
                                     FdObject* object,
                                     const SbVec3f& transl,
                                     const SbRotation& rot,
                                     const SbVec3f& center,
                                     const SbVec3f& oldGlobStickP,
                                     bool addStickerYesOrNo,
                                     SoTransform* transformBase)
{
  // Set up animationsensor:
  // Register "sensorCB" as callback, and set animation rate
  animationSensor = new SoTimerSensor(sensorCB,(void*)this);
  animationSensor->setInterval(animRate);

  // Save control data:
  transform = transf;
  transform->ref();

  objectToMove = object;
  addSticker   = addStickerYesOrNo;

  // Save positional data :

  if (transformBase)
  {
    // We have a base-transformation. Then we have to transform
    // the positional data so that it becomes relative the base-transform

    SbMatrix   invBaseMatrix;
    SbRotation invBaseRotation;

    // Make Matrix from base transform:
    baseMatrix = new SbMatrix();
    baseMatrix->setTransform(transformBase->translation.getValue(),
                            transformBase->rotation.getValue(),
                            SbVec3f(1,1,1));
    invBaseMatrix = baseMatrix->inverse();
    invBaseRotation.setValue(invBaseMatrix);

    // Save control positional data
    invBaseMatrix.multVecMatrix(center, centerPoint);
    invBaseMatrix.multVecMatrix(oldGlobStickP, oldGlobStickPoint);

    rotation = rot;
    invBaseRotation.multVec(transl,translation);
  }
  else
  {
    // We are working relative the global coordinate system

    baseMatrix = NULL;

    // Save control positional data:
    centerPoint       = center;
    oldGlobStickPoint = oldGlobStickP;

    // Save changes in position:
    rotation    = rot;
    translation = transl;
  }

  // Save starting Position
  oldTranslation = transform->translation.getValue();
  oldOrientation = transform->rotation.getValue();
  oldLocalCenter = centerPoint - oldTranslation;

  totalOrientation = oldOrientation * rotation;
}


FdPtPMoveAnimator::~FdPtPMoveAnimator()
{
  transform->unref();
  delete animationSensor;
  delete baseMatrix;
}


void FdPtPMoveAnimator::start()
{
  // Get animation starting time
  startTime.setToTimeOfDay();

  // Schedule sensor and call viewer start callbacks
  if (!animationSensor->isScheduled())
    animationSensor->schedule();
}


bool FdPtPMoveAnimator::update()
{
  // Called whenever the PtPMoveanimation sensor fires. Finds the amount
  // of time since we started PtPMove and does the correct interpolation.

  // Get the time difference
  SbTime time     = SbTime::getTimeOfDay();
  SbTime timeDiff = time - startTime;

  // Get the interpolation parameter, truncate to 1.0 if larger
  float t = (float)timeDiff.getValue() / animTime;
  if (t > 0.9999f) t = 1.0f;

  // Transform according to the animation time
  // Use an ease-in ease-out approach:
  float cos_t = 0.5f * (1.0f - (float)cos(t*M_PI));

  transform->rotation = SbRotation::slerp(oldOrientation, totalOrientation, cos_t);

  // Translating Coordinate system along an arc.
  // The rotation center will only translate along actual glider.

  if (oldLocalCenter.length() < 1.0e-12f) // Glide translation
    transform->translation = oldTranslation + translation * cos_t;
  else // Rotation + Glide translation
  {
    currentRelRot = SbRotation::slerp(SbRotation::identity(), rotation, cos_t);
    currentRelRot.multVec(oldLocalCenter,newLocalCenter);
    transform->translation = oldTranslation + (oldLocalCenter - newLocalCenter)
                                            + translation * cos_t;
  }

  if (t < 1.0f) return false;

  // This was the last interval, thus stop animation:
  animationSensor->unschedule();

  // And update the DB object:

  // Unless a Simple Joint, Smart Move is supposed to move the complete joint
  // (master and slave as well) so the master triad update will be sufficient.
  if (!objectToMove->isOfType(FdSimpleJoint::getClassTypeID()))
    objectToMove->updateFmOwner();

  if (objectToMove->isOfType(FdTriad::getClassTypeID()))
  {
    // Update the other triad in a free SingleMasterJoint
    // if objectToMove is member of such a joint:
    std::vector<FmJointBase*> joints;
    FmTriad* triadToMove = (FmTriad*)(objectToMove->getFmOwner());
    triadToMove->getJointBinding(joints);
    if (!joints.empty())
    {
      FmJointBase* joint = joints.front();
      if (!joint->isAttachedToLink() && joint->isOfType(FmSMJointBase::getClassTypeID()) && !joint->isOfType(FmFreeJoint::getClassTypeID()))
      {
        if (triadToMove->isSlaveTriad())
          ((FmSMJointBase*)joint)->getItsMasterTriad()->getFdPointer()->updateFmOwner();
        else if (triadToMove->isMasterTriad())
          joint->getSlaveTriad()->getFdPointer()->updateFmOwner();
      }
    }
  }

  else if (objectToMove->isOfType(FdPart::getClassTypeID()))
  {
    // We have moved a part. A part may have free joint ends (triads)
    // that must get their DB coordinate systems updated.
    // These triads only have global coordinate systems, you see.
    std::vector<FmTriad*> triads;
    ((FmPart*)(objectToMove->getFmOwner()))->getFreeJointEnds(triads);
    for (FmTriad* triad : triads)
      triad->getFdPointer()->updateFmOwner();
  }

  if (addSticker && objectToMove->getFmOwner()->isOfType(FmIsPositionedBase::getClassTypeID()))
  {
    // Add Sticker on the first picked point after transforming it to new position
    SbMatrix newTransform, oldTransform, oldInvTransform;
    SbVec3f  newGlobStickPoint, localStickPoint;

    // Recreate old transform:
    oldTransform.setTransform(oldTranslation, oldOrientation, SbVec3f(1,1,1));
    // Invert it:
    oldInvTransform = oldTransform.inverse();
    // Get local sticker point:
    oldInvTransform.multVecMatrix(oldGlobStickPoint, localStickPoint);

    // Create transform from the new position:
    newTransform.setTransform(transform->translation.getValue(),
                              transform->rotation.getValue(), SbVec3f(1,1,1));
    // Multiply it with local stickerPoint to get new global sticker point:
    newTransform.multVecMatrix(localStickPoint,newGlobStickPoint);
    if (baseMatrix)
      baseMatrix->multVecMatrix(newGlobStickPoint,newGlobStickPoint);

    // Place sticker at new point, and add it:
    FmSticker* sticker = new FmSticker;
    sticker->placeAtPoint(FdConverter::toFaVec3(newGlobStickPoint));
    ((FmIsPositionedBase*)(objectToMove->getFmOwner()))->addSticker(sticker);

    // Make it visible:
    sticker->getFdPointer()->updateFdAll();
  }

  return true;
}
