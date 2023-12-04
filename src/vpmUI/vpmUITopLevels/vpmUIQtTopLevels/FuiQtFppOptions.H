// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTFPPOPTIONS_H
#define FUIQTFPPOPTIONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiFppOptions.H"

// Typedefs and fwd declarations

class FuiQtFppOptions: public FFuQtTopLevelShell,
			public FuiFppOptions
{
public:
  FuiQtFppOptions(QWidget* parent=0,int xpos=100,int ypos=100,
			int width=100,int height=100,
			const char* title= "",
			const char* name = "FuiQtFppOptions");
  virtual ~FuiQtFppOptions();

// Operations
private:
  virtual void setSensitivity(bool isSensitive) {
    FuiFppOptions::setSensitivity(isSensitive);}

// Attributes 
private: 
 

};
/////////////////////////////////////////////////////////////////////////////

#endif
