// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTVARIABLETYPE_H
#define FUIQTVARIABLETYPE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiVariableType.H"


class FuiQtVariableType : public virtual FFuQtMultUIComponent,
			  public FuiVariableType
{
public:
  FuiQtVariableType(QWidget* parent = 0,
		  int xpos =100, int ypos =100,
		  int width=800, int height=35,
		  const char* name="Variable Type");
  virtual ~FuiQtVariableType() {}

  virtual void setSensitivity(bool sensitive)
  { FuiVariableType::setSensitivity(sensitive); }
};

#endif
