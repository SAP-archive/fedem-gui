// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_THRESHOLD_H
#define FUI_QT_THRESHOLD_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiThreshold.H"


class FuiQtThreshold : public virtual FFuQtMultUIComponent,
                       public FuiThreshold
{
public:
  FuiQtThreshold(QWidget* parent, const char* name="Threshold");
  virtual ~FuiQtThreshold() {}
};

#endif
