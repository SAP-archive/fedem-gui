// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTGAGEOPTIONS_H
#define FUIQTGAGEOPTIONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiGageOptions.H"

// Typedefs and fwd declarations

class FuiQtGageOptions: public FFuQtTopLevelShell,
			public FuiGageOptions
{
public:
  FuiQtGageOptions(QWidget* parent=0,int xpos=100,int ypos=100,
			int width=100,int height=100,
			const char* title= "",
			const char* name = "FuiQtGageOptions");
  virtual ~FuiQtGageOptions();

// Operations
private:
  virtual void setSensitivity(bool isSensitive) {
    FuiGageOptions::setSensitivity(isSensitive);}

// Attributes 
private: 
 

};
/////////////////////////////////////////////////////////////////////////////

#endif
