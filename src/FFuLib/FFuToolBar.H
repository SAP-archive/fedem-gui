// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_TOOL_BAR_H
#define FFU_TOOL_BAR_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include <string>

class FFuaCmdItem;
class FFuToolButton;


class FFuToolBar : virtual public FFuComponentBase
{
public:
  FFuToolBar() {}
  virtual ~FFuToolBar() {}

  // Methods to add a CmdItem which is either a button or a separator.
  // If item is a header, a pop-up is created, parented to this, and
  // item is not book-kept (thus can be deleted). Regular items and header items
  // are book-kept and must not be deleted as long as their menu exists.
  // A menu bar views only txt.
  // A pop-up menu views pixmap and txt;
  // pixmap+txt -> icon(small px) and txt, pixmap only -> (big)pixmap
  virtual FFuToolButton* insertCmdItem(FFuaCmdItem* item) = 0;

  virtual void updateCmdItem(FFuaCmdItem* item, bool sensitivity) = 0;

  void updateSensitivityOnAll() { this->updateCmdItem(NULL,true); }
  void updateToggleOnAll() { this->updateCmdItem(NULL,false); }

  virtual void clearBar() = 0;
  virtual void setBarLabel(const std::string& label) = 0;
  //see FFuaOrientation
  virtual void setBarOrientation(int orientation) = 0;
};

#endif
