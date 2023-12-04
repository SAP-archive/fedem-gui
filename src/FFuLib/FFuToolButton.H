// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_TOOL_BUTTON_H
#define FFU_TOOL_BUTTON_H

#include "FFuLib/FFuButton.H"

class FFuaCmdItem;


class FFuToolButton : virtual public FFuButton
{
public:
  FFuToolButton() : cmdItem(NULL), activeCmdItem(NULL) {}
  virtual ~FFuToolButton() {}

  FFuaCmdItem* getCmdItem() { return cmdItem; }

  virtual void updateButton(bool sensitivity) = 0;
  void updateSensitivity() { this->updateButton(true); }

protected:
  FFuaCmdItem* cmdItem;//header or regular
  FFuaCmdItem* activeCmdItem;// regular; for sgl toolbuttons, cmdItem = activeCmdItem
};

#endif
