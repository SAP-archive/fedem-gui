// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTJOINTTABADVANCED_H
#define FUIQTJOINTTABADVANCED_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiJointTabAdvanced.H"


class FuiQtJointTabAdvanced : public virtual FFuQtMultUIComponent, 
                         public FuiJointTabAdvanced
{
  
public:

  FuiQtJointTabAdvanced(QWidget* parent = 0,
                   int xpos=100,
                   int ypos=100,
                   int width=800,
                   int height=35,
                   const char* name="JointTabAdvanced");
  virtual ~FuiQtJointTabAdvanced();


};

#endif
