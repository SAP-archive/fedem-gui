// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_DROP_DOWN_BOX_H
#define FFU_QT_DROP_DOWN_BOX_H

#include <QWidget>

class QFrame;
class QLabel;
class QToolButton;
class QGridLayout;


class FFuQtDropDownBox : public QWidget
{
public:
  FFuQtDropDownBox(QWidget* parent = NULL);
  virtual ~FFuQtDropDownBox() {}

  void setHeading(const QString& text);
  void setOpen(bool isOpen);
  void setContentLayout(QLayout* layout);

private:
  QFrame* myContentsFrame;
  QLabel* myHeadingLabel;
  QToolButton* myExpandIconButton;
  QGridLayout* myLayout;
};

#endif
