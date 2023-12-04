// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_SPIN_BOX_H
#define FFU_SPIN_BOX_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <string>


class FFuSpinBox : virtual public FFuComponentBase
{
public:
  FFuSpinBox() {}
  virtual ~FFuSpinBox() {}

  virtual int getIntValue() = 0;
  virtual void setIntValue(int value) = 0;

  // text prefixed/suffixed to the number, e.g. a unit
  virtual std::string getPrefixString() = 0;
  virtual void setPrefixString(const std::string& prefix)=0;

  virtual std::string getSuffixString()=0;
  virtual void setSuffixString(const std::string& suffix)=0;

  // Allow to "wrap around" from max to min and vice versa
  virtual void setWrapping(bool on)=0;
  virtual bool hasWrapping()=0;

  enum {ARROWS, PLUS_MINUS};
  virtual void setButtonSymbol(int symbol)=0;
  virtual int getButtonSymbol()=0;

  virtual int getMinValue()=0;
  virtual int getMaxValue()=0;
  virtual void setMinMax(int min, int max)=0;

  virtual void setStepSize(int step)=0;
  virtual int getStepSize()=0;

  virtual void stepOneUp()=0;
  virtual void stepOneDown()=0;

  void setValueChangedCB(const FFaDynCB1<int>& cb) { myValueChangedCB = cb; }

protected:
  void callValueChangedCB(int value) { myValueChangedCB.invoke(value); }

private:
  FFaDynCB1<int> myValueChangedCB;
};

#endif
