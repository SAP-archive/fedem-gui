// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QtGui/QPixmap>

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"


FFuQtLabel::FFuQtLabel(QWidget* parent) : QLabel(parent)
{
  this->setWidget(this);
  this->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

  QObject::connect(this,SIGNAL(linkActivated(const QString&)),
                   this,SLOT(fwdLinkActivated(const QString&)));
}


void FFuQtLabel::setPixMap(const char** pixmap, int width, int height)
{
  if (pixmap) {
    QPixmap xpm(pixmap);
    if (width > 0 && height > 0)
      this->QLabel::setPixmap(xpm.scaled(width,height));
    else if (width > 0)
      this->QLabel::setPixmap(xpm.scaledToWidth(width));
    else if (height > 0)
      this->QLabel::setPixmap(xpm.scaledToHeight(height));
    else
      this->QLabel::setPixmap(xpm);
  }
  else
    this->QLabel::clear();
}


void FFuQtLabel::setLabel(const char* label)
{
  this->setText(label);
}

void FFuQtLabel::setLabel(const std::string& label)
{
  this->setText(label.c_str());
}

void FFuQtLabel::setLabelAlignment(int alignment)
{
  this->setAlignment(static_cast<Qt::Alignment>(alignment));
}

std::string FFuQtLabel::getLabel() const
{
  return this->text().toStdString();
}

void FFuQtLabel::fwdLinkActivated(const QString& txt)
{
  myLinkActivatedCB.invoke(txt.toStdString());
}
