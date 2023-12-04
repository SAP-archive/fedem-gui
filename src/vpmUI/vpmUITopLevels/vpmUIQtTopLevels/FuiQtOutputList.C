// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*! 
  \class FuiQtOutputList FuiQtOutputList.H

  \author Jacob Storen

  \date 
      \b 13.08.99 Created (\e JL) 
  
*/////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtMemo.H"
#include "FuiQtOutputList.H"

FuiOutputList* FuiOutputList::create(FFuComponentBase* parent,
				     int xpos,int ypos,
                                     int width,int height, 
                                     const char* title,
                                     const char* name)
{
  return new FuiQtOutputList(dynamic_cast<QWidget*>(parent),xpos,ypos,width,height,title,name);
}

FuiQtOutputList::FuiQtOutputList(QWidget* parent,int xpos,int ypos,
                                 int width,int height, 
                                 const char* title,
                                 const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name,Qt::Dialog)
{
  FFuQtMemo* list;
  myMemo = list = new FFuQtMemo(this);
  list->setReadOnly(true);

  QFont fnt("Courier",8);
  fnt.setStyleHint(QFont::Courier);
  list->setFont(fnt);

  this->initWidgets();
}

FuiQtOutputList::~FuiQtOutputList()
{
 
}
