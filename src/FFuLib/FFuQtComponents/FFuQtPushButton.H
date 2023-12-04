// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_PUSH_BUTTON_H
#define FFU_QT_PUSH_BUTTON_H

#include <QPushButton>

#include "FFuLib/FFuQtComponents/FFuQtButton.H"
#include "FFuLib/FFuPushButton.H"


class FFuQtPushButton : public QPushButton,
                        public FFuQtButton, virtual public FFuPushButton
{
  Q_OBJECT

public:
  FFuQtPushButton(QWidget* parent = NULL, const char* name = NULL);
  virtual ~FFuQtPushButton() {}

  virtual void setToggleAble(bool able);
  virtual void toggleOn(bool toggle);

protected slots:
  void arm();
  void unarm();
  void activate();
  void toggle(bool value);
};

#endif
