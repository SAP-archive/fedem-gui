// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTBEAMPROPSUMMARY_H
#define FUIQTBEAMPROPSUMMARY_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiBeamPropSummary.H"


class FuiQtBeamPropSummary : public virtual FFuQtMultUIComponent,
			  public FuiBeamPropSummary
{
public:
  FuiQtBeamPropSummary(QWidget* parent = 0,
		    int xpos = 100, int ypos = 100,
		    int width = 800, int height = 35,
		    const char* name="BeamPropSummary");
  virtual ~FuiQtBeamPropSummary() {}
};

#endif
