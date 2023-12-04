// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtJointTabAdvanced.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"

FuiQtJointTabAdvanced::FuiQtJointTabAdvanced(QWidget* parent, int xpos, int ypos,
                 int width, int height, const char* name)
  :FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myRotFormulationFrame = new FFuQtLabelFrame(this);
  myRotFormulationLabel = new FFuQtLabel(this);
  myRotFormulationMenu  = new FFuQtOptionMenu(this);
  myRotSequenceLabel    = new FFuQtLabel(this);
  myRotExplainLabel     = new FFuQtLabel(this);
  myRotSequenceMenu     = new FFuQtOptionMenu(this);

  mySpringCplFrame      = new FFuQtLabelFrame(this);
  myTranSpringCplLabel  = new FFuQtLabel(this);
  myTranSpringCplMenu   = new FFuQtOptionMenu(this);
  myRotSpringCplLabel   = new FFuQtLabel(this);
  myRotSpringCplMenu    = new FFuQtOptionMenu(this);

  this->initWidgets();
}

FuiQtJointTabAdvanced::~FuiQtJointTabAdvanced()
{
  
}
