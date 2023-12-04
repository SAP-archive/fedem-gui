// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTBEAMPROPHYDRO_H
#define FUIQTBEAMPROPHYDRO_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiBeamPropHydro.H"


class FuiQtBeamPropHydro : public virtual FFuQtMultUIComponent,
			  public FuiBeamPropHydro
{
public:
  FuiQtBeamPropHydro(QWidget* parent = 0,
		    int xpos = 100, int ypos = 100,
		    int width = 800, int height = 35,
		    const char* name="BeamPropHydro");
  virtual ~FuiQtBeamPropHydro() {}
};

#endif
