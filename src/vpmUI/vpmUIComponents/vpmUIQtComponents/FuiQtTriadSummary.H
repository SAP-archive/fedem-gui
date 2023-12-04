// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTTRIADSUMMARY_H
#define FUIQTTRIADSUMMARY_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiTriadSummary.H"


class FuiQtTriadSummary : public virtual FFuQtMultUIComponent,
			  public FuiTriadSummary
{
public:
  FuiQtTriadSummary(QWidget* parent = 0,
		    int xpos = 100, int ypos = 100,
		    int width = 800, int height = 35,
		    const char* name="TriadSummary");
  virtual ~FuiQtTriadSummary() {}
};

#endif
