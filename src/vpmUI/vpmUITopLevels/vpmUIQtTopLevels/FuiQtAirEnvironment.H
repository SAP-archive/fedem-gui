// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_AIR_ENVIRONMENT_H
#define FUI_QT_AIR_ENVIRONMENT_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiAirEnvironment.H"


class FuiQtAirEnvironment : public FFuQtTopLevelShell, public FuiAirEnvironment
{
public:
  FuiQtAirEnvironment(QWidget* parent = 0,
		      int xpos =100, int ypos  =100,
		      int width=100, int height=100,
		      const char* title= "Fedem",
		      const char* name = "FuiQtAirEnvironment");
  virtual ~FuiQtAirEnvironment() {}

private:
  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiAirEnvironment::setSensitivity(isSensitive);
  }
};

#endif
