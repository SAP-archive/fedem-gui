// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_RADIO_BUTTON_H
#define FFU_RADIO_BUTTON_H

#include "FFuLib/FFuButton.H"


class FFuRadioButton : virtual public FFuButton
{
public:
  FFuRadioButton() {}
  virtual ~FFuRadioButton() {}

  // To be implemented in the UI Lib dependent code:
  virtual bool getValue() const = 0;
};

#endif
