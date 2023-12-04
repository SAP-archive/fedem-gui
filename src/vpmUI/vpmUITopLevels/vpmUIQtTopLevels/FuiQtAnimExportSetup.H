// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTANIMEXPORTSETUP_H
#define FUIQTANIMEXPORTSETUP_H

#include "FFuLib/FFuQtBaseClasses/FFuQtModalDialog.H"
#include "vpmUI/vpmUITopLevels/FuiAnimExportSetup.H"


class FuiQtAnimExportSetup : public FFuQtModalDialog,
			     virtual public FuiAnimExportSetup
{
public:
  FuiQtAnimExportSetup(int xpos = 100, int ypos  = 100,
		       int width= 100, int height= 100,
		       const char* title= "Fedem",
		       const char* name = "FuiQtAnimExportSetup");
  virtual ~FuiQtAnimExportSetup() {}
};

#endif
