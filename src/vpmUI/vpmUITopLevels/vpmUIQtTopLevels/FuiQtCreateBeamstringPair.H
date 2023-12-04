// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CREATE_BEAMSTRING_PAIR_H
#define FUI_QT_CREATE_BEAMSTRING_PAIR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiCreateBeamstringPair.H"


class FuiQtCreateBeamstringPair : public FFuQtTopLevelShell, public FuiCreateBeamstringPair
{
public:
  FuiQtCreateBeamstringPair(QWidget* parent = 0,
		      int xpos =100, int ypos  =100,
		      int width=100, int height=100,
		      const char* title= "Fedem",
		      const char* name = "FuiQtCreateBeamstringPair");
  virtual ~FuiQtCreateBeamstringPair() {}

private:
  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiCreateBeamstringPair::setSensitivity(isSensitive);
  }
};

#endif
