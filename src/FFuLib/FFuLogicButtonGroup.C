// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuLogicButtonGroup.H"
#include "FFuLib/FFuButton.H"


FFuLogicButtonGroup::~FFuLogicButtonGroup()
{
  for (ButtonMap::value_type& bm : myButtonMap)
    bm.first->setGroup(NULL);
}


/*!
  Insert the \a aButton into the button group.
*/

void FFuLogicButtonGroup::insert(FFuButton* aButton, int id,
				 FFuComponentBase* component)
{
  if (aButton->getGroup())
    aButton->getGroup()->remove(aButton);

  static int seq_no = -2;
  if (id < -1)
    id = seq_no--;
  else if (id == -1)
    id = myButtonMap.size();

  myButtonMap[aButton] = std::make_pair(id,component);

  aButton->setGroup(this);
  aButton->setGroupToggleCB(FFaDynCB2M(FFuLogicButtonGroup,this,
				       buttonToggledCB,FFuButton*,bool));

  aButton->setGroupArmCB(FFaDynCB1M(FFuLogicButtonGroup,this,
				    buttonArmedCB,FFuButton*));

  aButton->setGroupUnarmCB(FFaDynCB1M(FFuLogicButtonGroup,this,
				      buttonUnarmedCB,FFuButton*));

  aButton->setGroupActivateCB(FFaDynCB1M(FFuLogicButtonGroup,this,
					 buttonActivatedCB,FFuButton*));
}

void FFuLogicButtonGroup::insert(FFuButton* aButton,
                                 FFuComponentBase* component)
{
  this->insert(aButton,-1,component);
}


/*!
  Remove the \a aButton from the button group.
*/

void FFuLogicButtonGroup::remove(FFuButton* aButton)
{
  if (myButtonMap.find(aButton) == myButtonMap.end()) return;

  aButton->setGroup(NULL);
  myButtonMap.erase(aButton);
}


int FFuLogicButtonGroup::getValue() const
{
  for (const ButtonMap::value_type& bm : myButtonMap)
    if (bm.first->getValue())
      return bm.second.first;

  return -1;
}


void FFuLogicButtonGroup::setValue(int id, bool setOn)
{
  for (ButtonMap::value_type& bm : myButtonMap)
    if (bm.second.first == id)
      bm.first->setUIValue(setOn);
    else if (iAmExclusive && (myButtonMap.size() < 3 || setOn))
      bm.first->setUIValue(!setOn);
}


/*!
  Set the value of \a aButton to \a setOn and all other buttons in the group
  to the opposite value, unless more than two buttons and \a setOn is false.
*/

void FFuLogicButtonGroup::setValue(FFuButton* aButton, bool setOn)
{
  if (!iAmExclusive)
    aButton->setUIValue(setOn);
  else for (ButtonMap::value_type& bm : myButtonMap)
    if (bm.first == aButton)
      bm.first->setUIValue(setOn);
    else if (myButtonMap.size() < 3 || setOn)
      bm.first->setUIValue(!setOn);
}


void FFuLogicButtonGroup::setSensitivity(bool sensitivity)
{
  for (ButtonMap::value_type& bm : myButtonMap)
    bm.first->setSensitivity(sensitivity);
}


void FFuLogicButtonGroup::setGroupToggleCB(const FFaDynCB2<int, bool>& aDynCB)
{
  myGroupToggleCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupArmCB(const FFaDynCB1<int>& aDynCB)
{
  myGroupArmCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupUnarmCB(const FFaDynCB1<int>& aDynCB)
{
  myGroupUnarmCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupActivateCB(const FFaDynCB1<int>& aDynCB)
{
  myGroupActivateCB = aDynCB;
}


void FFuLogicButtonGroup::setGroupToggleCB(const FFaDynCB2<FFuComponentBase*,bool>& aDynCB)
{
  myGroupTogglePtrCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupArmCB(const FFaDynCB1<FFuComponentBase*>& aDynCB)
{
  myGroupArmPtrCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupUnarmCB(const FFaDynCB1<FFuComponentBase*>& aDynCB)
{
  myGroupUnarmPtrCB = aDynCB;
}

void FFuLogicButtonGroup::setGroupActivateCB(const FFaDynCB1<FFuComponentBase*>& aDynCB)
{
  myGroupActivatePtrCB = aDynCB;
}


void FFuLogicButtonGroup::buttonToggledCB(FFuButton* aButton, bool setOn)
{
  if (iAmExclusive)
  {
    // Turn every button off exept for the one toggeled on:
    for (ButtonMap::value_type& bm : myButtonMap)
      bm.first->setUIValue(bm.first == aButton);

    // Invoke the callbacks (but only if the selection changes):
    if (aButton->getValue()) // check for TRUE because it is set in UI already
      aButton->invokeToggleCB(setOn = true);
    else
      return;
  }
  else
  {
    aButton->setUIValue(setOn);
    aButton->invokeToggleCB(setOn);
  }

  myGroupToggleCB.invoke(myButtonMap[aButton].first, setOn);
  myGroupTogglePtrCB.invoke(myButtonMap[aButton].second, setOn);
}

void FFuLogicButtonGroup::buttonArmedCB(FFuButton* aButton)
{
  myGroupArmCB.invoke(myButtonMap[aButton].first);
  myGroupArmPtrCB.invoke(myButtonMap[aButton].second);
}

void FFuLogicButtonGroup::buttonUnarmedCB(FFuButton* aButton)
{
  myGroupUnarmCB.invoke(myButtonMap[aButton].first);
  myGroupUnarmPtrCB.invoke(myButtonMap[aButton].second);
}

void FFuLogicButtonGroup::buttonActivatedCB(FFuButton* aButton)
{
  myGroupActivateCB.invoke(myButtonMap[aButton].first);
  myGroupActivatePtrCB.invoke(myButtonMap[aButton].second);
}
