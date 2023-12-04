// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQSNCURVESELCTOR_H
#define FUIQSNCURVESELCTOR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSNCurveSelector.H"


class FuiQtSNCurveSelector : public virtual FFuQtMultUIComponent,
			     public FuiSNCurveSelector
{
public:
  FuiQtSNCurveSelector(QWidget* parent = 0,
		       int xpos =100, int ypos =100,
		       int width=800, int height=35,
		       const char* name="SN-curve selector");
  virtual ~FuiQtSNCurveSelector() {}

  virtual void setSensitivity(bool sensitive)
  { FuiSNCurveSelector::setSensitivity(sensitive); }
};

#endif
