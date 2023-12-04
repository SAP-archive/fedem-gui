// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QAbstractButton>
#include <QPixmap>

#include "FFuLib/FFuQtComponents/FFuQtButton.H"


void FFuQtButton::setButtonWidget(QAbstractButton* w)
{
  this->setWidget(widget = w);
}


void FFuQtButton::setPixMap(const char** pixmap)
{
  QPixmap xpm(pixmap);
  widget->setIcon(QIcon(xpm));
}


void FFuQtButton::setLabel(const char *label)
{
  widget->setText(label);
}


bool FFuQtButton::getToggleAble()
{
  return widget->isCheckable();
}


bool FFuQtButton::getToggle()
{
  return widget->isChecked();
}
