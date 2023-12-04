// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUQTLABELFIELD_H
#define FFUQTLABELFIELD_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "FFuLib/FFuLabelField.H"

class FFuQtLabelField : public FFuQtMultUIComponent, public FFuLabelField
{
public :
  FFuQtLabelField(QWidget* parent = 0,
		  int xpos = 100, int ypos  = 100,
		  int width= 100, int height= 15,
		  const char* name = "FFuLabelField");
  virtual ~FFuQtLabelField() {}

  virtual void setSensitivity(bool setSensitive){this->FFuLabelField::setSensitivity(setSensitive);}
  virtual bool getSensitivity() {return this->FFuLabelField::getSensitivity();}
  virtual void setToolTip(const char* tip) {this->FFuLabelField::setToolTip(tip);}
};

#endif
