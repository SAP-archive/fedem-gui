// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_SPR_DA_FORCE_H
#define FUI_QT_SPR_DA_FORCE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSprDaForce.H"


class FuiQtSprDaForce : public virtual FFuQtMultUIComponent,
                        public FuiSprDaForce
{
public:
  FuiQtSprDaForce(QWidget* parent=0,
		  int xpos=100, int ypos=100,
		  int width=800,int height=35,
		  const char* name="SprDaForce");
  virtual ~FuiQtSprDaForce() {}

  virtual void setSensitivity(bool sensitive)
  { this->FuiSprDaForce::setSensitivity(sensitive); }
};

#endif
