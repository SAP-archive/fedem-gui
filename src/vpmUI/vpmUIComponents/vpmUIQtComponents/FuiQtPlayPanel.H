// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTPLAYPANEL_H
#define FUIQTPLAYPANEL_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiPlayPanel.H"

class QWidget;

class FuiQtPlayPanel: public FFuQtMultUIComponent, public  FuiPlayPanel
{
public:
  FuiQtPlayPanel(QWidget* parent = 0,
			 int xpos=100,
			 int ypos=100,
			 int width=40,
			 int height=60,
			 const char* name="PlayPanel");
  virtual ~FuiQtPlayPanel(){};

};


#endif
