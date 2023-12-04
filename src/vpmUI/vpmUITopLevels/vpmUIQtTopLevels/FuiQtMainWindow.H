// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_MAIN_WINDOW_H
#define FUI_QT_MAIN_WINDOW_H

#include <QMainWindow>

#include "vpmUI/vpmUITopLevels/FuiMainWindow.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"

class QProgressBar;
class QLabel;
class QFrame;
class QStackedWidget;


class FuiQtMainWindow : public QMainWindow,
			public FuiMainWindow, public FFuQtComponentBase
{
public:
  FuiQtMainWindow();
  virtual ~FuiQtMainWindow() {}

  void addDefinitionWidget(QWidget* w);
  void removeDefinitionWidget(QWidget* w);

  virtual void setStatusBarMessage(const char* message, int ms = 0);
  virtual void clearStatusBarMessage();

  virtual void removeToolBar(int toolBar);

private:
  // Reimplementing the Qt eventhandeler on window manager close
  virtual void closeEvent(QCloseEvent* e);

  void onHintDone();
  void onHintCancel();

public:
  virtual void setTitle(const char* title);
  virtual const char* getTitle() const;

  virtual void setHintText(const char* text);
  virtual void showHintPanel(bool b);

  virtual void setStatus(const char* statusText);

  virtual void enableSubSteps(int steps);
  virtual void setSubStep(int step);
  virtual void disableSubSteps();

  virtual void displayTime(int hour, int min, int sec);
  virtual void clearTime();

  virtual void setSubTask(const char* taskText);

  virtual void enableProgress(int nSteps);
  virtual void setProgress(int progressStep);
  virtual void disableProgress();

private:
  QProgressBar*   myProgBar;
  QLabel*         myStatusLabel;
  QLabel*         mySubStepLabel;
  QLabel*         mySubTaskLabel;
  QLabel*         myHintLabel;
  QFrame*         myMainHintFrame;
  QStackedWidget* myDefinitionWidgetStack;

  int mySubStepCount;
};

#endif
