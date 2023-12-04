// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_SPRING_DEF_CALC_H
#define FUI_QT_SPRING_DEF_CALC_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSpringDefCalc.H"


class FuiQtSpringDefCalc : public virtual FFuQtMultUIComponent,
                           public FuiSpringDefCalc
{
public:
  FuiQtSpringDefCalc(QWidget* parent = 0,
		     int xpos=100, int ypos=100,
		     int width=800,int height=35,
		     const char* name="SpringDefCalc");
  virtual ~FuiQtSpringDefCalc() {}

  virtual void setSensitivity(bool sensitive)
  { this->FuiSpringDefCalc::setSensitivity(sensitive); }
};

#endif
