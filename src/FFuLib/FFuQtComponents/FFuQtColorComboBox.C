// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtColorComboBox.H"
#include <QPainter>


FFuQtColorComboBox::FFuQtColorComboBox(QWidget* parent, const char*)
{
  this->setWidget(this);
  this->setParent(parent);
  QObject::connect(this, SIGNAL(activated(int)),
                   this, SLOT(fwdSelectionChanged(int)));
}


void FFuQtColorComboBox::setCurrentCol(const FFuColor& rgb)
{
  for (int i = 0; i < this->count(); i++)
  {
    QColor color = this->itemData(i).value<QColor>();
    if (rgb == FFuColor(color.red(),color.green(),color.blue())) {
      this->setCurrentIndex(i);
      break;
    }
  }
}


void FFuQtColorComboBox::insertCol(const FFuColor& rgb,
                                   const std::string& name, int index)
{
  int r = rgb[0];
  if (r > 255)
    r = 255;
  else if (r < 0)
    r = 0;

  int g = rgb[1];
  if (g > 255)
    g = 255;
  else if (g < 0)
    g = 0;

  int b = rgb[2];
  if (b > 255)
    b = 255;
  else if (b < 0)
    b = 0;

  QColor color(r, g, b);
  QPixmap pixmap(12, 12);
  QPainter painter(&pixmap);

  painter.setPen(Qt::gray);
  painter.setBrush(QBrush(color));
  painter.drawRect(0, 0, 12, 12);

  QIcon icon;
  icon.addPixmap(pixmap);

  this->insertItem(index, icon, QString(name.c_str()), color);
}


FFuColor FFuQtColorComboBox::getCurrentCol()
{
  QColor c = this->itemData(this->currentIndex()).value<QColor>();
  return FFuColor(c.red(),c.green(),c.blue());
}

void FFuQtColorComboBox::enableColorDialog(bool tf)
{
  this->setEnabled(tf);
}


void FFuQtColorComboBox::fwdSelectionChanged(int index)
{
  QColor colr = this->itemData(index).value<QColor>();
  this->callSelectionChangedCB(FFuColor(colr.red(),colr.green(),colr.blue()));
}
