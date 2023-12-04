// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QSpinBox>

#include "FFuLib/FFuQtComponents/FFuQtSpinBox.H"


FFuQtSpinBox::FFuQtSpinBox(QWidget* parent) : QSpinBox(parent)
{
  this->setWidget(this);

  QObject::connect(this, SIGNAL(valueChanged(int)),this,SLOT(fwdValueChanged(int)));
}

void FFuQtSpinBox::setIntValue(int value)
{
  this->blockLibSignals(true);
  this->setValue(value);
  this->blockLibSignals(false);
}

int FFuQtSpinBox::getIntValue()
{
  return this->value();
}

void FFuQtSpinBox::setPrefixString(const std::string& prefix)
{
  this->setPrefix(prefix.c_str());
}

std::string FFuQtSpinBox::getPrefixString()
{
  return this->prefix().toStdString();
}

void FFuQtSpinBox::setSuffixString(const std::string& suffix)
{
  this->setSuffix(suffix.c_str());
}

std::string FFuQtSpinBox::getSuffixString()
{
  return this->suffix().toStdString();
}

bool FFuQtSpinBox::hasWrapping()
{
  return this->wrapping();
}

void FFuQtSpinBox::setWrapping(bool on)
{
  this->QSpinBox::setWrapping(on);
}

void FFuQtSpinBox::setButtonSymbol(int symbol)
{
  switch (symbol) {
  case ARROWS:
    this->setButtonSymbols(QSpinBox::UpDownArrows);
    break;
  case PLUS_MINUS:
    this->setButtonSymbols(QSpinBox::PlusMinus);
    break;
  default:
    this->setButtonSymbols(QSpinBox::UpDownArrows);
    break;
  }
}

int FFuQtSpinBox::getButtonSymbol()
{
  switch (this->buttonSymbols()) {
  case QSpinBox::UpDownArrows:
    return ARROWS;
  case QSpinBox::PlusMinus:
    return PLUS_MINUS;
  default:
    return ARROWS;
  }
}

void FFuQtSpinBox::setMinMax(int min, int max)
{
  this->setMinimum(min);
  this->setMaximum(max);
}

int FFuQtSpinBox::getMinValue()
{
  return this->minimum();
}

int FFuQtSpinBox::getMaxValue()
{
  return this->maximum();
}

void FFuQtSpinBox::setStepSize(int step)
{
  this->setSingleStep(step);
}

int FFuQtSpinBox::getStepSize()
{
  return this->singleStep();
}

void FFuQtSpinBox::stepOneUp()
{
  this->stepUp();
}

void FFuQtSpinBox::stepOneDown()
{
  this->stepDown();
}

void FFuQtSpinBox::fwdValueChanged(int value)
{
  this->callValueChangedCB(value);
}
