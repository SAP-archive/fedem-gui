// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTCTRLMODELLER_H
#define FUIQTCTRLMODELLER_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMDIWindow.H"
#include "vpmUI/vpmUITopLevels/FuiCtrlModeller.H"

class FuiQtCtrlModeller: public FFuQtMDIWindow, public FuiCtrlModeller
{
public:
  FuiQtCtrlModeller(QWidget* parent=0,int xpos  = 100, int ypos   = 100,
		    int width = 100, int height = 100,
		    const char *title="Control System",
		    const char* name="FuiCtrlModeller");

  virtual ~FuiQtCtrlModeller(){}

};

#endif
