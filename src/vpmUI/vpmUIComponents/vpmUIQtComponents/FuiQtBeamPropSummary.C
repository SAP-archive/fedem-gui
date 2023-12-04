// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtBeamPropSummary.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"


FuiQtBeamPropSummary::FuiQtBeamPropSummary(QWidget* parent,
					   int xpos, int ypos,
					   int width,int height,
					   const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myCrossSectionTypeLabel = new FFuQtLabel(this);
  myCrossSectionTypeMenu  = new FFuQtOptionMenu(this);
  myMaterialDefLabel      = new FFuQtLabel(this);
  myMaterialDefField      = new FuiQtQueryInputField(this);
  myDefinitionFrame       = new FFuQtLabelFrame(this);
  myDoField               = new FFuQtLabelField(this);
  myDiField               = new FFuQtLabelField(this);
  myImage                 = new FFuQtLabel(this);
  myGEAField              = new FFuQtLabelField(this);
  myGEIyyField            = new FFuQtLabelField(this);
  myGEIzzField            = new FFuQtLabelField(this);
  myGItField              = new FFuQtLabelField(this);
  myGmlField              = new FFuQtLabelField(this);
  myGIpField              = new FFuQtLabelField(this);

  myDependencyFrame       = new FFuQtLabelFrame(this);
  myDependencyButton      = new FFuQtToggleButton(this);
  myAField                = new FFuQtLabelField(this);
  myIyField               = new FFuQtLabelField(this);
  myIzField               = new FFuQtLabelField(this);
  myIpField               = new FFuQtLabelField(this);

  myShearKFrame           = new FFuQtLabelFrame(this);
  myShearKYField          = new FFuQtLabelField(this);
  myShearKZField          = new FFuQtLabelField(this);
  myShearGAsyField        = new FFuQtLabelField(this);
  myShearGAszField        = new FFuQtLabelField(this);
  myShearSFrame           = new FFuQtLabelFrame(this);
  myShearSYField          = new FFuQtLabelField(this);
  myShearSZField          = new FFuQtLabelField(this);

  this->initWidgets();
}
