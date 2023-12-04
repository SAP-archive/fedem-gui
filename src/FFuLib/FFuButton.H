// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_BUTTON_H
#define FFU_BUTTON_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLogicButtonGroup;


/*!
  \brief The FFuButton class is an abstract base class for buttons.

  FFuButton provides interface for FFuLogicButtonGroup.
  Toggle callbacks are also set in this class.

  \author Jens Lien
*/

class FFuButton : virtual public FFuComponentBase
{
public:
  FFuButton() : myButtonGroup(NULL) {}
  virtual ~FFuButton();

  virtual void setPixMap(const char** pixmap) = 0;
  virtual void setLabel (const char* label) = 0;

  virtual void setValue(bool onOrOff);
  virtual bool getValue() const { return false; }

  // Toggle func (if you want the tool or push button to have toggle func)
  virtual void setToggleAble(bool) {}
  virtual bool getToggleAble() { return false; }
  virtual bool getToggle() { return false; }

  void setArmCB(const FFaDynCB0& aDynCB); //pressed
  void setUnarmCB(const FFaDynCB0& aDynCB); //released
  void setActivateCB(const FFaDynCB0& aDynCB);//clicked
  void setToggleCB(const FFaDynCB1<bool>& aDynCB);

protected:
  // These are to be called on appropriate times from subclass
  void callArmCB();
  void callUnarmCB();
  void callActivateCB();
  void callToggleCB(bool value);

public:
  // These are to be called from FFuLogicButtonGroup only
  void invokeToggleCB(bool value) { myToggleCB.invoke(value); }
  void setGroupToggleCB(const FFaDynCB2<FFuButton*,bool>& aDynCB);
  void setGroupArmCB(const FFaDynCB1<FFuButton*>& aDynCB);
  void setGroupUnarmCB(const FFaDynCB1<FFuButton*>& aDynCB);
  void setGroupActivateCB(const FFaDynCB1<FFuButton*>& aDynCB);

  void setGroup(FFuLogicButtonGroup* group) { myButtonGroup = group; }
  FFuLogicButtonGroup* getGroup() const { return myButtonGroup; }

  virtual void setUIValue(bool) {}

private:
  FFaDynCB1<bool> myToggleCB;
  FFaDynCB0       myArmCB;
  FFaDynCB0       myUnarmCB;
  FFaDynCB0       myActivateCB;

  FFaDynCB2<FFuButton*,bool> myGroupToggleCB;
  FFaDynCB1<FFuButton*>      myGroupArmCB;
  FFaDynCB1<FFuButton*>      myGroupUnarmCB;
  FFaDynCB1<FFuButton*>      myGroupActivateCB;

  FFuLogicButtonGroup* myButtonGroup;
};

#endif
