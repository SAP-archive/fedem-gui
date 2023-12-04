// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_ANIM_EXPORT_SETUP_H
#define FUI_QT_ANIM_EXPORT_SETUP_H

#include "FFuLib/FFuQtBaseClasses/FFuQtModalDialog.H"
#include "vpmUI/vpmUITopLevels/FuiRepeatCurve.H"


class FuiQtRepeatCurve : public FFuQtModalDialog,
                         virtual public FuiRepeatCurve
{
public:
  FuiQtRepeatCurve(int xpos = 100, int ypos  = 100,
		   int width= 100, int height= 100,
		   const char* title= "Fedem",
		   const char* name = "FuiQtRepeatCurve");
  virtual ~FuiQtRepeatCurve() {}
};

#endif
