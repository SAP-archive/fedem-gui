// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_TURB_WIND_H
#define FUI_QT_TURB_WIND_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiTurbWind.H"

#include <QProcess>

class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;


class FuiQtTurbWind : public FFuQtTopLevelShell, public FuiTurbWind
{
  Q_OBJECT

public:
  FuiQtTurbWind(QWidget* parent = NULL,
                int xpos = 100, int ypos = 100,
                int width = 100, int height = 100,
                const char* title= "Fedem",
                const char* name = "FuiQtTurbWind");
  virtual ~FuiQtTurbWind() {}

  virtual void setValues(double hubHeight, double gridSize,
                         double timeInc, double duration,
                         const char* outputPath);

private:
  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiTurbWind::setSensitivity(isSensitive);
  }

private slots:
  void onBtnTemplateFileClick();
  void onBtnOutputFolderClick();
  void onBtnGenerateClick();
  void onBtnCloseClick();
  void onBtnHelpClick();
  void onReadyReadStandardOutput();
  void onReadyReadStandardError();
  void onFinished(int status, QProcess::ExitStatus);

private:
  QProcess*    pProcess;
  QLabel*      labTopImg;
  QGroupBox*   frmTurbSpc;
  QLabel*      labHubHeight;
  QLabel*      labGridHeight;
  QLineEdit*   editHubHeight;
  QLineEdit*   editGridHeight;
  QLabel*      labGridWidth;
  QLineEdit*   editGridWidth;
  QLineEdit*   editNumGridY;
  QLabel*      labNumGridY;
  QLabel*      labNumGridZ;
  QLineEdit*   editNumGridZ;
  QLabel*      labTimeStep;
  QLineEdit*   editTimeStep;
  QLabel*      labDuration;
  QLineEdit*   editDuration;
  QComboBox*   cmbIECturbc;
  QLabel*      labIECturbc;
  QLineEdit*   editRefHt;
  QLabel*      labRefHt;
  QLabel*      labInfoA1;
  QLabel*      labInfoA2;
  QLabel*      labInfoA3;
  QGroupBox*   frmGenerate;
  QLabel*      labTemplateFile;
  QLabel*      labWindType;
  QComboBox*   cmbWindType;
  QLabel*      labWindSpeed;
  QLineEdit*   editWindSpeed;
  QLabel*      labPLExp;
  QLineEdit*   editPLExp;
  QCheckBox*   chkTowerPoints;
  QLabel*      labRandSeed1;
  QLineEdit*   editRandSeed1;
  QLabel*      labOutputFolder;
  QLineEdit*   editOutputFolder;
  QLineEdit*   editTemplateFile;
  QPushButton* btnTemplateFile;
  QPushButton* btnOutputFolder;
  QPushButton* btnGenerate;
  QPushButton* btnClose;
  QPushButton* btnHelp;
  QLabel*      labInfoB2;
  QLabel*      labInfoB1;
  QLabel*      labInfoB3;
  QTextEdit*   textEdit;
};

#endif
