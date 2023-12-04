// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtScale.H"
#include "FFuLib/FFuQtComponents/FFuQtColorSelector.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"

#include "FuiQtAppearance.H"


FuiAppearance* FuiAppearance::create(int xpos, int ypos,
                                     int width, int height,
                                     const char* title,
                                     const char* name)
{
  return new FuiQtAppearance(xpos,ypos,width,height,title,name);
}


FuiQtAppearance::FuiQtAppearance(int xpos, int ypos,
                                 int width, int height,
                                 const char* title,
                                 const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name,Qt::WindowStaysOnTopHint)
{
  FFuQtLabelFrame* qtDetailsFrame;
  FFuQtLabelFrame* qtColorFrame;
  FFuQtLabelFrame* qtMaterialFrame;

  myDetailsFrame = qtDetailsFrame = new FFuQtLabelFrame(this);
  myColorFrame = qtColorFrame = new FFuQtLabelFrame(this);
  myMaterialFrame = qtMaterialFrame = new FFuQtLabelFrame(this);

  myDialogButtons = new FFuQtDialogButtons(this);

  myColorSelector = new FFuQtColorSelector(qtColorFrame);

  myPolygonsLabel = new FFuQtLabel(qtDetailsFrame);
  myLinesLabel = new FFuQtLabel(qtDetailsFrame);

  myPolygonOptions = new FFuQtOptionMenu(qtDetailsFrame);
  myLinesOptions= new FFuQtOptionMenu(qtDetailsFrame);

  myShininessLabel  = new FFuQtLabel(qtMaterialFrame);
  myTransparencyLabel  = new FFuQtLabel(qtMaterialFrame);

  FFuQtScale* qtShininessScale;
  FFuQtScale* qtTransperanceScale;
  myShininessScale = qtShininessScale = new FFuQtScale(qtMaterialFrame);
  myTransparencyScale = qtTransperanceScale = new FFuQtScale(qtMaterialFrame);
  qtShininessScale->setOrientation(Qt::Horizontal);
  qtTransperanceScale->setOrientation(Qt::Horizontal);

  this->initWidgets();
}
