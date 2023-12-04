// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_MENU_BAR_H
#define FFU_MENU_BAR_H

#include "FFuLib/FFuMenuBase.H"


class FFuMenuBar : virtual public FFuMenuBase
{
public:
  FFuMenuBar() {}
  virtual ~FFuMenuBar() {}
};

#endif
