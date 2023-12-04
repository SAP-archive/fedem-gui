// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTJOINTSUMMARY_H
#define FUIQTJOINTSUMMARY_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiJointSummary.H"


class FuiQtJointSummary : public virtual FFuQtMultUIComponent,
			  public FuiJointSummary
{
public:
  FuiQtJointSummary(QWidget* parent = 0,
		    int xpos = 100, int ypos = 100,
		    int width = 800, int height = 35,
		    const char* name="JointSummary");
  virtual ~FuiQtJointSummary() {}
};

#endif
