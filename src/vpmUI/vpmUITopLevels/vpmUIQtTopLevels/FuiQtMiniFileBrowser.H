// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_MINI_FILE_BROWSER_H
#define FUI_QT_MINI_FILE_BROWSER_H

#include "vpmUI/vpmUITopLevels/FuiMiniFileBrowser.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"


class FuiQtMiniFileBrowser : public FFuQtTopLevelShell, public FuiMiniFileBrowser
{
public:
  FuiQtMiniFileBrowser(int xpos, int ypos, int width, int height,
                       const char* title="Result File Browser",
                       const char* name="FuiQtMiniFileBrowser");
  virtual ~FuiQtMiniFileBrowser() {}
};

#endif
