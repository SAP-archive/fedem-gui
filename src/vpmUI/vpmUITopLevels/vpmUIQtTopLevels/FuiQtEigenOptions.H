// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_EIGEN_OPTIONS_H
#define FUI_QT_EIGEN_OPTIONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiEigenOptions.H"


class FuiQtEigenOptions : public FFuQtTopLevelShell, public FuiEigenOptions
{
public:
  FuiQtEigenOptions(int xpos=100, int ypos=100,
                    int width=388, int height=460,
		    const char* title="Fedem",
		    const char* name ="FuiQtEigenOptions");

  virtual ~FuiQtEigenOptions() {}

private:
  virtual void setSensitivity(bool sens)
  {
    FuiEigenOptions::setSensitivity(sens);
  }
};

#endif
