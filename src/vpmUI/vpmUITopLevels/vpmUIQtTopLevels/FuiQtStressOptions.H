// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTSTRESSOPTIONS_H  
#define FUIQTSTRESSOPTIONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiStressOptions.H"

// Typedefs and fwd declarations

class FuiQtStressOptions: public FFuQtTopLevelShell,
			  public FuiStressOptions
{
public:
  FuiQtStressOptions(QWidget* parent=0,int xpos=100,int ypos=100,
		       int width=330,int height=250,
		       const char* title= "Fedem",
		       const char* name = "FuiQtStressOptions");
  virtual ~FuiQtStressOptions();


 
  // Operations
 
private:
  virtual void setSensitivity(bool sens)
    { FuiStressOptions::setSensitivity( sens);}

  // Attributes 

private: 

};
/////////////////////////////////////////////////////////////////////////////
#endif
