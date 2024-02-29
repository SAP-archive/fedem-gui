// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QtGui/QPixmap>
#include <QMdiSubWindow>
#include <QIcon>

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtModeller.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtPlayPanel.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdViewer.H"
#else
#include <iostream>
#endif

extern const char* openMechModeller_xpm[];


FuiModeller* FuiModeller::create(FFuComponentBase* parent,
				 int xpos, int ypos,
				 int width,int height,
				 const char* title,
				 const char* name)
{
  return new FuiQtModeller(dynamic_cast<QWidget*>(parent),
			   xpos,ypos,width,height,title,name);
}


FuiQtModeller::FuiQtModeller(QWidget* parent,
			     int xpos, int ypos,
			     int width,int height,
			     const char* title,
			     const char* name)
  : FFuQtMDIWindow(parent,xpos,ypos,width,height,title,name)
{
  this->myPlayPanel = new FuiQtPlayPanel(this);
  this->my3Dpoint = new FuiQt3DPoint(this);
#ifdef USE_INVENTOR
  this->myViewer = FdViewer::create(this);
#else
  std::cerr <<" *** FuiQtModeller: No viewer in this build."<< std::endl;
#endif
  myQtSubWindow->setWindowIcon(QIcon(QPixmap(openMechModeller_xpm)));

  this->initWidgets();
}
