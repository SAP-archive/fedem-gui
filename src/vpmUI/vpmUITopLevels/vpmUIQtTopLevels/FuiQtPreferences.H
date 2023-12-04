// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTPREFERENCES_H  
#define FUIQTPREFERENCES_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiPreferences.H"


class FuiQtPreferences : public FFuQtTopLevelShell, public FuiPreferences
{
public:
  FuiQtPreferences(QWidget* parent = 0,
		   int xpos  = 100, int ypos   = 100,
		   int width = 100, int height = 100,
		   const char* title= "Fedem",
		   const char* name = "FuiQtPreferences");

  virtual ~FuiQtPreferences();

private:
  virtual void setSensitivity(bool sen) { FuiPreferences::setSensitivity(sen); }
};

#endif
