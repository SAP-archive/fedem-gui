// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_LINK_RAM_SETTINGS_H
#define FUI_QT_LINK_RAM_SETTINGS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiLinkRamSettings.H"


class FuiQtLinkRamSettings : public FFuQtTopLevelShell, public FuiLinkRamSettings
{
public:
  FuiQtLinkRamSettings(QWidget* parent=0,
		       int xpos=100,int ypos=100,
		       int width=100,int height=100,
		       const char* title= "",
		       const char* name = "FuiQtLinkRamSettings");
  virtual ~FuiQtLinkRamSettings() {}

private:
  virtual void setSensitivity(bool) {}
};

#endif
