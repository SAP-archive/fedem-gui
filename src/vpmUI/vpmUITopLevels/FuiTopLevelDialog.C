// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiTopLevelDialog.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


enum {
  DONE = FFuDialogButtons::LEFTBUTTON,
  APPLY = FFuDialogButtons::MIDBUTTON,
  CANCEL = FFuDialogButtons::RIGHTBUTTON
};


void FuiTopLevelDialog::initWidgets()
{
  this->dialogButtons->setButtonClickedCB(FFaDynCB1M(FuiTopLevelDialog,this,
						     onDialogButtonClicked,int));
  this->dialogButtons->setButtonLabel(DONE,"OK");
  this->dialogButtons->setButtonLabel(APPLY,"Apply");
  this->dialogButtons->setButtonLabel(CANCEL,"Cancel");

  this->placeWidgets(this->getWidth(),this->getHeight());

  FFuUAExistenceHandler::invokeCreateUACB(this);
}


int FuiTopLevelDialog::getDialogButtonsHeightHint() const
{
  return this->dialogButtons->getHeightHint();
}


void FuiTopLevelDialog::placeWidgets(int width, int height)
{
  int y = height - this->dialogButtons->getHeightHint();
  this->dialogButtons->setEdgeGeometry(0,width,y,height);
}


void FuiTopLevelDialog::onPoppedUp()
{
  this->placeWidgets(this->getWidth(),this->getHeight());
  this->updateUIValues();
}


void FuiTopLevelDialog::onDialogButtonClicked(int button)
{
  switch (button) {
  case DONE:
    if (this->updateDBValues(false))
      this->invokeFinishedCB();
    break;
  case APPLY:
    this->updateDBValues(true);
    break;
  case CANCEL:
    this->invokeFinishedCB();
  }
}


bool FuiTopLevelDialog::onClose()
{
  this->invokeFinishedCB();
  return false;
}


void FuiTopLevelDialog::setSensitivity(bool sens)
{
  this->dialogButtons->setButtonSensitivity(DONE,sens);
  this->dialogButtons->setButtonSensitivity(APPLY,sens);
}
