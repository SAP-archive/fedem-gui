// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtObjectBrowser.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtListView.H"
#include "FFuLib/FFuQtComponents/FFuQtMemo.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"

#include <QApplication>
#include <QClipboard>


FuiObjectBrowser* FuiObjectBrowser::create(int xpos, int ypos,
					   int width, int height,
					   const char* title,
					   const char* name)
{
  return new FuiQtObjectBrowser(xpos,ypos,width,height,title,name);
}


FuiQtObjectBrowser::FuiQtObjectBrowser(int xpos, int ypos,
				       int width, int height,
				       const char* title,
				       const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name)
{
  this->headerImage2    = new FFuQtLabel(this);
  this->headerImage1    = new FFuQtLabel(this);
  this->searchLabel     = new FFuQtLabel(this);
  this->searchField     = new FFuQtIOField(this);
  this->searchButton    = new FFuQtPushButton(this);
  this->searchView      = new FFuQtListView(this);
  this->outputLabel     = new FFuQtLabel(this);
  this->outputMemo      = new FFuQtMemo(this);
  this->closeButton     = new FFuQtPushButton(this);
  this->helpButton      = new FFuQtPushButton(this);
  this->sepLabel        = new FFuQtLabel(this);
  this->copyDataButton  = new FFuQtPushButton(this);

  this->initWidgets();
}


void FuiQtObjectBrowser::onCopyDataButtonClicked()
{
  QApplication::clipboard()->setText(outputMemo->getText().c_str());
}
