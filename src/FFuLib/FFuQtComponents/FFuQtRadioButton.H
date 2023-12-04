// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_RADIO_BUTTON_H
#define FFU_QT_RADIO_BUTTON_H

#include <QRadioButton>

#include "FFuLib/FFuQtComponents/FFuQtButton.H"
#include "FFuLib/FFuRadioButton.H"


class FFuQtRadioButton : public QRadioButton,
                         public FFuQtButton, virtual public FFuRadioButton
{
  Q_OBJECT

public:
  FFuQtRadioButton(QWidget* parent = NULL, const char* name = NULL);
  virtual ~FFuQtRadioButton() {}

  virtual void setUIValue(bool onOrOff);
  virtual bool getValue() const;

protected slots:
  void onToggled(bool value);
};

#endif
