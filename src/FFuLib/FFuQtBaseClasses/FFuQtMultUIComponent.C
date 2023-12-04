// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QResizeEvent>
#include <QEvent>

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"


FFuQtMultUIComponent::FFuQtMultUIComponent(QWidget* parent,
                                           const char* name,
                                           Qt::WindowFlags f)
  : QWidget(parent,f)
{
  this->setObjectName(name);
  this->setWidget(this);
}

FFuQtMultUIComponent::FFuQtMultUIComponent(QWidget* parent,
                                           int xpos, int ypos,
                                           int width, int height,
                                           const char* name,
                                           Qt::WindowFlags f)
  : QWidget(parent,f)
{
  this->setObjectName(name);
  this->setWidget(this);
  this->setGeometry(xpos, ypos, width, height);
}


void FFuQtMultUIComponent::resizeEvent(QResizeEvent* e)
{
  this->QWidget::resizeEvent(e);
  this->placeWidgets(this->width(),this->height());
}


void FFuQtMultUIComponent::setVisible(bool visible)
{
  bool wasvisible = this->isVisible();

  this->QWidget::setVisible(visible);

  if (!wasvisible && visible)
    this->onPoppedUpFromMemLoc();
  else if (wasvisible && !visible)
    this->onPoppedDownToMemLoc();
}


bool FFuQtMultUIComponent::event(QEvent* e)
{
  bool ret = this->QWidget::event(e);

  switch (e->type()) {
  case QEvent::Show:
    this->onPoppedUp();
    return true;
  case QEvent::Hide:
    this->onPoppedDown();
    return true;
  default:
    break;
  }

  return ret;
}
