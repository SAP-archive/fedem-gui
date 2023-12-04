// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtCSSelector.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtItemsListViews.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"


FuiCSSelector* FuiCSSelector::create(int xpos, int ypos, int width, int height,
                                     const char* title, const char* name)
{
  return new FuiQtCSSelector(xpos,ypos,width,height,title,name);
}


FuiQtCSSelector::FuiQtCSSelector(int xpos, int ypos, int width, int height,
                                 const char* title, const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name,Qt::WindowStaysOnTopHint)
{
  lvCS = new FuiQtCrossSectionListView(this);
  lvMat = new FuiQtMaterialListView(this);
  csLabel = new FFuQtLabel(this);
  matLabel = new FFuQtLabel(this);
  notesImage = new FFuQtLabel(this);
  notesLabel = new FFuQtLabel(this);
  notesText = new FFuQtLabel(this);
  importButton = new FFuQtPushButton(this);
  closeButton = new FFuQtPushButton(this);

  this->initWidgets();
}
