// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

//#define QT3_SUPPORT // temporary
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"


FuiQt3DPoint::FuiQt3DPoint(QWidget* parent,
			   int xpos,
			   int ypos,
			   int width,
			   int height,
			   const char* name,
			   bool refMenu)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  this->myFrame = new FFuQtFrame(this);
  if (refMenu) {
    this->myRefLabel = new FFuQtLabel(this);
    this->myRefMenu  = new FFuQtOptionMenu(this);
  }
  else {
    this->myRefLabel = 0;
    this->myRefMenu  = 0;
  }
  this->myZLabel = new FFuQtLabel  (this);
  this->myYLabel = new FFuQtLabel  (this);
  this->myXLabel = new FFuQtLabel  (this);
  this->myXField = new FFuQtIOField(this);
  this->myYField = new FFuQtIOField(this);
  this->myZField = new FFuQtIOField(this);

  this->init();
}
