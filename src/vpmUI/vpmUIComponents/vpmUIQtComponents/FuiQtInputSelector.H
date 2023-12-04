// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_INPUT_SELECTOR_H
#define FUI_QT_INPUT_SELECTOR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiInputSelector.H"


class FuiQtInputSelector : public virtual FFuQtMultUIComponent, public FuiInputSelector
{
public:
  FuiQtInputSelector(QWidget* parent = 0,
		     int xpos=100, int ypos=100,
		     int width=800,int height=35,
		     const char* name="InputSelector");
  virtual ~FuiQtInputSelector() {}

  virtual void setSensitivity(bool sensitive) { FuiInputSelector::setSensitivity(sensitive); }
};

#endif
