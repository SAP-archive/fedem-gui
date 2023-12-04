// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQSIMPLELOAD_H
#define FUIQSIMPLELOAD_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSimpleLoad.H"


class FuiQtSimpleLoad : public virtual FFuQtMultUIComponent, 
                         public FuiSimpleLoad
{
  
public:

  FuiQtSimpleLoad(QWidget* parent = 0,
                   int xpos=100,
                   int ypos=100,
                   int width=800,
                   int height=35,
                   const char* name="Motion Type");
  virtual ~FuiQtSimpleLoad();

  virtual void setSensitivity(bool sensitive){FuiSimpleLoad::setSensitivity(sensitive);}

};

#endif
