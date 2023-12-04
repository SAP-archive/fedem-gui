// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_TOGGLE_BUTTON_H
#define FFU_QT_TOGGLE_BUTTON_H

#include <QCheckBox>

#include "FFuLib/FFuQtComponents/FFuQtButton.H"
#include "FFuLib/FFuToggleButton.H"


class FFuQtToggleButton : public QCheckBox,
                          public FFuQtButton, virtual public FFuToggleButton
{
  Q_OBJECT

public:
  FFuQtToggleButton(QWidget* parent = NULL, const char* name = NULL);
  virtual ~FFuQtToggleButton() {}

  virtual void setUIValue(bool onOrOff);
  virtual bool getValue() const;

  virtual int  getTristateValue() const;
  virtual void useUITristate(bool y = true);
  virtual void setUITristateValue(int value);

protected slots:
  void onStateChanged(int value);
};

#endif
