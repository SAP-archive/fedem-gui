// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_MODEL_MANAGER_H
#define FUI_QT_MODEL_MANAGER_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUITopLevels/FuiModelManager.H"


class FuiQtModelManager : public FFuQtMultUIComponent, public FuiModelManager
{
public:
  FuiQtModelManager(QWidget* parent,
		    int xpos = 100, int ypos  = 100,
		    int width= 100, int height= 100,
		    const char* name = "FuiQtModelManager");
  virtual ~FuiQtModelManager() {}
};

#endif
