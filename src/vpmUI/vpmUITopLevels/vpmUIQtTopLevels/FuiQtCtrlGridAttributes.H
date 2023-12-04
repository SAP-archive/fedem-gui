// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CTRL_GRID_ATTRIBUTES_H
#define FUI_QT_CTRL_GRID_ATTRIBUTES_H

#include "vpmUI/vpmUITopLevels/FuiCtrlGridAttributes.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"


class FuiQtCtrlGridAttributes : public FFuQtTopLevelShell,
				public FuiCtrlGridAttributes
{
public:
  FuiQtCtrlGridAttributes(QWidget* parent = NULL);
  virtual ~FuiQtCtrlGridAttributes() {}
};

#endif
