// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_MULT_UI_COMPONENT_H
#define FUI_MULT_UI_COMPONENT_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaTypeCheck/FFaTypeCheck.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


class FFuMultUIComponent : virtual public FFuComponentBase
{
  Fmd_BASE_HEADER_INIT();

public:
  FFuMultUIComponent();
  virtual ~FFuMultUIComponent() {}

public:
  // distributing popped up/down to/from mem
  void setAppearanceOnScreenCB(const FFaDynCB1<bool>& cb) { appearanceCB = cb; }

protected:
  // Virtual method to be reimplemented in subclasses.
  // It is supposed to set size and position on the widgets of the component.
  // Invoked each time the component is resized.
  virtual void placeWidgets(int,int) {}

  // These methods are called every time a UI-component pops up/down,
  // also from an iconified position.
  // Reimplement if you want to do something on that event.
  virtual void onPoppedUp() {}
  virtual void onPoppedDown() {}

  // to/from memory only
  // called every time a ui appears on the screen (not from icon)
  virtual void onPoppedUpFromMem() {}
  // called when a ui is on its way to the memory (hide)
  virtual void onPoppedDownToMem() {}

  void onPoppedUpFromMemLoc() {
    this->invokeAppearanceCB(true);
    this->onPoppedUpFromMem();}
  void onPoppedDownToMemLoc() {
    this->invokeAppearanceCB(false);
    this->onPoppedDownToMem();}

  // A conveinence method to calculate positions of
  // "Grid lines" to be used when positioning widgets.
  // REL_OFFSET means "offset * (size/relativeOffsetBase)"
  // FROM_START means "offset"
  // FROM_END means "size - offset"

  enum { REL_OFFSET, FROM_START, FROM_END };
  static int getGridLinePos(int size, int offset,
                            int offsetType = REL_OFFSET,
                            int relativeOffsetBase = 1000);

  // Methods to return commonly used sizes :

  virtual int getBorder();

  void invokeAppearanceCB(bool popup) { appearanceCB.invoke(popup); }

private:
  FFaDynCB1<bool> appearanceCB;
};

#endif
