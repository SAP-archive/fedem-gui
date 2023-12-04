// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_VIEW_SETTINGS_H
#define FUI_QT_VIEW_SETTINGS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiViewSettings.H"


class FuiQtViewSettings : public FFuQtTopLevelShell, public FuiViewSettings
{
public:
  FuiQtViewSettings(int xpos, int ypos, int width, int height,
                    const char* title, const char* name);
  virtual ~FuiQtViewSettings() {}
};

#endif
