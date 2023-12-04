// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_PUSH_BUTTON_H
#define FFU_PUSH_BUTTON_H

#include "FFuLib/FFuButton.H"


class FFuPushButton : virtual public FFuButton
{
public:
  FFuPushButton() {}
  virtual ~FFuPushButton() {}
};

#endif
