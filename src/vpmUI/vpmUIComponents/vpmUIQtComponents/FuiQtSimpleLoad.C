// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtSimpleLoad.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"


FuiQtSimpleLoad::FuiQtSimpleLoad(QWidget* parent, int xpos, int ypos,
                 int width, int height, const char* name)
  :FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myFrame       = new FFuQtLabelFrame(this);
  myEngineField = new FuiQtQueryInputField(this);

  this->initWidgets();
}

FuiQtSimpleLoad::~FuiQtSimpleLoad()
{
  
}
