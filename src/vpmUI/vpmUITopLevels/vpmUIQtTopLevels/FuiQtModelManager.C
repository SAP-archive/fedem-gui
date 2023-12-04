// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtTabbedWidgetStack.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtItemsListViews.H"
#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtModelManager.H"


FuiQtModelManager::FuiQtModelManager(QWidget* parent,
				     int xpos, int ypos,
				     int width,int height,
				     const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  this->tabStack = new FFuQtTabbedWidgetStack(this);
  this->simModelManager = new FuiQtSimModelListView(this);
  this->resultManager = new FuiQtResultListView(this);

  this->initWidgets();
}
