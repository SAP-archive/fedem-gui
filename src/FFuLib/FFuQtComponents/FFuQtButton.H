// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_BUTTON_H
#define FFU_QT_BUTTON_H

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuButton.H"

class QAbstractButton;


class FFuQtButton : public FFuQtComponentBase, virtual public FFuButton
{
public:
  FFuQtButton() : widget(NULL) {}
  virtual ~FFuQtButton() {}

  virtual void setPixMap(const char** pixmap);
  virtual void setLabel (const char* label);

  virtual bool getToggleAble();
  virtual bool getToggle();

protected:
  void setButtonWidget(QAbstractButton* widget);

private:
  QAbstractButton* widget;
};

#endif
