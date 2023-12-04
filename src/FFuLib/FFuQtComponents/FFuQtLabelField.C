// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"

FFuQtLabelField::FFuQtLabelField(QWidget* parent ,
				 int xpos , int ypos ,
				 int width, int height,
				 const char* name)
  :FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  this->myLabel = new FFuQtLabel(this);
  this->myField = new FFuQtIOField(this);
}
 
FFuLabelField * FFuLabelField::create(FFuComponentBase * parent)
{
  return new FFuQtLabelField(dynamic_cast<QWidget*>(parent));
}
