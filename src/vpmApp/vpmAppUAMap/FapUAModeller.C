// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAModeller.H"
#include "vpmApp/vpmAppCmds/FapAnimationCmds.H"

#include "vpmUI/vpmUITopLevels/FuiModeller.H"
#include "vpmUI/vpmUIComponents/Fui3DPoint.H"
#include "vpmUI/vpmUIComponents/FuiPlayPanel.H"
#include "vpmUI/FuiModes.H"

#ifdef USE_INVENTOR
#include "vpmDisplay/FdAnimateModel.H"
#include "vpmDisplay/FdPickedPoints.H"
#include "vpmDisplay/FdDB.H"
#endif

enum pointType { POINT_1, POINT_2 };

int FapUAModeller::whichPoint = 0;
FuiModeller* FapUAModeller::ourFuiModeller = NULL;


void FapUAModeller::init(FuiModeller* aFuiModeller)
{
  ourFuiModeller = aFuiModeller;
  if (ourFuiModeller)
    {
      ourFuiModeller->setPointChangedCB    (FFaDynCB2S(FapUAModeller::onPointChanged,const FaVec3&,bool));
      ourFuiModeller->setRefChangedCB      (FFaDynCB1S(FapUAModeller::onPointRefChanged,bool));
      ourFuiModeller->setAnimTypeChangedCB (FFaDynCB1S(FapUAModeller::onAnimTypeChange,int));
      ourFuiModeller->setAnimationPressCB  (FFaDynCB1S(FapUAModeller::onAnimationPress,int));
      ourFuiModeller->setRealTimeCB        (FFaDynCB0S(FapUAModeller::onRealTimePress));
      ourFuiModeller->setSpeedScaleChangeCB(FFaDynCB1S(FapUAModeller::onSpeedScaleChange,int));
      ourFuiModeller->setCloseAnimCB       (FFaDynCB0S(FapUAModeller::closeAnimation));
      ourFuiModeller->setAllFramesCB       (FFaDynCB1S(FapUAModeller::onAllFramesToggle,bool));
    }
}


void FapUAModeller::updateMode()
{
  if (!ourFuiModeller)
    return;

  switch (FuiModes::getMode())
    {
      // Modes that initially have a default global point
    case FuiModes::MAKEGENERALSPIDER_MODE:
    case FuiModes::MAKEFORCE_MODE:
    case FuiModes::MAKETORQUE_MODE:
    case FuiModes::MAKETRIAD_MODE:
    case FuiModes::MAKEREVJOINT_MODE:
    case FuiModes::MAKEBALLJOINT_MODE:
    case FuiModes::MAKERIGIDJOINT_MODE:
    case FuiModes::MAKESPRING_MODE:
    case FuiModes::MAKEDAMPER_MODE:
    case FuiModes::MAKEFREEJOINT_MODE:
    case FuiModes::MAKECYLJOINT_MODE:
    case FuiModes::MAKEPRISMJOINT_MODE:
    case FuiModes::MAKECAMJOINT_MODE:
    case FuiModes::COMPICKPOINT_MODE:
      whichPoint = POINT_1;
      ourFuiModeller->getPickedPointUIC()->setGlobalOnly();
      FapUAModeller::updatePointUI();
      ourFuiModeller->getPickedPointUIC()->popUp();
      break;
    default:
      break;
    }
}

void FapUAModeller::updateState(int newState)
{
  if (!ourFuiModeller)
    return;

  Fui3DPoint* pointUIC = ourFuiModeller->getPickedPointUIC();

  switch (FuiModes::getMode())
    {
    case FuiModes::MAKEGENERALSPIDER_MODE:
      switch (newState)
	{
	case 0:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 1:
	  pointUIC->popDown();
	  break;
	}
      break;

    case FuiModes::PTPMOVE_MODE:
      switch (newState)
	{
	case 0:
	  pointUIC->popDown();
	  break;
	case 1:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 2:
	  whichPoint = POINT_2;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 3:
	  whichPoint = POINT_2;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	}
      break;

    case FuiModes::MAKEFORCE_MODE:
    case FuiModes::MAKETORQUE_MODE:
    case FuiModes::MAKETRIAD_MODE:
    case FuiModes::MAKEREVJOINT_MODE:
    case FuiModes::MAKEBALLJOINT_MODE:
    case FuiModes::MAKERIGIDJOINT_MODE:
    case FuiModes::COMPICKPOINT_MODE:
      switch (newState)
	{
	case 0:
	  whichPoint = POINT_1;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 1:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	}
      break;

    case FuiModes::MAKEFREEJOINTBETWEENTRIADS_MODE:
      switch (newState)
      {
      case 2:
        whichPoint = POINT_1;
        pointUIC->setGlobalOnly();
        FapUAModeller::updatePointUI();
        pointUIC->popUp();
        break;
      default:
        pointUIC->popDown();
        break;
      }
      break;

    case FuiModes::MAKESPRING_MODE:
    case FuiModes::MAKEDAMPER_MODE:
    case FuiModes::MAKEFREEJOINT_MODE:
    case FuiModes::MAKECYLJOINT_MODE:
    case FuiModes::MAKEPRISMJOINT_MODE:
      switch (newState)
	{
	case 0:
	  whichPoint = POINT_1;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 1:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 2:
	  whichPoint = POINT_2;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 3:
	  whichPoint = POINT_2;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	}
      break;

    case FuiModes::MAKECAMJOINT_MODE:
      switch (newState)
	{
	case 0:
	  whichPoint = POINT_1;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 1:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 2:
	  whichPoint = POINT_1;
	  pointUIC->setGlobalOnly();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	case 3:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	}
      break;

    case FuiModes::MAKESTICKER_MODE:
      switch (newState)
	{
	case 0:
	  pointUIC->popDown();
	  break;
	case 1:
	  whichPoint = POINT_1;
	  pointUIC->setLocal();
	  FapUAModeller::updatePointUI();
	  pointUIC->popUp();
	  break;
	}
      break;

    default:
      break;
    }
}

void FapUAModeller::cancel()
{
  if (ourFuiModeller)
    ourFuiModeller->getPickedPointUIC()->popDown();
}

void FapUAModeller::onPointChanged(const FaVec3& newPoint, bool isGlobal)
{
#ifdef USE_INVENTOR
  if (FdDB::setPPoint(whichPoint,isGlobal,newPoint))
    FuiModes::notifyCreatePointChange();
#else
  std::cout <<"FapUAModeller::onPointChanged("<< newPoint
            <<" "<< std::boolalpha << isGlobal <<") does nothing."<< std::endl;
#endif
  FapUAModeller::updatePointUI();
}

void FapUAModeller::onPointRefChanged(bool)
{
  FapUAModeller::updatePointUI();
}

void FapUAModeller::updatePointUI()
{
#ifdef USE_INVENTOR
  if (!ourFuiModeller) return;

  Fui3DPoint* pointUIC = ourFuiModeller->getPickedPointUIC();
  FaVec3 point = FdDB::getPPoint(whichPoint,pointUIC->isGlobal());

  // Trim small numbers (due to round-off in global-to-local transformations?)
  const double ptol = 1.0e-8;
  for (int i = 0; i < 3; i++)
    if (point[i] < ptol && -point[i] < ptol)
      point[i] = 0.0;

  pointUIC->setValue(point);
#endif
}

void FapUAModeller::setGlobalOnly()
{
  ourFuiModeller->getPickedPointUIC()->setGlobalOnly();
}

void FapUAModeller::setLocal()
{
  ourFuiModeller->getPickedPointUIC()->setLocal();
}

void FapUAModeller::showPointUI(bool doShow)
{
  if (doShow)
    ourFuiModeller->getPickedPointUIC()->popUp();
  else
    ourFuiModeller->getPickedPointUIC()->popDown();
}

//////////////////////////////////
//
//  Animation Control
//  Callbacks :
//
/////////////////////////////////

void FapUAModeller::onAllFramesToggle(bool onOrOff)
{
  FapAnimationCmds::animationToggleSkip(!onOrOff);
}

void FapUAModeller::onSpeedScaleChange(int value)
{
  FapAnimationCmds::animationFrequencyScale((float)value);
}

void FapUAModeller::onAnimationPress(int action)
{
  switch (action)
    {
    case FuiPlayPanel::TO_LAST:
      FapAnimationCmds::animationToLastFrame();
      break;
    case FuiPlayPanel::TO_FIRST:
      FapAnimationCmds::animationToFirstFrame();
      break;
    case FuiPlayPanel::PLAY_REW:
      FapAnimationCmds::animationPlayReverse();
      break;
    case FuiPlayPanel::STEP_REW:
      FapAnimationCmds::animationStepRwd();
      break;
    case FuiPlayPanel::STOP:
      FapAnimationCmds::animationStop();
      break;
    case FuiPlayPanel::PAUSE:
      FapAnimationCmds::animationPause();
      break;
    case FuiPlayPanel::PLAY_FWD:
      FapAnimationCmds::animationPlay();
      break;
    case FuiPlayPanel::STEP_FWD:
      FapAnimationCmds::animationStepFwd();
      break;
    }
}

void FapUAModeller::onRealTimePress()
{
  FapAnimationCmds::absoluteAnimationFrequency(100);
}

void FapUAModeller::closeAnimation()
{
  FapAnimationCmds::hide();
}

void FapUAModeller::onAnimTypeChange(int animationType)
{
  switch (animationType)
    {
    case FuiPlayPanel::ONESHOT:
#ifdef USE_INVENTOR
      FapAnimationCmds::animationType(FdAnimateModel::ONESHOT);
#endif
      break;
    case FuiPlayPanel::CONTINOUS:
#ifdef USE_INVENTOR
      FapAnimationCmds::animationType(FdAnimateModel::LOOP);
#endif
      break;
    case FuiPlayPanel::CONTINOUS_CYCLE:
#ifdef USE_INVENTOR
      FapAnimationCmds::animationType(FdAnimateModel::PINGPONG);
#endif
      break;
    }
}
