// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiModelManager.H"
#include "vpmUI/vpmUIComponents/FuiItemsListViews.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "FFuLib/FFuTabbedWidgetStack.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

//----------------------------------------------------------------------------

FuiModelManager::FuiModelManager()
{
  this->tabStack = NULL;
  this->simModelManager = NULL;
  this->resultManager = NULL;
}
//----------------------------------------------------------------------------

void FuiModelManager::initWidgets()
{
  this->tabStack->addTabPage(this->simModelManager,"Objects",treeObjects_xpm);
  this->tabStack->addTabPage(this->resultManager,"Results",treeResults_xpm);
  this->tabStack->setTabSelectedCB(FFaDynCB1M(FuiModelManager,this,onTabSelected,int));
}
//----------------------------------------------------------------------------

void FuiModelManager::placeWidgets(int width, int height)
{
  int border = 5;
  this->tabStack->setEdgeGeometry(border,width-border,border,height-border);
}
//----------------------------------------------------------------------------

void FuiModelManager::onTabSelected(int)
{
  //maybe something happend in mainwin
}
//----------------------------------------------------------------------------
