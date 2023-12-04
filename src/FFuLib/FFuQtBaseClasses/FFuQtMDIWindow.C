// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtBaseClasses/FFuQtMDIWindow.H"
#include <QMdiArea>
#include <QMdiSubWindow>

//----------------------------------------------------------------------------

FFuQtMDIWindow::FFuQtMDIWindow(QWidget* parent,
			     int xpos,int ypos,int width,int height, 
			     const char* title,
			     const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name)
{
  QMdiArea* mdiArea =  dynamic_cast<QMdiArea*>(parent);
  if(mdiArea){
    myQtSubWindow = mdiArea->addSubWindow(this);
    myQtSubWindow->setGeometry(xpos,ypos,width,height);
    myQtSubWindow->setMinimumSize(320,240); // used by "Windows > Casacade"
  }
}
//----------------------------------------------------------------------------

FFuQtMDIWindow::~FFuQtMDIWindow()
{
}
//----------------------------------------------------------------------------

void FFuQtMDIWindow::popUp()
{ 
  //  cout<<"FFuQtMDIWindow::popUp"<<endl;
  myQtSubWindow->show();
  //FFuQtTopLevelShell::popUp();
  this->setFocus();//TMP hack since qworkspace works bad
}
//----------------------------------------------------------------------------

/*
void FFuQtMDIWindow::popUp()
{
  //this->reparent(dynamic_cast<QWidget*>(Fui::getMainWindow()->getWorkSpace()),0,this->position);
  
  FFuQtTopLevelShell::popUp();
  
  this->setFocus(); //TMP hack since qworkspace works bad
}
*/
void FFuQtMDIWindow::popDown()
{
  myQtSubWindow->hide();
}

void FFuQtMDIWindow::removeFromTopLevel()
{
  myQtSubWindow->mdiArea()->removeSubWindow(myQtSubWindow);
}

//----------------------------------------------------------------------------
