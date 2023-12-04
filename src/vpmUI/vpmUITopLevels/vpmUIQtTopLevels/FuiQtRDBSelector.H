// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_RDB_SELECTOR_H
#define FUI_QT_RDB_SELECTOR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiRDBSelector.H"


class FuiQtRDBSelector : public FFuQtTopLevelShell, public FuiRDBSelector
{
public:
  FuiQtRDBSelector(int xpos, int ypos, int width, int height,
                   const char* title, const char* name);
  virtual ~FuiQtRDBSelector() {}
};

#endif
