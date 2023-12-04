// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTSPRINGCHAR_H
#define FUIQTSPRINGCHAR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSpringChar.H"


class FuiQtSpringChar : public virtual FFuQtMultUIComponent,
			public FuiSpringChar
{
public:

  FuiQtSpringChar(QWidget* parent = 0,
		  int xpos=100,
		  int ypos=100,
		  int width=800,
		  int height=35,
		  const char* name="SpringChar");
  virtual ~FuiQtSpringChar();

  virtual void setSensitivity(bool sensitive){FuiSpringChar::setSensitivity(sensitive);}
};

#endif
