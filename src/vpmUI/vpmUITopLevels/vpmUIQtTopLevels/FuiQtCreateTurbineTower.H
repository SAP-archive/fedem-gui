// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CREATE_TURBINE_TOWER_H
#define FUI_QT_CREATE_TURBINE_TOWER_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiCreateTurbineTower.H"


class FuiQtCreateTurbineTower : public FFuQtTopLevelShell, public FuiCreateTurbineTower
{
public:
  FuiQtCreateTurbineTower(QWidget* parent = 0,
		      int xpos =100, int ypos  =100,
		      int width=100, int height=100,
		      const char* title= "Fedem",
		      const char* name = "FuiQtCreateTurbineTower");
  virtual ~FuiQtCreateTurbineTower() {}

private:
  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiCreateTurbineTower::setSensitivity(isSensitive);
  }
};

#endif
