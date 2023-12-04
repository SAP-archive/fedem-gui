// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_MENU_BASE_H
#define FFU_QT_MENU_BASE_H

#include "FFuLib/FFuMenuBase.H"


class FFuQtMenuBase : virtual public FFuMenuBase
{
public:
  FFuQtMenuBase() {}
  virtual ~FFuQtMenuBase() {}

  virtual bool insertCmdItem(FFuaCmdItem* item);
  virtual void updateCmdItem(FFuaCmdItem* item, bool sensitivity);
};

#endif
