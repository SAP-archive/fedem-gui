// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtMooringLine.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiMooringLine* FuiMooringLine::create(int xpos, int ypos,
                                       int width, int height,
                                       const char* title,
                                       const char* name)
{
  return new FuiQtMooringLine(xpos,ypos,width,height,title,name);
}


FuiQtMooringLine::FuiQtMooringLine(int xpos, int ypos,
                                   int width, int height,
                                   const char* title,
                                   const char* name)
  : FFuQtModalDialog(xpos,ypos,width,height,title,name,
                     Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  myNumField = new FFuQtLabelField(this);
  myTypeLabel = new FFuQtLabel(this);
  myTypeMenu = new FFuQtOptionMenu(this);
  myLengthField = new FFuQtLabelField(this);
  myDialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();

  myDialogButtons->setButtonClickedCB(FFaDynCB1M(FuiQtMooringLine,this,
                                                 onDialogButtonClicked,int));
}


void FuiQtMooringLine::onDialogButtonClicked(int button)
{
  this->done(button == 0 ? QDialog::Accepted : QDialog::Rejected);
}
