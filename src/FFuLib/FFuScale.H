// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_SCALE_H
#define FFU_SCALE_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


class FFuScale : virtual public FFuComponentBase
{
public:
  FFuScale() {}
  virtual ~FFuScale() {}

  virtual void setValue(int value) = 0;
  virtual int  getValue() const = 0;

  virtual void setMinMax(int  min, int  max) = 0;
  virtual void getMinMax(int& min, int& max) const = 0;

  void setDragCB(const FFaDynCB1<int>& cb) { myDragCB = cb; }
  void setReleaseCB(const FFaDynCB0& cb) { myReleaseCB = cb; }

protected:
  // Should be called on appropriate times by UI-lib dependent subclass
  void callDragCB(int value) { myDragCB.invoke(value); }
  void callReleaseCB() { myReleaseCB.invoke(); }

private:
  FFaDynCB1<int> myDragCB;
  FFaDynCB0      myReleaseCB;
};

#endif
