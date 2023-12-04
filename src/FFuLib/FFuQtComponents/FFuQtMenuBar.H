// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  \file FFuQtMenuBar.H
  \brief Qt implementation of a menu bar.
  \author Jacob Storen
  \date 22 Feb 1998
*/

#ifndef FFU_QT_MENU_BAR_H
#define FFU_QT_MENU_BAR_H

#include <QMenuBar>

#include "FFuLib/FFuMenuBar.H"
#include "FFuLib/FFuQtComponents/FFuQtMenuBase.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"


class FFuQtMenuBar : public QMenuBar, public FFuMenuBar,
                     public FFuQtMenuBase, public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtMenuBar(QWidget* parent = NULL);
  virtual ~FFuQtMenuBar() {}

  virtual bool isMenuEmpty() const;

protected:
  virtual int  basicNewItem(FFuaCmdItem* item, FFuPopUpMenu* menu);
  virtual void basicDeleteItems();
  virtual void insertSeparator();
};

#endif
