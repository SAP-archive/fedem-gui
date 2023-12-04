// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtBeamPropHydro.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"


FuiQtBeamPropHydro::FuiQtBeamPropHydro(QWidget* parent,
				       int xpos, int ypos,
				       int width,int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myBeamHydroToggleButton = new FFuQtToggleButton(this);
  myBeamHydroDbField      = new FFuQtLabelField(this);
  myBeamHydroDdField      = new FFuQtLabelField(this);
  myBeamHydroCdField      = new FFuQtLabelField(this);
  myBeamHydroCaField      = new FFuQtLabelField(this);
  myBeamHydroCmField      = new FFuQtLabelField(this);
  myBeamHydroCdAxialField = new FFuQtLabelField(this);
  myBeamHydroCaAxialField = new FFuQtLabelField(this);
  myBeamHydroCmAxialField = new FFuQtLabelField(this);
  myBeamHydroCdSpinField  = new FFuQtLabelField(this);
  myBeamHydroDiField      = new FFuQtLabelField(this);

  this->initWidgets();
}
