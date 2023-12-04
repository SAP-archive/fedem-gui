// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtScale.H"

/*!
 * \TODO Have a look at this for qt4.
  SKE: There is a bug in QSlider (3.0.4) that causes a lag between the values
  you get from the sliderMoved signal and call to value().
  Implemented a hack as a workaround to this.
*/

FFuQtScale::FFuQtScale(QWidget* parent) : QSlider(parent)
{
  myValue = 0;

  this->setWidget(this);

  QObject::connect(this,SIGNAL(valueChanged(int)),this,SLOT(dragged(int)));
  QObject::connect(this,SIGNAL(sliderMoved(int)),this,SLOT(dragged(int)));
  QObject::connect(this,SIGNAL(sliderReleased()),this,SLOT(released()));
}


void FFuQtScale::setValue(int value)
{
  this->blockLibSignals(true);
  this->QSlider::setValue(value);
  this->myValue = value;
  this->blockLibSignals(false);
}


int FFuQtScale::getValue() const
{
  return myValue;
  //return (this->value());
}


void FFuQtScale::setMinMax(int  min, int max)
{
  this->setMinimum(min);
  this->setMaximum(max);
}


void FFuQtScale::getMinMax(int& min, int& max) const
{
  min = this->minimum();
  max = this->maximum();
}


void FFuQtScale::dragged(int value)
{
  if (value == myValue) return;

  myValue = value;
  this->callDragCB(value);
}


void FFuQtScale::released()
{
  this->callReleaseCB();
}
