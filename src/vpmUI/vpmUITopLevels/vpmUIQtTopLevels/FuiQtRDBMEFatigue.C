// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtRDBMEFatigue.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtItemsListViews.H"

#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtTable.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"

#include <QApplication>
#include <QClipboard>


FuiRDBMEFatigue* FuiRDBMEFatigue::create(int xpos, int ypos,
					 int width, int height,
					 const char* title,
					 const char* name)
{
  return new FuiQtRDBMEFatigue(xpos,ypos,width,height,title,name);
}


FuiQtRDBMEFatigue::FuiQtRDBMEFatigue(int xpos, int ypos,
				     int width, int height,
				     const char* title,
				     const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name,Qt::WindowStaysOnTopHint)
{
  this->tableMain = new FFuQtTable(this);
  this->useProbToggle = new FFuQtToggleButton(this);
  this->startTimeField = new FFuQtLabelField(this);
  this->stopTimeField = new FFuQtLabelField(this);
  this->standardField = new FFuQtLabelField(this);
  this->snCurveField = new FFuQtLabelField(this);
  this->copyDataButton = new FFuQtPushButton(this);
  this->notesImage = new FFuQtLabel(this);
  this->notesLabel = new FFuQtLabel(this);
  this->notesText = new FFuQtLabel(this);
  this->dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}


void FuiQtRDBMEFatigue::onCopyDataClicked()
{
  std::string text;
  int rowCount = this->tableMain->getNumberRows();
  int colCount = this->tableMain->getNumberColumns();

  // Get header
  for (int j = 0; j < colCount; j++) {
    text.append(this->tableMain->getColumnLabel(j));
    if (j < colCount-1)
      text.append("\t");
  }
  text.append("\n");

  // Get data
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      if (j > 0)
        text.append(this->tableMain->getText(i,j));
      else if (this->tableMain->getCheckBoxItemToggle(i,j))
        text.append("X");
      if (j < colCount-1)
	text.append("\t");
    }
    text.append("\n");
  }

  QApplication::clipboard()->setText(text.c_str());
}
