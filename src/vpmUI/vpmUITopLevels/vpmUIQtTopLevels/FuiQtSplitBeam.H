// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_SPLIT_BEAM_H
#define FUI_QT_SPLIT_BEAM_H

#include "FFuLib/FFuQtBaseClasses/FFuQtModalDialog.H"
#include "vpmUI/vpmUITopLevels/FuiSplitBeam.H"


class FuiQtSplitBeam : public FFuQtModalDialog,
                       virtual public FuiSplitBeam
{
public:
  FuiQtSplitBeam(int xpos = 100, int ypos  = 100,
		 int width= 100, int height= 100,
		 const char* title= "Fedem",
		 const char* name = "FuiQtSplitBeam");
  virtual ~FuiQtSplitBeam() {}
};

#endif
