// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  \file FFuQtMenuBar.C
  \brief Qt implementation of a menu bar.
  \author Jacob Storen
  \date 22 Feb 1998
*/

#include <iostream>
#include <QMenu>

#include "FFuLib/FFuQtComponents/FFuQtMenuBar.H"
#include "FFuLib/FFuQtComponents/FFuQtPopUpMenu.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"


FFuQtMenuBar::FFuQtMenuBar(QWidget* parent) : QMenuBar(parent)
{
  this->setWidget(this);
}


int FFuQtMenuBar::basicNewItem(FFuaCmdItem* item, FFuPopUpMenu* menu)
{
  QMenu* qMenu = dynamic_cast<QMenu*>(menu);
  if (!qMenu)
  {
    std::cerr <<"  ** Command item \""<< item->getText()
              <<"\" is not a header (ignored)."<< std::endl;
    return -1;
  }

  qMenu->setTitle(item->getText().c_str());
  this->addMenu(qMenu);

  return this->actions().size();
}


void FFuQtMenuBar::basicDeleteItems()
{
  this->clear();
}


bool FFuQtMenuBar::isMenuEmpty() const
{
  return this->actions().isEmpty();
}


void FFuQtMenuBar::insertSeparator()
{
  this->addSeparator();
}
