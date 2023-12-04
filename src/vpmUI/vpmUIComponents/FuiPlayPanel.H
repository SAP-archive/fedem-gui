// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_PLAY_PANEL_H
#define FUI_PLAY_PANEL_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFuLib/FFuBase/FFuMultUIComponent.H"

class FFuToggleButton;
class FFuPushButton;
class FFuLabel;
class FFuScale;
class FFuFrame;


class FuiPlayPanel : public virtual FFuMultUIComponent
{
public:
  FuiPlayPanel() { IAmRestrictedToGLView = false; }
  virtual ~FuiPlayPanel() {}
 
  void makeSpeedControllsInactive(bool yesOrNo);
  void setSpeedScale(int value);
  
  bool isPingPong();
  bool isContinous();
  bool isShowAllFrames();
  int  getSpeedScaleValue();

  enum { PLAY_FWD,
	 PLAY_REW,
	 PAUSE,
	 TO_FIRST,
	 TO_LAST,
	 STEP_FWD,
	 STEP_REW,
	 STOP} ;

  enum { ONESHOT,
	 CONTINOUS,
	 CONTINOUS_CYCLE};
  
  void setAnimationPressCB  (const FFaDynCB1<int>& aDynCB);
  void setAnimTypeChangedCB (const FFaDynCB1<int>& aDynCB);
  void setRealTimeCB        (const FFaDynCB0& aDynCB);
  void setSpeedScaleChangeCB(const FFaDynCB1<int>& aDynCB);
  void setAllFramesCB       (const FFaDynCB1<bool> & aDynCB);
  void setCloseAnimCB       (const FFaDynCB0& dynCB)
  {this->closeAnimCB = dynCB;}

  void restrictToGLView();

protected:

  virtual void placeWidgets(int width, int height);
 
  // Initialisation to be called by UILib dep. subclass
  
  void init(); 
  
  // Internal Callbacks :

  void playFwdCB();
  void playRwdCB();
  void pauseCB  ();
  void toFirstCB();
  void toLastCB ();
  void stepFwdCB();
  void stepRwdCB();
  void stopCB   ();
  
  void onCloseAnimButtonClicked() {this->invokeCloseAnimCB();}
  void invokeCloseAnimCB() {this->closeAnimCB.invoke();}

  virtual void onPoppedUp();

  void onAnimTypeChanged  ( bool val );
  void onRealTimePressed  ( );
  void onAllFramesToggled ( bool val );
  void onSpeedScaleChanged( int  val );

  // Shadow Pt's from Subclass, 
  // Subclass is responsible to set them up:

  FFuToggleButton* myContinousToggleButton;
  FFuToggleButton* myAllFramesToggle;
  FFuToggleButton* myPingPongToggleButton;
  FFuLabel* myFastLabel;
  FFuLabel* mySlowLabel;
  FFuScale* mySpeedScale;
  FFuPushButton* myRealTimeButton;
  FFuPushButton* myStopPushButton;
  FFuPushButton* myToLastPushButton;
  FFuPushButton* myStepFwdPushButton;
  FFuPushButton* myStepRwdPushButton;
  FFuPushButton* myToFirstPushButton;
  FFuPushButton* myPlayPushButton;
  FFuPushButton* myPausePushButton;
  FFuPushButton* myPlayRwdPushButton;
  FFuFrame*      myMainFrame;
  FFuPushButton* myCloseAnimPushButton;
private:

  FFaDynCB1<int> myAnimationPressCB;
  FFaDynCB1<int> myAnimTypeChangedCB;

  FFaDynCB0       closeAnimCB;
  FFaDynCB0       myRealtimePressedCB;
  FFaDynCB1<bool> myAllFramesToggeledCB;
  FFaDynCB1<int>  mySpeedScaleChangedCB;

  bool IAmRestrictedToGLView;
};

#endif
