// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiPlayPanel.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuScale.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "FFuLib/FFuFrame.H"


//////////////////////////////////////////////////////////////////////
//
// Initialise method to be called from subclass constructor :
//

void FuiPlayPanel::init()
{
    this->myStopPushButton   ->setPixMap((const char **)animStop_xpm   );
    this->myToLastPushButton ->setPixMap((const char **)animToLast_xpm );
    this->myStepFwdPushButton->setPixMap((const char **)animStepFwd_xpm);
    this->myStepRwdPushButton->setPixMap((const char **)animStepRwd_xpm);
    this->myToFirstPushButton->setPixMap((const char **)animToFirst_xpm);
    this->myPlayPushButton   ->setPixMap((const char **)animPlay_xpm   );
    this->myPausePushButton  ->setPixMap((const char **)animPause_xpm  );
    this->myPlayRwdPushButton->setPixMap((const char **)animPlayRwd_xpm);

    this->myCloseAnimPushButton   ->setLabel("Close");
    this->myContinousToggleButton->setLabel("Continous");
    this->myAllFramesToggle      ->setLabel("Show all frames");
    this->myPingPongToggleButton ->setLabel("Cycle");
    this->myFastLabel            ->setLabel("Fast");
    this->mySlowLabel            ->setLabel("Slow");
    this->myRealTimeButton       ->setLabel("Real"); 

    this->myPlayPushButton   ->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, playFwdCB));
    this->myPlayRwdPushButton->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, playRwdCB));
    this->myPausePushButton  ->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, pauseCB));
    this->myToFirstPushButton->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, toFirstCB));
    this->myToLastPushButton ->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, toLastCB));
    this->myStepFwdPushButton->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, stepFwdCB));
    this->myStepRwdPushButton->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, stepRwdCB));
    this->myStopPushButton   ->setActivateCB(FFaDynCB0M(FuiPlayPanel,this, stopCB));

    this->myCloseAnimPushButton->setActivateCB(FFaDynCB0M(FuiPlayPanel,this,onCloseAnimButtonClicked));

    this->myContinousToggleButton->setToggleCB(FFaDynCB1M(FuiPlayPanel,this,onAnimTypeChanged,bool));

    this->myPingPongToggleButton ->setToggleCB(FFaDynCB1M(FuiPlayPanel,this,onAnimTypeChanged ,bool));
 
    this->myRealTimeButton->setActivateCB(FFaDynCB0M(FuiPlayPanel, this, onRealTimePressed));
   
    this->myAllFramesToggle->setToggleCB(FFaDynCB1M(FuiPlayPanel,this,onAllFramesToggled ,bool));

    this->mySpeedScale->setMinMax(1,100);
    this->mySpeedScale->setValue(50);
    this->mySpeedScale->setDragCB(FFaDynCB1M(FuiPlayPanel,this,onSpeedScaleChanged,int));
}

//////////////////////////////////////////////////////////////////////
//
// Geometry management :
//

void FuiPlayPanel::placeWidgets(int width, int height)
{
  int corrHeight = height;
  
  if (IAmRestrictedToGLView)
    corrHeight = (int)(1.27*height); // To make use of room after allframestoggle etc.

  // Horisontal GridLines :
  
  int glH1  = FFuMultUIComponent::getGridLinePos(corrHeight,  40);
  int glH2  = FFuMultUIComponent::getGridLinePos(corrHeight, 176);
  int glH3  = FFuMultUIComponent::getGridLinePos(corrHeight, 313);
  int glH4  = FFuMultUIComponent::getGridLinePos(corrHeight, 449);
  int glH5  = FFuMultUIComponent::getGridLinePos(corrHeight, 469);
  int glH5_4= FFuMultUIComponent::getGridLinePos(corrHeight, 555);
  int glH5_5= FFuMultUIComponent::getGridLinePos(corrHeight, 565);
  int glH6  = FFuMultUIComponent::getGridLinePos(corrHeight, 650);
  int glH7  = FFuMultUIComponent::getGridLinePos(height, 680);
  int glH8  = FFuMultUIComponent::getGridLinePos(height, 773);
  int glH9  = FFuMultUIComponent::getGridLinePos(height, 866);
  int glH10 = FFuMultUIComponent::getGridLinePos(height, 959);

  // Vertical GridLines :

  int glV1  = FFuMultUIComponent::getGridLinePos(width,   40);
  int glV2  = FFuMultUIComponent::getGridLinePos(width,  270);
  int glV3  = FFuMultUIComponent::getGridLinePos(width,  385);
  int glV4  = FFuMultUIComponent::getGridLinePos(width,  500);
  int glV5  = FFuMultUIComponent::getGridLinePos(width,  615);
  int glV6  = FFuMultUIComponent::getGridLinePos(width,  730);
  int glV7  = FFuMultUIComponent::getGridLinePos(width,  960);

  this->myMainFrame->setEdgeGeometry(0,width,0,height);

  this->myContinousToggleButton->setEdgeGeometry(glV1,glV7,glH8,glH9);
  this->myAllFramesToggle      ->setEdgeGeometry(glV1,glV7,glH7,glH8);
  this->myPingPongToggleButton ->setEdgeGeometry(glV1,glV7,glH9,glH10);

  this->myFastLabel->setEdgeGeometry(     glV5, glV7, glH5,  glH5_4);
  this->mySlowLabel->setEdgeGeometry(     glV1, glV3, glH5,  glH5_4);
  this->mySpeedScale->setEdgeGeometry(    glV1, glV7, glH5_5,glH6  );
  this->myRealTimeButton->setEdgeGeometry(glV3 -3, glV5+3, glH5,  glH5_4);

  this->myStopPushButton->setEdgeGeometry(   glV1, glV7, glH3, glH4 );
  this->myToLastPushButton->setEdgeGeometry( glV6, glV7, glH2, glH3 );
  this->myStepFwdPushButton->setEdgeGeometry(glV4, glV6, glH2, glH3 );
  this->myStepRwdPushButton->setEdgeGeometry(glV2, glV4, glH2, glH3 );
  this->myToFirstPushButton->setEdgeGeometry(glV1, glV2, glH2, glH3 );
  this->myPlayPushButton->setEdgeGeometry(   glV5, glV7, glH1, glH2 );
  this->myPausePushButton->setEdgeGeometry(  glV3, glV5, glH1, glH2 );
  this->myPlayRwdPushButton->setEdgeGeometry(glV1, glV3, glH1, glH2 );
 
  this->myCloseAnimPushButton->setEdgeGeometry(   glV5, glV7,glH9 ,  glH10+5);
}

void FuiPlayPanel::restrictToGLView()
{
  this->myRealTimeButton->popDown();
  this->myAllFramesToggle->popDown();
  this->myContinousToggleButton->setValue(true);
  this->myContinousToggleButton->popDown();
  this->IAmRestrictedToGLView = true;
}

//////////////////////////////////////////////////////////////////////
//
// Set values :
//

void FuiPlayPanel::makeSpeedControllsInactive(bool yesOrNo)
{
  this->myRealTimeButton->setSensitivity(!yesOrNo);
  this->mySpeedScale->setSensitivity(yesOrNo);
}

void FuiPlayPanel::setSpeedScale(int value)
{
  this->mySpeedScale->setValue(value);
}

//////////////////////////////////////////////////////////////////////
//
// Get values :
//
  
bool FuiPlayPanel::isPingPong()
{
  return myPingPongToggleButton->getValue();
}

bool FuiPlayPanel::isContinous()
{
  return myContinousToggleButton->getValue();
}

bool FuiPlayPanel::isShowAllFrames()
{
  return myAllFramesToggle->getValue();
}

int FuiPlayPanel::getSpeedScaleValue()
{
  return mySpeedScale->getValue();
}

//////////////////////////////////////////////////////////////////////
//
// Set Callbacks :
//

void FuiPlayPanel::setAnimationPressCB(const FFaDynCB1<int>& aDynCB)
{
  this->myAnimationPressCB = aDynCB;  
}

void FuiPlayPanel::setAnimTypeChangedCB(const FFaDynCB1<int>& aDynCB)
{
  this->myAnimTypeChangedCB = aDynCB;  
}

void FuiPlayPanel::setAllFramesCB(const FFaDynCB1<bool> &aDynCB) 
{
  myAllFramesToggeledCB = aDynCB;
}

void FuiPlayPanel::setRealTimeCB(const FFaDynCB0& aDynCB)
{
  myRealtimePressedCB = aDynCB;
}

void FuiPlayPanel::setSpeedScaleChangeCB (const FFaDynCB1<int>& aDynCB)
{
  mySpeedScaleChangedCB = aDynCB;
}


//////////////////////////////////////////////////////////////////////
//
// Internal Callbacks that invokes the external callbacks :
// Mapping from widget CB's to Component CB's
//

void FuiPlayPanel::playFwdCB()
{
  this->myAnimationPressCB.invoke(PLAY_FWD);
}

void FuiPlayPanel::playRwdCB()
{
  this->myAnimationPressCB.invoke(PLAY_REW);
}

void FuiPlayPanel::pauseCB()
{
  this->myAnimationPressCB.invoke(PAUSE);
}

void FuiPlayPanel::toFirstCB()
{
  this->myAnimationPressCB.invoke(TO_FIRST);
}

void FuiPlayPanel::toLastCB()
{
  this->myAnimationPressCB.invoke(TO_LAST);
}

void FuiPlayPanel::stepFwdCB()
{
  this->myAnimationPressCB.invoke(STEP_FWD);
}

void FuiPlayPanel::stepRwdCB()
{
  this->myAnimationPressCB.invoke(STEP_REW);
}

void FuiPlayPanel::stopCB()
{
  this->myAnimationPressCB.invoke(STOP);
}


void FuiPlayPanel::onAnimTypeChanged(bool)
{
  if (!this->isContinous())
    this->myAnimTypeChangedCB.invoke(FuiPlayPanel::ONESHOT);
  else if (this->isPingPong())
    this->myAnimTypeChangedCB.invoke(FuiPlayPanel::CONTINOUS_CYCLE);
  else
    this->myAnimTypeChangedCB.invoke(FuiPlayPanel::CONTINOUS);
}

void FuiPlayPanel::onRealTimePressed()
{
  this->setSpeedScale(50);
  myRealtimePressedCB.invoke();
}

void FuiPlayPanel::onAllFramesToggled(bool val)
{
  myAllFramesToggeledCB.invoke(val);
}


void FuiPlayPanel::onSpeedScaleChanged(int val)
{ 
  mySpeedScaleChangedCB.invoke(val); 
}

void FuiPlayPanel::onPoppedUp()
{
  this->onAnimTypeChanged(true);
  this->onAllFramesToggled(this->isShowAllFrames());
  this->onSpeedScaleChanged(this->getSpeedScaleValue());
}
