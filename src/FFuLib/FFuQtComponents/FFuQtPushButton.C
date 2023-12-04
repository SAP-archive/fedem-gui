// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"


FFuQtPushButton::FFuQtPushButton(QWidget* parent, const char* name)
  : QPushButton(name,parent)
{
  this->setButtonWidget(this);

  QObject::connect(this,SIGNAL(pressed()), this, SLOT(arm()));
  QObject::connect(this,SIGNAL(released()),this, SLOT(unarm()));
  QObject::connect(this,SIGNAL(clicked()), this, SLOT(activate()));
  QObject::connect(this,SIGNAL(toggled(bool)), this, SLOT(toggle(bool)));
}


void FFuQtPushButton::setToggleAble(bool able)
{
  this->setCheckable(able);
}

void FFuQtPushButton::toggleOn(bool toggle)
{
  if (!this->isCheckable())
    this->setCheckable(true);

  this->setChecked(toggle);
}


void FFuQtPushButton::arm()
{
  this->callArmCB();
}

void FFuQtPushButton::unarm()
{
  this->callUnarmCB();
}

void FFuQtPushButton::activate()
{
  this->callActivateCB();
}

void FFuQtPushButton::toggle(bool value)
{
  this->callToggleCB(value);
}
