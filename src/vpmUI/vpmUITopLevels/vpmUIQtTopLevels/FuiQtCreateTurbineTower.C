// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtCreateTurbineTower.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtSpinBox.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiCreateTurbineTower* FuiCreateTurbineTower::create(int xpos, int ypos,
							   int width, int height,
							   const char* title,
							   const char* name)
{
  return new FuiQtCreateTurbineTower(0,xpos,ypos,width,height,title,name);
}


FuiQtCreateTurbineTower::FuiQtCreateTurbineTower(QWidget* parent,
						       int xpos, int ypos,
						       int width, int height,
						       const char* title,
						       const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name,Qt::MSWindowsFixedSizeDialogHint)
{
  this->headerImage         = new FFuQtLabel(this);
  this->modelImage          = new FFuQtLabel(this);
  this->towerGeometryFrame  = new FFuQtLabelFrame(this);
  this->towerGeometryD1Field = new FFuQtLabelField(this);
  this->towerGeometryD2Field = new FFuQtLabelField(this);
  this->towerGeometryM1Field = new FFuQtLabelField(this);
  this->towerGeometryH1Field = new FFuQtLabelField(this);
  this->towerGeometryH2Field = new FFuQtLabelField(this);
  this->towerGeometryWallThicknessField = new FFuQtLabelField(this);
  this->towerMeshFrame        = new FFuQtLabelFrame(this);
  this->towerMeshN1Field      = new FFuQtLabelField(this);
  this->towerMeshN2Field      = new FFuQtLabelField(this);
  this->towerMaterialFrame    = new FFuQtLabelFrame(this);
  this->towerMaterialMenu     = new FuiQtQueryInputField(this);
  this->towerMaterialRhoField = new FFuQtLabelField(this);
  this->towerMaterialEField  = new FFuQtLabelField(this);
  this->towerMaterialNuField = new FFuQtLabelField(this);
  this->towerMaterialGField = new FFuQtLabelField(this);
  this->notesImage          = new FFuQtLabel(this);
  this->notesLabel          = new FFuQtLabel(this);
  this->notesSeparator      = new FFuQtLabelFrame(this);
  this->notesText           = new FFuQtLabel(this);
  this->dialogButtons       = new FFuQtDialogButtons(this);

  this->initWidgets();
}
