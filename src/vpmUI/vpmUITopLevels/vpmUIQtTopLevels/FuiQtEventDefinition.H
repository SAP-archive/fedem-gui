// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_EVENT_DEFINITION_H
#define FUI_QT_EVENT_DEFINITION_H

#include <QObject>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiEventDefinition.H"

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;
class MultiEventModel;


class FuiQtEventDefinition : public FFuQtTopLevelShell, public FuiEventDefinition
{
  Q_OBJECT

public:
  FuiQtEventDefinition(QWidget* parent = 0,
                       int xpos =100, int ypos =100,
                       int width=100, int height=100,
                       const char* title= "Fedem",
                       const char* name = "FuiQtEventDefinition");
  virtual ~FuiQtEventDefinition() {}

private:
  virtual void setSensitivity(bool) {} // Always sensitive since this dialog is read only

  void showEvent(QShowEvent* pEvent);
  void closeEvent(QCloseEvent* pEvent);

public slots:
  void help();

private:
  // Widgets
  QPushButton* apCloseButton;
  QPushButton* apHelpButton;
  QTableWidget* pTable;

  // Layouts
  QVBoxLayout* apMainLayout;
  QHBoxLayout* apDialogButtonLayout;

  MultiEventModel* apMultiEventModel;
};

#endif
