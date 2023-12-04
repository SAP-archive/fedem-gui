// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTMODELLER_H
#define FUIQTMODELLER_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMDIWindow.H"
#include "vpmUI/vpmUITopLevels/FuiModeller.H"


class FuiQtModeller: public FFuQtMDIWindow, public FuiModeller
{
public:
  FuiQtModeller(QWidget* parent=0,int xpos  = 100, int ypos   = 100,
		int width = 100, int height = 100,
		const char *title="Modeler",
		const char* name="FuiModeller");
  virtual ~FuiQtModeller(){}


};

#endif
