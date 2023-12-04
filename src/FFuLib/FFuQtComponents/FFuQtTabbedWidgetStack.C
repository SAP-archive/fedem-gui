// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtTabbedWidgetStack.H"
#include <QTabBar>

//----------------------------------------------------------------------------

FFuQtTabbedWidgetStack::FFuQtTabbedWidgetStack(QWidget* parent, const char*)
  : QTabWidget(parent)
{
  this->setWidget(this);

  connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabSelected(int)));
}
//----------------------------------------------------------------------------

void FFuQtTabbedWidgetStack::onTabSelected(int tab)
{
  if (this->isPoppedUp()) {
    this->tabSelectedIdCB.invoke(tab);
    FFuComponentBase* compBase = dynamic_cast<FFuComponentBase*>(this->widget(tab));
    if (compBase)
      this->tabSelectedWidgetCB.invoke(compBase);
  }
}
//----------------------------------------------------------------------------

bool FFuQtTabbedWidgetStack::addTabPage(FFuComponentBase* widget, const std::string& label,
                                        const char** icon, int idx)
{
  QWidget* qwidget = dynamic_cast<QWidget*>(widget);
  if (qwidget && this->indexOf(qwidget) < 0) {
    if (icon)
      this->addTab(qwidget, QIcon(QPixmap(icon)), QString(label.c_str()));
    else if (idx < 0)
      this->addTab(qwidget, QString(label.c_str()));
    else
      this->insertTab(idx, qwidget, QString(label.c_str()));
    return true;
  }
  return false;
}

bool FFuQtTabbedWidgetStack::renameTabPage(FFuComponentBase* widget, const std::string& label)
{
  int tab = this->indexOf(dynamic_cast<QWidget*>(widget));
  if (tab < 0) return false;

  this->setTabText(tab,QString(label.c_str()));
  return true;
}

bool FFuQtTabbedWidgetStack::removeTabPage(FFuComponentBase* widget)
{
  int tab = this->indexOf(dynamic_cast<QWidget*>(widget));
  if (tab < 0) return false;

  this->removeTab(tab);
  return true;
}
//----------------------------------------------------------------------------

void FFuQtTabbedWidgetStack::setTabSensitivity(int tab, bool makeSensitive)
{
  this->setTabEnabled(tab,makeSensitive);
}

void FFuQtTabbedWidgetStack::setTabSensitivity(FFuComponentBase* widget, bool makeSensitive)
{
  int tab = this->indexOf(dynamic_cast<QWidget*>(widget));
  if (tab > -1)
    this->setTabEnabled(tab,makeSensitive);
}
//----------------------------------------------------------------------------

void FFuQtTabbedWidgetStack::setCurrentTab(int tab)
{
  this->setCurrentIndex(tab);
}

void FFuQtTabbedWidgetStack::setCurrentTab(FFuComponentBase* widget)
{
  QWidget* qwidget = dynamic_cast<QWidget*>(widget);
  if (qwidget)
    this->setCurrentWidget(qwidget);
}

void FFuQtTabbedWidgetStack::setCurrentTab(const std::string& name)
{
  // Loop over tabs and set current by pos index
  for (int idx = 0; idx < this->count(); idx++)
    if (this->tabText(idx).toStdString() == name) {
      this->setCurrentIndex(idx);
      return;
    }

  // If we get here, select first
  this->setCurrentIndex(0);
}
//----------------------------------------------------------------------------

std::string FFuQtTabbedWidgetStack::getCurrentTabName()
{
  return this->tabText(this->currentIndex()).toStdString();
}
//----------------------------------------------------------------------------

void FFuQtTabbedWidgetStack::setTabBarVisible(bool show)
{
  QTabBar* pTabBar = this->findChild<QTabBar*>();
  if (show)
    pTabBar->show();
  else
    pTabBar->hide();
}
//----------------------------------------------------------------------------

int FFuQtTabbedWidgetStack::getCurrentTabPosIdx()
{
  return this->currentIndex();
}

FFuComponentBase* FFuQtTabbedWidgetStack::getCurrentTabWidget()
{
  return dynamic_cast<FFuComponentBase*>(this->currentWidget());
}
//----------------------------------------------------------------------------
