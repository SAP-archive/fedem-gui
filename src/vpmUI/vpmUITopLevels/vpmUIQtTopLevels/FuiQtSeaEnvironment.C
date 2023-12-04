// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtSeaEnvironment.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiSeaEnvironment* FuiSeaEnvironment::create(int xpos, int ypos,
					     int width, int height,
					     const char* title,
					     const char* name)
{
  return new FuiQtSeaEnvironment(0,xpos,ypos,width,height,title,name);
}


FuiQtSeaEnvironment::FuiQtSeaEnvironment(QWidget* parent,
					 int xpos, int ypos,
					 int width, int height,
					 const char* title,
					 const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  this->waterDensityField  = new FFuQtLabelField(this);
  this->meanSeaLevelField  = new FFuQtLabelField(this);
  this->seaDepthField      = new FFuQtLabelField(this);

  this->gravitationFrame  = new FFuQtLabelFrame(this);
  this->gravitationVector = new FuiQt3DPoint(this,0,0,0,0,"g",false);

  this->waveDirectionFrame  = new FFuQtLabelFrame(this);
  this->waveDirectionVector = new FuiQt3DPoint(this,0,0,0,0,"Xw",false);

  this->marineGrowthFrame           = new FFuQtLabelFrame(this);
  this->marineGrowthDensityField    = new FFuQtLabelField(this);
  this->marineGrowthThicknessField  = new FFuQtLabelField(this);
  this->marineGrowthUpperLimitField = new FFuQtLabelField(this);
  this->marineGrowthLowerLimitField = new FFuQtLabelField(this);

  this->waveLabel      = new FFuQtLabel(this);
  this->waveQueryField = new FuiQtQueryInputField(this);

  this->currLabel      = new FFuQtLabel(this);
  this->currQueryField = new FuiQtQueryInputField(this);

  this->currDirLabel      = new FFuQtLabel(this);
  this->currDirQueryField = new FuiQtQueryInputField(this);

  this->currScaleLabel      = new FFuQtLabel(this);
  this->currScaleQueryField = new FuiQtQueryInputField(this);

  this->hdfScaleLabel      = new FFuQtLabel(this);
  this->hdfScaleQueryField = new FuiQtQueryInputField(this);

  this->dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
