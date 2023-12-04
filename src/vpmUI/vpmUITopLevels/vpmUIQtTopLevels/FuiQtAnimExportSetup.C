// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtAnimExportSetup.H"
#include "FFuLib/FFuQtComponents/FFuQtSpinBox.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiAnimExportSetup* FuiAnimExportSetup::create(int xpos, int ypos,
					       int width, int height,
					       const char* title,
					       const char* name)
{
  return new FuiQtAnimExportSetup(xpos,ypos,width,height,title,name);
}


FuiQtAnimExportSetup::FuiQtAnimExportSetup(int xpos, int ypos,
					   int width, int height,
					   const char* title,
					   const char* name)
  : FFuQtModalDialog(xpos,ypos,width,height,title,name,
                     Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  myRealBtn = new FFuQtRadioButton(this);
  myAllBtn  = new FFuQtRadioButton(this);
  myOmitBtn = new FFuQtRadioButton(this);
  mySomeBtn = new FFuQtRadioButton(this);

  omitNthSpinBox  = new FFuQtSpinBox(this);
  everyNthSpinBox = new FFuQtSpinBox(this);

  myFileLabel = new FFuQtLabel(this);
  myFileField = new FFuQtIOField(this);
  myBrowseButton = new FFuQtPushButton(this);

  dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}
