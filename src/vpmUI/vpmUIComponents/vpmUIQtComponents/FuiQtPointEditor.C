// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtPointEditor.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"

FuiQtPointEditor::FuiQtPointEditor(QWidget* parent, int xpos, int ypos,
                 int width, int height, const char* name)
  :FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  myPointUI = new FuiQt3DPoint(this);
  myPickButton = new FFuQtPushButton(this);
  myViewPointButton = new FFuQtPushButton(this);
  myApplyButton = new FFuQtPushButton(this);
  myViewWhatButton= new FFuQtPushButton(this);
  myIdField = new FFuQtIOField(this);
  myOnLabel = new FFuQtLabel(this);

  this->initWidgets();
}

FuiQtPointEditor::~FuiQtPointEditor()
{
  
}
