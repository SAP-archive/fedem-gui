// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTDUTYCYCLEOPTIONS_H
#define FUIQTDUTYCYCLEOPTIONS_H

#include "vpmUI/vpmUITopLevels/FuiDutyCycleOptions.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"


class FuiQtDutyCycleOptions : public FFuQtTopLevelShell,
			      public FuiDutyCycleOptions
{
public:
  FuiQtDutyCycleOptions(QWidget* parent=0,int xpos=100,int ypos=100,
			int width=388,int height=460,
			const char* title= "Duty Cycle Setup",
			const char* name = "FuiQtDutyCycleOptions");

  virtual ~FuiQtDutyCycleOptions() {}

  virtual void setSensitivity(bool isSensitive);

};

#endif
