// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQMOTIONTYPE_H
#define FUIQMOTIONTYPE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiMotionType.H"


class FuiQtMotionType : public virtual FFuQtMultUIComponent, 
			public FuiMotionType
{
public:
  FuiQtMotionType(QWidget* parent = 0, int nRButton = 4,
		  int xpos=100, int ypos=100,
		  int width=800,int height=35,
		  const char* name="Motion Type");
  virtual ~FuiQtMotionType() {}

  virtual void setSensitivity(bool sensitive)
  { FuiMotionType::setSensitivity(sensitive); }
};

#endif
