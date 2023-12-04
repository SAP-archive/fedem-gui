// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_DIALOGi_BUTTONS_H
#define FFU_DIALOG_BUTTONS_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuPushButton;
class FFuFrame;


class FFuDialogButtons : virtual public FFuMultUIComponent
{
public:
  FFuDialogButtons();
  virtual ~FFuDialogButtons();

public:
  enum { //Buttons
    LEFTBUTTON, // 0
    MIDBUTTON,  // 1
    RIGHTBUTTON,// 2
    NBUTTONS    // 3 
  };

  //You get the buttons in which you set their labels
  //Empty label ("") gives no button
  void setButtonLabel(int button,const char* label);
  void setButtonSensitivity(int button,bool makeSensitive);
  void setButtonClickedCB(const FFaDynCB1<int>& dynCB);
  
  virtual int getWidthHint(); 
  virtual int getHeightHint();// with borders on all sides

protected:
  void initWidgets(const char* leftButtonLabel,const char* midButtonLabel,
		   const char* rightButtonLabel); 

  virtual void placeWidgets(int width,int height);

private:
  void initVariables();
  void onLeftButtonClicked();
  void onMidButtonClicked();
  void onRightButtonClicked();

protected:
  FFuPushButton* leftButton;
  FFuPushButton* midButton;
  FFuPushButton* rightButton;
  FFuFrame*      separator;

  bool leftButtonUp;
  bool midButtonUp;
  bool rightButtonUp;

private:
  FFaDynCB1<int> buttonClickedCB;
};

#endif
