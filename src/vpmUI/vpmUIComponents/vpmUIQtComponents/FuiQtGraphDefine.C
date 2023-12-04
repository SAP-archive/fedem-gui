// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtGraphDefine.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtSpinBox.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"


FuiQtGraphDefine::FuiQtGraphDefine(QWidget* parent,
				   const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->FuiGraphDefine::titleField = new FFuQtIOField(this);
  this->FuiGraphDefine::titleLabel = new FFuQtLabel(this);
  this->FuiGraphDefine::subtitleField = new FFuQtIOField(this);
  this->FuiGraphDefine::subtitleLabel = new FFuQtLabel(this);

  this->FuiGraphDefine::xAxisField = new FFuQtIOField(this);
  this->FuiGraphDefine::xAxisLabel = new FFuQtLabel(this);
  this->FuiGraphDefine::yAxisField = new FFuQtIOField(this);
  this->FuiGraphDefine::yAxisLabel = new FFuQtLabel(this);

  for (FFuLabel*& label : this->FuiGraphDefine::fontSizeLabel)
    label = new FFuQtLabel(this);
  for (FFuSpinBox*& box : this->FuiGraphDefine::fontSizeBox)
    box = new FFuQtSpinBox(this);

  this->FuiGraphDefine::gridMenu = new FFuQtOptionMenu(this);
  this->FuiGraphDefine::gridLabel = new FFuQtLabel(this);
  this->FuiGraphDefine::legendButton = new FFuQtToggleButton(this);
  this->FuiGraphDefine::autoscaleButton = new FFuQtToggleButton(this);

  this->FuiGraphDefine::tminField = new FFuQtLabelField(this);
  this->FuiGraphDefine::tmaxField = new FFuQtLabelField(this);
  this->FuiGraphDefine::timeButton = new FFuQtToggleButton(this);

  this->FuiGraphDefine::initWidgets();
}
