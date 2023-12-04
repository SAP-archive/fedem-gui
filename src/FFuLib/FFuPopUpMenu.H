// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_POP_UP_MENU_H
#define FFU_POP_UP_MENU_H

#include "FFuLib/FFuMenuBase.H"


class FFuPopUpMenu : virtual public FFuMenuBase
{
public:
  FFuPopUpMenu() {}
  virtual ~FFuPopUpMenu() {}

  virtual FFuaCmdItem* executeAtCursorPos() = 0;
};

#endif
