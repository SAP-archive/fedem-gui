// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTCTRLELEMPROPERTIES_H
#define FUIQTCTRLELEMPROPERTIES_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiCtrlElemProperties.H"

class FFuLabelField;


class FuiQtCtrlElemProperties : public FFuQtMultUIComponent, public FuiCtrlElemProperties
{
public:
  FuiQtCtrlElemProperties(QWidget* parent);
  virtual ~FuiQtCtrlElemProperties() {}

  virtual void setSensitivity(bool isSensitive);

protected:
  virtual FFuLabelField* makeALabelField();
};

#endif
