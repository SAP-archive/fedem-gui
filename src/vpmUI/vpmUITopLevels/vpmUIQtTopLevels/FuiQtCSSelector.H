// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CS_SELECTOR_H
#define FUI_QT_CS_SELECTOR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiCSSelector.H"


class FuiQtCSSelector : public FFuQtTopLevelShell, public FuiCSSelector
{
public:
  FuiQtCSSelector(int xpos, int ypos, int width, int height,
                  const char* title, const char* name);
  virtual ~FuiQtCSSelector() {}
};

#endif
