// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_MODEL_EXPORT_H
#define FUI_QT_MODEL_EXPORT_H

#include <QObject>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiModelExport.H"

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QGroupBox;
class QGridLayout;
class QCheckBox;
class QFileDialog;
class QTableWidget;

class FileSelectorWidget : public QWidget
{
  Q_OBJECT

private:
  QLineEdit* label;
  QPushButton* button;
  QHBoxLayout* layout;
  QString filter;
public slots:
  void browse();
public:
  FileSelectorWidget(QWidget* parent, const char* f);
  std::string getLabel() const;
  void setLabel(const std::string& lbl);
};


class FuiQtModelExport : public FFuQtTopLevelShell, public FuiModelExport
{
  Q_OBJECT

public:
  FuiQtModelExport(int xpos  = 100, int ypos = 100,
                   int width = 100, int height = 100,
                   const char* title = "Fedem",
                   const char* name = "FuiQtModelExport");
  virtual ~FuiQtModelExport() {}

private:
  void showEvent(QShowEvent* pEvent);
  void closeEvent(QCloseEvent* pEvent);

  void setUIValues(const FFuaUIValues* values);
  void getUIValues(FFuaUIValues* values);

public slots:
  void xport();
  void apply();
  void help();

private:
  // Stream
  QGroupBox* apStreamBox;
  QGridLayout* apStreamGrid;

  FileSelectorWidget* apStreamFileDialog;
  QLabel* apStreamFileLabel;
  QLabel* apStreamInpIndLabel;
  QLineEdit* apStreamInpIndEdit;
  QLabel* apStreamOutIndLabel;
  QLineEdit* apStreamOutIndEdit;
  QLabel* apStreamWindowLabel;
  QLineEdit* apStreamWindowEdit;
  QCheckBox* apStreamStateCheckbox;

  // Batch
  QGroupBox* apBatchBox;
  QGridLayout* apBatchGrid;

  FileSelectorWidget* apBatchFileDialog;
  QLabel* apBatchFileLabel;
  QLabel* apBatchInpIndLabel;
  QLineEdit* apBatchInpIndEdit;
  QCheckBox* apBatchSurfCheckbox;
  QCheckBox* apBatchStressCheckbox;
  QCheckBox* apBatchFECheckbox;

  // FMU
  QGroupBox* apFMUBox;
  QGridLayout* apFMUGrid;

  FileSelectorWidget* apFMUFileDialog;
  QLabel* apFMUFileLabel;

  // Functions
  QLabel* apInputsLabel;
  QLabel* apOutputsLabel;

  // Main
  QPushButton* apExportButton;
  QPushButton* apApplyButton;
  QPushButton* apCancelButton;
  QPushButton* apHelpButton;

  QVBoxLayout* apAppLayout;
  QVBoxLayout* apFunctionLayout;
  QHBoxLayout* apWidgetLayout;
  QVBoxLayout* apMainLayout;
  QHBoxLayout* apDialogButtonLayout;

  QTableWidget* inputTable;
  QTableWidget* outputTable;
};

#endif
