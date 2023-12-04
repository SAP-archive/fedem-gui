// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_TOGGLE_BUTTON_H
#define FFU_TOGGLE_BUTTON_H

#include "FFuLib/FFuButton.H"


class FFuToggleButton : virtual public FFuButton
{
public:
  FFuToggleButton() {}
  virtual ~FFuToggleButton() {}

  // To be implemented in the UI Lib dependent code:
  virtual bool getValue() const = 0;

  // tristate support
  virtual int  getTristateValue() const = 0;
  virtual void useUITristate(bool y = true) = 0;
  virtual void setUITristateValue(int value) = 0;
};

#endif
