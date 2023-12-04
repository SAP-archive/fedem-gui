// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTEXTCTRLSYSPROPERTIES_H
#define FUIQTEXTCTRLSYSPROPERTIES_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiExtCtrlSysProperties.H"

class FFuLabelField;

class FuiQtExtCtrlSysProperties : public virtual FFuQtMultUIComponent, 
				  public FuiExtCtrlSysProperties
{
public:
  FuiQtExtCtrlSysProperties(QWidget* parent=0, const char* name = "FuiQtExtCtrlSysProperties");
  virtual ~FuiQtExtCtrlSysProperties();
  void makeNewFields();
  virtual void setSensitivity(bool isSensitive); 
};
#endif
