// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUQTMDIWINDOW_H
#define FFUQTMDIWINDOW_H



#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "FFuLib/FFuBase/FFuMDIWindow.H"

// Typedefs and fwd declarations
class QMdiSubWindow;

class FFuQtMDIWindow: public FFuQtTopLevelShell,virtual public FFuMDIWindow
{
public:
  
  FFuQtMDIWindow(QWidget* parent=0,
		int xpos=100,int ypos=100,int width=100,int height=100,
		const char* title= "FFuQtMDIWindowUI",
		const char* name = "FFuQtMDIWindow");
  virtual ~FFuQtMDIWindow();


 
// Operations
private:
  virtual void popUp(); 
  virtual void popDown();
  virtual void removeFromTopLevel();

// Attributes 
protected: 
  //  QPoint position;
  QMdiSubWindow * myQtSubWindow;

};
/////////////////////////////////////////////////////////////////////////////
#endif
