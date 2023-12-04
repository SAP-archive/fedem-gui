// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_ANIMATION_CONTROL_H
#define FUI_QT_ANIMATION_CONTROL_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiAnimationControl.H"


class FuiQtAnimationControl : public FFuQtTopLevelShell, public FuiAnimationControl
{
public:
  FuiQtAnimationControl(int xpos, int ypos, int width, int height,
                        const char* title, const char* name);
  virtual ~FuiQtAnimationControl() {}

private:
  virtual void setSensitivity(bool isSensitive) {
    FuiAnimationControl::setSensitivity(isSensitive);}
};

#endif
