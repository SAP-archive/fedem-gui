// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTMODELPREFERENCES_H
#define FUIQTMODELPREFERENCES_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiModelPreferences.H"


class FuiQtModelPreferences : public FFuQtTopLevelShell,
			      public FuiModelPreferences
{
public:
  FuiQtModelPreferences(QWidget* parent = 0,
			int xpos =100, int ypos  =100,
			int width=100, int height=100,
			const char* title= "Fedem",
			const char* name = "FuiQtModelPreferences");
  virtual ~FuiQtModelPreferences() {}

private:
  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiModelPreferences::setSensitivity(isSensitive);
  }
};

#endif
