// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTOUTPUTLIST_H
#define FUIQTOUTPUTLIST_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMDIWindow.H"
#include "vpmUI/vpmUITopLevels/FuiOutputList.H"



class FuiQtOutputList : public FFuQtTopLevelShell, // public FFuQtMDIWindow, 
                        public FuiOutputList
{
public:
  FuiQtOutputList(QWidget* parent=0,int xpos =100 ,int ypos = 100,
                  int width = 500,int height = 300, 
                  const char* title = "List",
                  const char* name = "FuiQtOutputList");
  virtual ~FuiQtOutputList();
 

private:
};

#endif
