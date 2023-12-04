// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef _FFUQTCOLORSELECTOR_H_
#define _FFUQTCOLORSELECTOR_H_


#include "FFuLib/FFuColorSelector.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"

class QWidget;
class FFuQtFrame;

class FFuQtColorSelector: public FFuQtMultUIComponent, public  FFuColorSelector
{

public:
  FFuQtColorSelector(QWidget* parent = 0,
		     int xpos=100,
		     int ypos=100,
		     int width=260,
		     int height=80,
		     const char* name="Color selector");
  virtual ~FFuQtColorSelector(){};
  
protected:
  virtual void updateSampleFrame();
  
private:
  FFuQtFrame* qtColorSampleFrame;

  
};


#endif
