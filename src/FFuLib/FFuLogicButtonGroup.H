// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_LOGIC_BUTTON_GROUP_H
#define FFU_LOGIC_BUTTON_GROUP_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"

#include <cstddef> // To ensure NULL is defined
#include <map>

class FFuButton;
class FFuComponentBase;


/*!
  \brief Logic grouping of buttons (e.g., toggle-, radio- and push-buttons).

  A FFuButton is inserted in the FFuLogicButtonGroup object.

  \author Jens Lien
*/

class FFuLogicButtonGroup
{
  typedef std::pair<int,FFuComponentBase*> ButtonData;
  typedef std::map<FFuButton*,ButtonData>  ButtonMap;

public:
  FFuLogicButtonGroup(bool exclusive = true) : iAmExclusive(exclusive) {}
  ~FFuLogicButtonGroup();

  void insert(FFuButton* aButton, int id = -1, FFuComponentBase* comp = NULL);
  void insert(FFuButton* aButton, FFuComponentBase* comp);
  void remove(FFuButton* aButton);

  int  getValue() const;
  void setValue(int id, bool setOn = true);
  void setValue(FFuButton* aButton, bool setOn);
  void setSensitivity(bool sensitivity);

  void setGroupToggleCB(const FFaDynCB2<int,bool>& aDynCB);
  void setGroupArmCB(const FFaDynCB1<int>& aDynCB);
  void setGroupUnarmCB(const FFaDynCB1<int>& aDynCB);
  void setGroupActivateCB(const FFaDynCB1<int>& aDynCB);

  void setGroupToggleCB(const FFaDynCB2<FFuComponentBase*,bool>& aDynCB);
  void setGroupArmCB(const FFaDynCB1<FFuComponentBase*>& aDynCB);
  void setGroupUnarmCB(const FFaDynCB1<FFuComponentBase*>& aDynCB);
  void setGroupActivateCB(const FFaDynCB1<FFuComponentBase*>& aDynCB);

  void setExclusive(bool exclusive) { iAmExclusive = exclusive; }

protected:
  void buttonToggledCB(FFuButton* aButton, bool setOn);
  void buttonArmedCB(FFuButton* aButton);
  void buttonUnarmedCB(FFuButton* aButton);
  void buttonActivatedCB(FFuButton* aButton);

private:
  ButtonMap myButtonMap;

  FFaDynCB2<int,bool> myGroupToggleCB;
  FFaDynCB1<int>      myGroupArmCB;
  FFaDynCB1<int>      myGroupUnarmCB;
  FFaDynCB1<int>      myGroupActivateCB;

  FFaDynCB2<FFuComponentBase*,bool> myGroupTogglePtrCB;
  FFaDynCB1<FFuComponentBase*>      myGroupArmPtrCB;
  FFaDynCB1<FFuComponentBase*>      myGroupUnarmPtrCB;
  FFaDynCB1<FFuComponentBase*>      myGroupActivatePtrCB;

  bool iAmExclusive;
};

#endif
