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


void FFuQtLabel::setPixMap(const char** pixmap, bool stretch)
{
  if (pixmap) {
    this->setScaledContents(stretch);
    this->QLabel::setPixmap(QPixmap(pixmap));
  }
  else
    this->QLabel::clear();
}


void FFuQtLabel::setLabel(const char* label)
{
  this->setText(label);
}


std::string FFuQtLabel::getLabel() const
{
  return this->text().toStdString();
}


void FFuQtLabel::fwdLinkActivated(const QString& txt)
{
  myLinkActivatedCB.invoke(txt.toStdString());
}
