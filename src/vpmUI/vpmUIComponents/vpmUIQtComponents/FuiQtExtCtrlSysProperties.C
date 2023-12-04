// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

//include
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtExtCtrlSysProperties.H"
#include "vpmUI/vpmUIComponents/FuiExtCtrlSysProperties.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtTable.H"

//----------------------------------------------------------------------------

FuiQtExtCtrlSysProperties::FuiQtExtCtrlSysProperties(QWidget* parent,
						     const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  // Component creation
  this->fileBrowseField = new FFuQtFileBrowseField(this);
  this->myTable = new FFuQtTable(this);

  //base class component initiation
  this->FuiExtCtrlSysProperties::initWidgets();
  
}
//----------------------------------------------------------------------------

FuiQtExtCtrlSysProperties::~FuiQtExtCtrlSysProperties()
{
}

//----------------------------------------------------------------------------
void FuiQtExtCtrlSysProperties::makeNewFields()
{
  QWidget* qTablePtr = dynamic_cast<QWidget*>(myTable);

  this->myInpEngineFields.push_back(new FuiQtQueryInputField(qTablePtr));
  this->myNameLabels.push_back(new FFuQtLabel(qTablePtr));
}

void FuiQtExtCtrlSysProperties::setSensitivity(bool isSensitive)
{
  FuiExtCtrlSysProperties::setSensitivity(isSensitive);
}

//----------------------------------------------------------------------------
