// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuFrame.H"
#include <cstring>


//----------------------------------------------------------------------------

FFuDialogButtons::FFuDialogButtons()
{
  this->initVariables();
}
//----------------------------------------------------------------------------

FFuDialogButtons::~FFuDialogButtons()
{
}
//----------------------------------------------------------------------------

void FFuDialogButtons::initVariables()
{
  this->leftButton = 0;
  this->midButton = 0;
  this->rightButton = 0;
  this->separator = 0;
  
  this->leftButtonUp = false;
  this->midButtonUp = false;
  this->rightButtonUp = false;
}
//----------------------------------------------------------------------------

void FFuDialogButtons::initWidgets(const char* leftButtonLabel, const char* midButtonLabel,
				   const char* rightButtonLabel)
{
  //labels
  this->leftButton->setLabel(leftButtonLabel);
  this->midButton->setLabel(midButtonLabel);
  this->rightButton->setLabel(rightButtonLabel);

  //cb's
  this->leftButton->setActivateCB(FFaDynCB0M(FFuDialogButtons,this,onLeftButtonClicked));
  this->midButton->setActivateCB(FFaDynCB0M(FFuDialogButtons,this,onMidButtonClicked));
  this->rightButton->setActivateCB(FFaDynCB0M(FFuDialogButtons,this,onRightButtonClicked));

  //popUp/Down
  if (this->leftButtonUp)  this->leftButton->popUp();
  else this->leftButton->popDown();

  if (this->midButtonUp)  this->midButton->popUp();
  else this->midButton->popDown();

  if (this->rightButtonUp) this->rightButton->popUp();
  else this->rightButton->popDown();
}
//----------------------------------------------------------------------------

void FFuDialogButtons::setButtonClickedCB(const FFaDynCB1<int>& dynCB)
{
  this->buttonClickedCB = dynCB;
}
//----------------------------------------------------------------------------

void FFuDialogButtons::onLeftButtonClicked()
{
  this->buttonClickedCB.invoke(LEFTBUTTON);
}
//----------------------------------------------------------------------------

void FFuDialogButtons::onMidButtonClicked()
{
  this->buttonClickedCB.invoke(MIDBUTTON);
}
//----------------------------------------------------------------------------

void FFuDialogButtons::onRightButtonClicked()
{
  this->buttonClickedCB.invoke(RIGHTBUTTON);
}
//----------------------------------------------------------------------------

void FFuDialogButtons::setButtonLabel(int button, const char* label)
{
  switch (button) {
  case LEFTBUTTON:
    if (strcmp(label,"")) {
      this->leftButton->setLabel(label);
      this->leftButton->popUp();
      this->leftButtonUp = true;
    }
    else {
      this->leftButton->popDown();
      this->leftButtonUp = false;
    }
    break;
  case MIDBUTTON:
    if (strcmp(label,"")) {
      this->midButton->setLabel(label);
      this->midButton->popUp();
      this->midButtonUp = true;
    }
    else {
      this->midButton->popDown();
      this->midButtonUp = false;
    }
    break;
  case RIGHTBUTTON:
    if (strcmp(label,"")) {
      this->rightButton->setLabel(label);
      this->rightButton->popUp();
      this->rightButtonUp = true;
    }
    else {
      this->rightButton->popDown();
      this->rightButtonUp = false;
    }
    break;
  }
}
//----------------------------------------------------------------------------

void FFuDialogButtons::setButtonSensitivity(int button,bool makeSensitive)
{
  switch (button) {
  case LEFTBUTTON:  this->leftButton->setSensitivity(makeSensitive); break;
  case MIDBUTTON:   this->midButton->setSensitivity(makeSensitive); break;
  case RIGHTBUTTON: this->rightButton->setSensitivity(makeSensitive); break;
  }
}
//----------------------------------------------------------------------------


void FFuDialogButtons::placeWidgets(int width,int height)
{
  //l-left, r-right, t-top, b-bottom,
  int border = this->getBorder();
  int maxbuttw = 0;
  int maxbutth = 0;
  
  if (this->leftButtonUp){ 
    if (this->leftButton->getWidthHint() > maxbuttw)  maxbuttw = this->leftButton->getWidthHint();
    if (this->leftButton->getHeightHint() > maxbutth) maxbutth = this->leftButton->getHeightHint();
  }
  if (this->midButtonUp) {
    if (this->midButton->getWidthHint() > maxbuttw)  maxbuttw = this->midButton->getWidthHint();
    if (this->midButton->getHeightHint() > maxbutth) maxbutth = this->midButton->getHeightHint();
  }
  if (this->rightButtonUp) {
    if (this->rightButton->getWidthHint() > maxbuttw)  maxbuttw = this->rightButton->getWidthHint();
    if (this->rightButton->getHeightHint() > maxbutth) maxbutth = this->rightButton->getHeightHint();
  }
  //GridLines 
  //vertical borders
  int glbl  = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_START);
  int glbr  = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_END);
  //horisontal borders
  int glbb  = this->getGridLinePos(height,border,FFuMultUIComponent::FROM_END);

  int glh1 = this->getGridLinePos(height,border+maxbutth+border,FFuMultUIComponent::FROM_END);

  //place widgets
  if (this->separator)
    this->separator->setSizeGeometry(glbl,glh1,glbr-glbl,2);
  if (this->leftButtonUp)     
    this->leftButton->setSizeGeometry(glbl,glbb-maxbutth,maxbuttw,maxbutth); //left
  if (this->midButtonUp)  
    this->midButton->setSizeGeometry((glbl+glbr)/2-maxbuttw/2,glbb-maxbutth,maxbuttw,maxbutth);//mid
  if (this->rightButtonUp)
    this->rightButton->setSizeGeometry(glbr-maxbuttw,glbb-maxbutth,maxbuttw,maxbutth);//right
}
//-----------------------------------------------------------------------------
 
int FFuDialogButtons::getWidthHint()
{
  int border = this->getBorder();
  int maxbuttw = 0;
  int maxw = 0;
  
  if (this->leftButtonUp)
    if (this->leftButton->getWidthHint() > maxbuttw) maxbuttw = this->leftButton->getWidthHint();
  if (this->midButtonUp) 
    if (this->midButton->getWidthHint() > maxbuttw) maxbuttw = this->midButton->getWidthHint();
  if (this->rightButtonUp) 
    if (this->rightButton->getWidthHint() > maxbuttw) maxbuttw = this->rightButton->getWidthHint();
  
  if (this->leftButtonUp)
    maxw += maxbuttw+border;
  if (this->midButtonUp) {
    if (!this->leftButtonUp || !this->rightButtonUp)
      maxw += 2*(maxbuttw+border);
    else 
      maxw += maxbuttw+border;
  }
  if (this->rightButtonUp) 
    maxw += maxbuttw+border;
  
  maxw += border;
  return maxw;
}
//----------------------------------------------------------------------------

int FFuDialogButtons::getHeightHint()
{
  int border = this->getBorder();
  int maxbutth = 0;
  int maxh = 0;
  
  if (this->leftButtonUp)
    if (this->leftButton->getHeightHint() > maxbutth)  maxbutth = this->leftButton->getHeightHint();
  if (this->midButtonUp) 
    if (this->midButton->getHeightHint() > maxbutth)  maxbutth = this->midButton->getHeightHint();
  if (this->rightButtonUp) 
    if (this->rightButton->getHeightHint() > maxbutth)  maxbutth = this->rightButton->getHeightHint();
  
  if (this->midButtonUp)
    maxh = maxbutth + 4*border;
  else if (this->leftButtonUp || this->rightButtonUp)
    maxh = maxbutth + 3*border;
  
  if (!this->separator)
    maxh -= border;
  
  return maxh;
}
//----------------------------------------------------------------------------
