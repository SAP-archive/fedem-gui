// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuQtToggleButton.H"


FFuQtToggleButton::FFuQtToggleButton(QWidget* parent, const char* name)
  : QCheckBox(name,parent)
{
  this->setButtonWidget(this);

  QObject::connect(this,SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
}


void FFuQtToggleButton::setUIValue(bool onOrOff)
{
  this->blockLibSignals(true);
  this->setChecked(onOrOff);
  this->blockLibSignals(false);
}

bool FFuQtToggleButton::getValue() const
{
  return this->isChecked();
}


void FFuQtToggleButton::onStateChanged(int value)
{
  this->callToggleCB(value > 0);
}


int FFuQtToggleButton::getTristateValue() const
{
  switch (this->checkState()) {
    case Qt::Checked:
      return 2;
    case Qt::PartiallyChecked:
      return 1;
    default:
      return 0;
  }
}


void FFuQtToggleButton::useUITristate(bool y)
{
  this->blockLibSignals(true);
  this->setTristate(y);
  this->blockLibSignals(false);
}


void FFuQtToggleButton::setUITristateValue(int value)
{
  this->blockLibSignals(true);
  switch (value) {
    case 2:
      this->setCheckState(Qt::Checked);
      break;
    case 1:
      this->setCheckState(Qt::PartiallyChecked);
      break;
    default:
      this->setCheckState(Qt::Unchecked);
      break;
  }

  this->blockLibSignals(false);
}
