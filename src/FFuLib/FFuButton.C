// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuButton.H"
#include "FFuLib/FFuLogicButtonGroup.H"


FFuButton::~FFuButton()
{
  if (myButtonGroup) myButtonGroup->remove(this);
}


void FFuButton::setValue(bool trueOrFalse)
{
  if (myButtonGroup)
    myButtonGroup->setValue(this,trueOrFalse);
  else
    this->setUIValue(trueOrFalse);
}


void FFuButton::callToggleCB(bool value)
{
  if (myButtonGroup)
    myGroupToggleCB.invoke(this,value);
  else
    myToggleCB.invoke(value);
}


void FFuButton::setArmCB(const FFaDynCB0& aDynCB)
{
  myArmCB = aDynCB;
}

void FFuButton::setUnarmCB(const FFaDynCB0& aDynCB)
{
  myUnarmCB = aDynCB;
}

void FFuButton::setActivateCB(const FFaDynCB0& aDynCB)
{
  myActivateCB = aDynCB;
}

void FFuButton::setToggleCB(const FFaDynCB1<bool>& aDynCB)
{
  myToggleCB = aDynCB;
}


void FFuButton::callArmCB()
{
  myArmCB.invoke();
  if (myButtonGroup)
    myGroupArmCB.invoke(this);
}

void FFuButton::callUnarmCB()
{
  myUnarmCB.invoke();
  if (myButtonGroup)
    myGroupUnarmCB.invoke(this);
}

void FFuButton::callActivateCB()
{
  myActivateCB.invoke();
  if (myButtonGroup)
    myGroupActivateCB.invoke(this);
}


void FFuButton::setGroupToggleCB(const FFaDynCB2<FFuButton*, bool>& aDynCB)
{
  myGroupToggleCB = aDynCB;
}

void FFuButton::setGroupArmCB(const FFaDynCB1<FFuButton*>& aDynCB)
{
  myGroupArmCB = aDynCB;
}

void FFuButton::setGroupUnarmCB(const FFaDynCB1<FFuButton*>& aDynCB)
{
  myGroupUnarmCB = aDynCB;
}

void FFuButton::setGroupActivateCB(const FFaDynCB1<FFuButton*>& aDynCB)
{
  myGroupActivateCB = aDynCB;
}
