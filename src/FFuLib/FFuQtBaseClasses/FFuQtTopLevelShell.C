// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QCloseEvent>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"


FFuQtTopLevelShell::FFuQtTopLevelShell(QWidget* parent,
				       int xpos, int ypos,
				       int width,int height,
				       const char* title,
				       const char* name,
				       Qt::WindowFlags f)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name,f)
{
  this->setWindowTitle(title);
}


void FFuQtTopLevelShell::popUp()
{
  this->show();
  this->raise();
}


void FFuQtTopLevelShell::refresh()
{
  if (this->isVisible()) this->repaint();
}


void FFuQtTopLevelShell::iconify()
{
  this->iconify();
}


void FFuQtTopLevelShell::deiconify()
{
  this->show();
  this->raise();
}


void FFuQtTopLevelShell::showTLSNormal()
{
  this->showNormal();
  this->setFocus();
}


void FFuQtTopLevelShell::setTitle(const char* title)
{
  this->setWindowTitle(title);
}


void FFuQtTopLevelShell::closeEvent(QCloseEvent* e)
{
  if (this->onClose())
    e->accept();
  else
    e->ignore();
}
