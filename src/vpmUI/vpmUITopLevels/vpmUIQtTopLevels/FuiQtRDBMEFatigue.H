// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_RDB_ME_FATIGUE_H
#define FUI_QT_RDB_ME_FATIGUE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiRDBMEFatigue.H"


class FuiQtRDBMEFatigue : public FFuQtTopLevelShell, public FuiRDBMEFatigue
{
public:
  FuiQtRDBMEFatigue(int xpos, int ypos, int width, int height,
                    const char* title, const char* name);
  virtual ~FuiQtRDBMEFatigue() {}

private:
  virtual void onCopyDataClicked();
};

#endif
