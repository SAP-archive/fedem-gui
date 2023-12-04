// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"


FFuQtRadioButton::FFuQtRadioButton(QWidget* parent, const char* name)
  : QRadioButton(name,parent)
{
  this->setButtonWidget(this);
  this->setAutoExclusive(false);

  QObject::connect(this,SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));
}


void FFuQtRadioButton::setUIValue(bool onOrOff)
{
  this->blockLibSignals(true);
  this->setChecked(onOrOff);
  this->blockLibSignals(false);
}

bool FFuQtRadioButton::getValue() const
{
  return this->isChecked();
}


void FFuQtRadioButton::onToggled(bool value)
{
  this->callToggleCB(value);
}
