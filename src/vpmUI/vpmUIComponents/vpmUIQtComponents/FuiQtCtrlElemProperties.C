// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtTableView.H"

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtCtrlElemProperties.H"


FuiQtCtrlElemProperties::FuiQtCtrlElemProperties(QWidget* parent)
  : FFuQtMultUIComponent(parent, "FuiCtrlElemProperties")
{
  FFuQtLabel* elemPixmap = new FFuQtLabel(this);
  elemPixmap->setAlignment(Qt::AlignCenter);

  this->myElemPixmap     = elemPixmap;
  this->myParameterFrame = new FFuQtLabelFrame(this);
  this->myParameterView  = new FFuQtTableView(this);

  this->initWidgets();
}


void FuiQtCtrlElemProperties::setSensitivity(bool isSensitive)
{
  FuiCtrlElemProperties::setSensitivity(isSensitive);
}


FFuLabelField* FuiQtCtrlElemProperties::makeALabelField()
{
  return new FFuQtLabelField(0);
}
