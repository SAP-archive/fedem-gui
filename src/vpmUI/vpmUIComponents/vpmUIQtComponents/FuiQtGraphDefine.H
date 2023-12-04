// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_GRAPHDEFINE_H
#define FUI_QT_GRAPHDEFINE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiGraphDefine.H"


class FuiQtGraphDefine : public FFuQtMultUIComponent,
			 public FuiGraphDefine
{
public:
  FuiQtGraphDefine(QWidget* parent = 0,
		   const char* name = "FuiQtGraphDefine");
  virtual ~FuiQtGraphDefine() {}

private:
  virtual void setSensitivity(bool) {}
};

#endif
