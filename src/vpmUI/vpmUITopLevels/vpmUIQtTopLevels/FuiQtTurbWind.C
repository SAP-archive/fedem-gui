// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtTurbWind.H"
#include "vpmUI/Fui.H"
#include "vpmUI/Pixmaps/turbWind.xpm"

extern const char* info_xpm[];

#include <QApplication>
#include <QDesktopServices>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>


FuiTurbWind* FuiTurbWind::create(int xpos, int ypos, int width, int height,
                                 const char* title, const char* name)
{
  return new FuiQtTurbWind(NULL,xpos,ypos,width,height,title,name);
}


FuiQtTurbWind::FuiQtTurbWind(QWidget* parent,
                             int xpos, int ypos, int width, int height,
                             const char* title, const char* name)
  : FFuQtTopLevelShell(parent, xpos, ypos, width, height, title, name), pProcess(NULL)
{
  labTopImg = new QLabel(this);
  labTopImg->setObjectName(QString::fromUtf8("labTopImg"));
  labTopImg->setGeometry(QRect(0, -2, 581, 111));
  labTopImg->setFrameShape(QFrame::NoFrame);
  labTopImg->setPixmap(QPixmap(turbWind_xpm));

  frmTurbSpc = new QGroupBox(this);
  frmTurbSpc->setObjectName(QString::fromUtf8("frmTurbSpc"));
  frmTurbSpc->setGeometry(QRect(10, 120, 256, 321));

  labHubHeight = new QLabel(frmTurbSpc);
  labHubHeight->setObjectName(QString::fromUtf8("labHubHeight"));
  labHubHeight->setGeometry(QRect(10, 28, 81, 16));
  editHubHeight = new QLineEdit(frmTurbSpc);
  editHubHeight->setObjectName(QString::fromUtf8("editHubHeight"));
  editHubHeight->setGeometry(QRect(100, 25, 126, 20));
  editHubHeight->setMaxLength(20);

  labGridHeight = new QLabel(frmTurbSpc);
  labGridHeight->setObjectName(QString::fromUtf8("labGridHeight"));
  labGridHeight->setGeometry(QRect(10, 53, 71, 16));
  editGridHeight = new QLineEdit(frmTurbSpc);
  editGridHeight->setObjectName(QString::fromUtf8("editGridHeight"));
  editGridHeight->setGeometry(QRect(100, 50, 126, 20));
  editGridHeight->setMaxLength(20);

  labGridWidth = new QLabel(frmTurbSpc);
  labGridWidth->setObjectName(QString::fromUtf8("labGridWidth"));
  labGridWidth->setGeometry(QRect(10, 78, 71, 16));
  editGridWidth = new QLineEdit(frmTurbSpc);
  editGridWidth->setObjectName(QString::fromUtf8("editGridWidth"));
  editGridWidth->setGeometry(QRect(100, 75, 126, 20));
  editGridWidth->setMaxLength(20);

  labNumGridZ = new QLabel(frmTurbSpc);
  labNumGridZ->setObjectName(QString::fromUtf8("labNumGridZ"));
  labNumGridZ->setGeometry(QRect(10, 103, 71, 16));
  editNumGridZ = new QLineEdit(frmTurbSpc);
  editNumGridZ->setObjectName(QString::fromUtf8("editNumGridZ"));
  editNumGridZ->setGeometry(QRect(100, 100, 126, 20));
  editNumGridZ->setMaxLength(20);

  labNumGridY = new QLabel(frmTurbSpc);
  labNumGridY->setObjectName(QString::fromUtf8("labNumGridY"));
  labNumGridY->setGeometry(QRect(10, 128, 71, 16));
  editNumGridY = new QLineEdit(frmTurbSpc);
  editNumGridY->setObjectName(QString::fromUtf8("editNumGridY"));
  editNumGridY->setGeometry(QRect(100, 125, 126, 20));
  editNumGridY->setMaxLength(20);

  labTimeStep = new QLabel(frmTurbSpc);
  labTimeStep->setObjectName(QString::fromUtf8("labTimeStep"));
  labTimeStep->setGeometry(QRect(10, 153, 71, 16));
  editTimeStep = new QLineEdit(frmTurbSpc);
  editTimeStep->setObjectName(QString::fromUtf8("editTimeStep"));
  editTimeStep->setGeometry(QRect(100, 150, 126, 20));
  editTimeStep->setMaxLength(20);

  labDuration = new QLabel(frmTurbSpc);
  labDuration->setObjectName(QString::fromUtf8("labDuration"));
  labDuration->setGeometry(QRect(10, 178, 71, 16));
  editDuration = new QLineEdit(frmTurbSpc);
  editDuration->setObjectName(QString::fromUtf8("editDuration"));
  editDuration->setGeometry(QRect(100, 175, 126, 20));
  editDuration->setMaxLength(20);

  labIECturbc = new QLabel(frmTurbSpc);
  labIECturbc->setObjectName(QString::fromUtf8("labIECturbc"));
  labIECturbc->setGeometry(QRect(10, 203, 80, 16));
  cmbIECturbc = new QComboBox(frmTurbSpc);
  cmbIECturbc->setObjectName(QString::fromUtf8("cmbIECturbc"));
  cmbIECturbc->setGeometry(QRect(100, 200, 126, 22));
  cmbIECturbc->setEditable(true);

  labInfoA1 = new QLabel(frmTurbSpc);
  labInfoA1->setObjectName(QString::fromUtf8("labInfoA1"));
  labInfoA1->setGeometry(QRect(10, 229, 21, 16));
  labInfoA1->setPixmap(QPixmap(info_xpm));
  labInfoA2 = new QLabel(frmTurbSpc);
  labInfoA2->setObjectName(QString::fromUtf8("labInfoA2"));
  labInfoA2->setGeometry(QRect(30, 231, 46, 13));
  labInfoA3 = new QLabel(frmTurbSpc);
  labInfoA3->setObjectName(QString::fromUtf8("labInfoA3"));
  labInfoA3->setGeometry(QRect(10, 244, 231, 65));
  labInfoA3->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
  labInfoA3->setWordWrap(true);

  frmGenerate = new QGroupBox(this);
  frmGenerate->setObjectName(QString::fromUtf8("frmGenerate"));
  frmGenerate->setGeometry(QRect(279, 120, 291, 166+42));

  labTemplateFile = new QLabel(frmGenerate);
  labTemplateFile->setObjectName(QString::fromUtf8("labTemplateFile"));
  labTemplateFile->setGeometry(QRect(10, 28, 71, 16));
  editTemplateFile = new QLineEdit(frmGenerate);
  editTemplateFile->setObjectName(QString::fromUtf8("editTemplateFile"));
  editTemplateFile->setGeometry(QRect(100, 25, 156, 20));
  btnTemplateFile = new QPushButton(frmGenerate);
  btnTemplateFile->setObjectName(QString::fromUtf8("btnTemplateFile"));
  btnTemplateFile->setGeometry(QRect(260, 23, 21, 23));

  labOutputFolder = new QLabel(frmGenerate);
  labOutputFolder->setObjectName(QString::fromUtf8("labOutputFolder"));
  labOutputFolder->setGeometry(QRect(10, 53, 71, 16));
  editOutputFolder = new QLineEdit(frmGenerate);
  editOutputFolder->setObjectName(QString::fromUtf8("editOutputFolder"));
  editOutputFolder->setGeometry(QRect(100, 50, 156, 20));
  btnOutputFolder = new QPushButton(frmGenerate);
  btnOutputFolder->setObjectName(QString::fromUtf8("btnOutputFolder"));
  btnOutputFolder->setGeometry(QRect(260, 48, 21, 23));

  labWindType = new QLabel(frmGenerate);
  labWindType->setObjectName(QString::fromUtf8("labWindType"));
  labWindType->setGeometry(QRect(10, 78, 86, 16));
  cmbWindType = new QComboBox(frmGenerate);
  cmbWindType->setObjectName(QString::fromUtf8("cmbWindType"));
  cmbWindType->setGeometry(QRect(100, 75, 156, 22));

  labWindSpeed = new QLabel(frmGenerate);
  labWindSpeed->setObjectName(QString::fromUtf8("labWindSpeed"));
  labWindSpeed->setGeometry(QRect(10, 108, 71, 16));
  editWindSpeed = new QLineEdit(frmGenerate);
  editWindSpeed->setObjectName(QString::fromUtf8("editWindSpeed"));
  editWindSpeed->setGeometry(QRect(100, 105, 56, 20));

  labPLExp = new QLabel(frmGenerate);
  labPLExp->setObjectName(QString::fromUtf8("labPLExp"));
  labPLExp->setGeometry(QRect(168, 108, 30, 16));
  editPLExp = new QLineEdit(frmGenerate);
  editPLExp->setObjectName(QString::fromUtf8("editPLExp"));
  editPLExp->setGeometry(QRect(200, 105, 56, 20));

  labRefHt = new QLabel(frmGenerate);
  labRefHt->setObjectName(QString::fromUtf8("labRefHt"));
  labRefHt->setGeometry(QRect(10, 133, 71, 16));
  editRefHt = new QLineEdit(frmGenerate);
  editRefHt->setObjectName(QString::fromUtf8("editRefHt"));
  editRefHt->setGeometry(QRect(100, 130, 156, 20));
  editRefHt->setMaxLength(20);

  chkTowerPoints = new QCheckBox(frmGenerate);
  chkTowerPoints->setObjectName(QString::fromUtf8("chkTowerPoints"));
  chkTowerPoints->setGeometry(QRect(100, 155, 156, 20));

  labRandSeed1 = new QLabel(frmGenerate);
  labRandSeed1->setObjectName(QString::fromUtf8("labRandSeed1"));
  labRandSeed1->setGeometry(QRect(10, 183, 75, 16));
  editRandSeed1 = new QLineEdit(frmGenerate);
  editRandSeed1->setObjectName(QString::fromUtf8("editRandSeed1"));
  editRandSeed1->setGeometry(QRect(100, 180, 156, 20));

  btnGenerate = new QPushButton(this);
  btnGenerate->setObjectName(QString::fromUtf8("btnGenerate"));
  btnGenerate->setGeometry(QRect(280, 410, 91, 26));
  btnClose = new QPushButton(this);
  btnClose->setObjectName(QString::fromUtf8("btnClose"));
  btnClose->setGeometry(QRect(380, 410, 91, 26));
  btnHelp = new QPushButton(this);
  btnHelp->setObjectName(QString::fromUtf8("btnHelp"));
  btnHelp->setGeometry(QRect(480, 410, 91, 26));

  labInfoB1 = new QLabel(this);
  labInfoB1->setObjectName(QString::fromUtf8("labInfoB1"));
  labInfoB1->setGeometry(QRect(280, 332, 21, 16));
  labInfoB1->setPixmap(QPixmap(info_xpm));
  labInfoB2 = new QLabel(this);
  labInfoB2->setObjectName(QString::fromUtf8("labInfoB2"));
  labInfoB2->setGeometry(QRect(300, 334, 46, 13));
  labInfoB3 = new QLabel(this);
  labInfoB3->setObjectName(QString::fromUtf8("labInfoB3"));
  labInfoB3->setGeometry(QRect(280, 347, 301, 65));
  labInfoB3->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
  labInfoB3->setWordWrap(false);

  textEdit = new QTextEdit(this);
  textEdit->setObjectName(QString::fromUtf8("textEdit"));
  textEdit->setGeometry(QRect(10, 445, 561, 316));

  QWidget::setTabOrder(editHubHeight, editGridHeight);
  QWidget::setTabOrder(editGridHeight, editGridWidth);
  QWidget::setTabOrder(editGridWidth, editNumGridZ);
  QWidget::setTabOrder(editNumGridZ, editNumGridY);
  QWidget::setTabOrder(editNumGridY, editTimeStep);
  QWidget::setTabOrder(editTimeStep, editDuration);
  QWidget::setTabOrder(editDuration, cmbIECturbc);
  QWidget::setTabOrder(cmbIECturbc, editTemplateFile);
  QWidget::setTabOrder(editTemplateFile, btnTemplateFile);
  QWidget::setTabOrder(btnTemplateFile, editOutputFolder);
  QWidget::setTabOrder(editOutputFolder, btnOutputFolder);
  QWidget::setTabOrder(btnOutputFolder, cmbWindType);
  QWidget::setTabOrder(cmbWindType, editWindSpeed);
  QWidget::setTabOrder(editWindSpeed, editPLExp);
  QWidget::setTabOrder(editPLExp, editRefHt);
  QWidget::setTabOrder(editRefHt, chkTowerPoints);
  QWidget::setTabOrder(chkTowerPoints, editRandSeed1);
  QWidget::setTabOrder(editRandSeed1, btnGenerate);
  QWidget::setTabOrder(btnGenerate, btnClose);
  QWidget::setTabOrder(btnClose, btnHelp);
  QWidget::setTabOrder(btnHelp, textEdit);

  labTopImg->setText(QString());
  frmTurbSpc->setTitle(QApplication::translate("Dialog", "Turbine Specification for Wind", 0, QApplication::UnicodeUTF8));
  labHubHeight->setText(QApplication::translate("Dialog", "Hub height", 0, QApplication::UnicodeUTF8));
  labGridHeight->setText(QApplication::translate("Dialog", "Grid height ", 0, QApplication::UnicodeUTF8));
  editHubHeight->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  editGridHeight->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  labGridWidth->setText(QApplication::translate("Dialog", "Grid width", 0, QApplication::UnicodeUTF8));
  editGridWidth->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));

  labNumGridY->setText(QApplication::translate("Dialog", "Num. grid Y", 0, QApplication::UnicodeUTF8));
  editNumGridY->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
  labNumGridZ->setText(QApplication::translate("Dialog", "Num. grid Z", 0, QApplication::UnicodeUTF8));
  editNumGridZ->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
  labTimeStep->setText(QApplication::translate("Dialog", "Time step", 0, QApplication::UnicodeUTF8));
  editTimeStep->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  labDuration->setText(QApplication::translate("Dialog", "Duration", 0, QApplication::UnicodeUTF8));
  editDuration->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  cmbIECturbc->clear();
  cmbIECturbc->insertItems(0, QStringList()
   << QApplication::translate("Dialog", "A", 0, QApplication::UnicodeUTF8)
   << QApplication::translate("Dialog", "B", 0, QApplication::UnicodeUTF8)
   << QApplication::translate("Dialog", "C", 0, QApplication::UnicodeUTF8)
  );
  labIECturbc->setText(QApplication::translate("Dialog", "IEC turbine class", 0, QApplication::UnicodeUTF8));
  editRefHt->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  labRefHt->setText(QApplication::translate("Dialog", "Ref. height", 0, QApplication::UnicodeUTF8));
  labInfoA1->setText(QString());
  labInfoA2->setText(QApplication::translate("Dialog", "<b>Note</b>", 0, QApplication::UnicodeUTF8));
  labInfoA3->setText(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The 'Hub height' value is extracted from the Fedem model. You will typically not modify this value. The 'Ref. height' value is initially set to the same value as 'Hub height,' but you may wish to adjust this value.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
  frmGenerate->setTitle(QApplication::translate("Dialog", "Generate Wind File", 0, QApplication::UnicodeUTF8));
  labTemplateFile->setText(QApplication::translate("Dialog", "Template file", 0, QApplication::UnicodeUTF8));
  labWindType->setText(QApplication::translate("Dialog", "Turbulence type", 0, QApplication::UnicodeUTF8));
  cmbWindType->clear();
  cmbWindType->insertItems(0, QStringList()
   << QApplication::translate("Dialog", "NTM", 0, QApplication::UnicodeUTF8)
   << QApplication::translate("Dialog", "ETM - class 1 turbine", 0, QApplication::UnicodeUTF8)
   << QApplication::translate("Dialog", "ETM - class 2 turbine", 0, QApplication::UnicodeUTF8)
   << QApplication::translate("Dialog", "ETM - class 3 turbine", 0, QApplication::UnicodeUTF8)
  );
  labWindSpeed->setText(QApplication::translate("Dialog", "Wind speed", 0, QApplication::UnicodeUTF8));
  editWindSpeed->setText(QApplication::translate("Dialog", "0.0", 0, QApplication::UnicodeUTF8));
  labPLExp->setText(QApplication::translate("Dialog", "PLExp", 0, QApplication::UnicodeUTF8));
  editPLExp->setText(QApplication::translate("Dialog", "0.11", 0, QApplication::UnicodeUTF8));
  chkTowerPoints->setText(QApplication::translate("Dialog", "Include tower points", 0, QApplication::UnicodeUTF8));
  labRandSeed1->setText(QApplication::translate("Dialog", "Random seed 1", 0, QApplication::UnicodeUTF8));
  editRandSeed1->setText(QApplication::translate("Dialog", "1234567", 0, QApplication::UnicodeUTF8));
  labOutputFolder->setText(QApplication::translate("Dialog", "Output folder", 0, QApplication::UnicodeUTF8));
  btnTemplateFile->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
  btnOutputFolder->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
  btnGenerate->setText(QApplication::translate("Dialog", "Generate", 0, QApplication::UnicodeUTF8));
  btnClose->setText(QApplication::translate("Dialog", "Close", 0, QApplication::UnicodeUTF8));
  btnHelp->setText(QApplication::translate("Dialog", "Help", 0, QApplication::UnicodeUTF8));
  labInfoB2->setText(QApplication::translate("Dialog", "<b>Note</b>", 0, QApplication::UnicodeUTF8));
  labInfoB1->setText(QString());
  labInfoB3->setText(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Please fill in the fields above before generating a wind file.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">- The template file is copied and filled in by this tool.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">- The output folder receives all output from the tool.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">- Additional parameters are available in the template file.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));

  // Set up slots
  connect(btnTemplateFile, SIGNAL(clicked()), this, SLOT(onBtnTemplateFileClick()));
  connect(btnOutputFolder, SIGNAL(clicked()), this, SLOT(onBtnOutputFolderClick()));
  connect(btnGenerate, SIGNAL(clicked()), this, SLOT(onBtnGenerateClick()));
  connect(btnClose, SIGNAL(clicked()), this, SLOT(onBtnCloseClick()));
  connect(btnHelp, SIGNAL(clicked()), this, SLOT(onBtnHelpClick()));

  // Set up tooltips
  editHubHeight->setToolTip("The wind turbine hub height");
  editGridHeight->setToolTip("The height of the wind field grid");
  editGridWidth->setToolTip("The width of the wind field grid");
  editNumGridZ->setToolTip("Vertical grid-point matrix dimension");
  editNumGridY->setToolTip("Horizontal grid-point matrix dimension");
  editTimeStep->setToolTip("Time step");
  editDuration->setToolTip("Analysis and usable time duration");
  cmbIECturbc->setToolTip("IEC turbulence characteristics");
  editTemplateFile->setToolTip("Specifies the TurbSim INP-file");
  editOutputFolder->setToolTip("Specifies the target folder for output data");
  cmbWindType->setToolTip("IEC turbulence type");
  editWindSpeed->setToolTip("Mean wind speed at the reference height");
  editPLExp->setToolTip("Power law exponent");
  editRefHt->setToolTip("Height of the reference wind speed");
  chkTowerPoints->setToolTip("Generate binary tower time series");
  editRandSeed1->setToolTip("First random seed (-2147483648 to 2147483647)");
  btnGenerate->setToolTip("Click to generate wind files");
  btnClose->setToolTip("Click to close this tool");
  btnHelp->setToolTip("Click to view help file");

  this->setMinimumSize(580, 445);
  this->setMaximumSize(580, 770);
}


void FuiQtTurbWind::setValues(double hubHeight, double gridSize,
                              double timeInc, double duration,
                              const char* outputPath)
{
  editHubHeight->setText(QString::number(hubHeight));
  editGridHeight->setText(QString::number(gridSize));
  editGridWidth->setText(QString::number(gridSize));
  editNumGridZ->setText("16");
  editNumGridY->setText("16");
  editTimeStep->setText(QString::number(timeInc));
  editDuration->setText(QString::number(duration));
  cmbIECturbc->setCurrentIndex(1); // "B"
  QString templateFile(templateDir.c_str());
  templateFile.replace(" ","%20");
  templateFile.replace("\\","/");
  templateFile.append("/IecKai.inp");
  editTemplateFile->setText(templateFile);
  QString outputDir(outputPath);
  outputDir.replace(" ","%20");
  outputDir.replace("\\","/");
  editOutputFolder->setText(outputDir);
  cmbWindType->setCurrentIndex(1); // "ETM - class 1 turbine"
  editWindSpeed->setText("18.2");
  editPLExp->setText("0.11");
  editRefHt->setText(QString::number(hubHeight));
  chkTowerPoints->setChecked(true);
  editRandSeed1->setText("1234567");
}


void FuiQtTurbWind::onBtnTemplateFileClick()
{
  // Show file open dialog
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  templateDir.c_str(),
                                                  tr("INP Files (*.inp);;All Files (*.*)"));
  fileName.replace('\\','/');
  editTemplateFile->setText(fileName);
}


void FuiQtTurbWind::onBtnOutputFolderClick()
{
  // Get current path
  QString dir1 = editOutputFolder->text();

  // Get user's document directory
  if (dir1.count() == 0)
    dir1 = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);

  // Show directory dialog
  QString dir2 = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir1,
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  // Set field
  dir2.replace('\\', '/');
  editOutputFolder->setText(dir2);
}


static int locateEntry(const QByteArray& line, const char* szName)
{
  int pos1 = line.indexOf(szName);
  if (pos1 < 0) return -1; // Entry not found

  int pos2 = line.indexOf("-",pos1);
  if (pos2 <= pos1) return -2; // Entry is inside the comments section

  return pos1;
}

void setTurboSimLineEntryDouble(QByteArray& line, const char* szName, double value)
{
  int pos = locateEntry(line,szName);
  if (pos < 0) return;

  QString sVal;
  sVal.sprintf("%.8f   ",value);
  line.replace(0,pos,sVal.toAscii());
}

void setTurboSimLineEntryInt(QByteArray& line, const char* szName, int value)
{
  int pos = locateEntry(line,szName);
  if (pos < 0) return;

  QString sVal;
  sVal.sprintf("%d   ",value);
  line.replace(0,pos,sVal.toAscii());
}

void setTurboSimLineEntryStr(QByteArray& line, const char* szName, const QString& value, bool quote = true)
{
  int pos = locateEntry(line,szName);
  if (pos < 0) return;

  QString sVal;
  if (quote)
    sVal = "\"" + value + "\"   ";
  else
    sVal = value + "   ";
  line.replace(0,pos,sVal.toAscii());
}


void FuiQtTurbWind::onBtnGenerateClick()
{
  // Get field values
  double fHubHeight = editHubHeight->text().toDouble();
  double fGridHeight = editGridHeight->text().toDouble();
  double fGridWidth = editGridWidth->text().toDouble();
  int    nNumGridZ = editNumGridZ->text().toInt();
  int    nNumGridY = editNumGridY->text().toInt();
  double fTimeStep = editTimeStep->text().toDouble();
  double fDuration = editDuration->text().toDouble();
  QString strIECturbc = cmbIECturbc->currentText();
  QString strTemplateFile = editTemplateFile->text();
  QString strOutputFolder = editOutputFolder->text();
  int    nTurbulenceType = cmbWindType->currentIndex();
  double fWindSpeed = editWindSpeed->text().toDouble();
  double fPLExp = editPLExp->text().toDouble();
  double fRefHt = editRefHt->text().toDouble();
  bool   bTowerPoints = chkTowerPoints->isChecked();
  int    nRandSeed1 = editRandSeed1->text().toInt();

  // Get strTurbulenceType
  QString strTurbulenceType;
  switch (nTurbulenceType) {
  case 0: strTurbulenceType += "NTM"; break;
  case 1: strTurbulenceType += "1ETM"; break;
  case 2: strTurbulenceType += "2ETM"; break;
  case 3: strTurbulenceType += "3ETM"; break;
  }

  // Check fields
  if (fHubHeight <= 0.0) {
    QMessageBox msgBox(QMessageBox::Warning,
                       "Error",
                       "<b>Illegal entry:</b><br>"
                       "Hub height must be greater than 0.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }
  else if (fGridHeight <= 0.0 || fGridWidth <= 0.0) {
    QMessageBox msgBox(QMessageBox::Warning,
                       "Error",
                       "<b>Illegal entry:</b><br>"
                       "grid height and width must be greater than 0.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }
  else if (strTemplateFile.count() == 0) {
    QMessageBox msgBox(QMessageBox::Warning, "Error",
                       "<b>Illegal entry:</b><br>"
                       "You must specify a template file.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }
  else if (strOutputFolder.count() == 0) {
    QMessageBox msgBox(QMessageBox::Warning, "Error",
                       "<b>Illegal entry:</b><br>"
                       "You must specify a output folder.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }

  // Set output path
  QString strOutputFile = strOutputFolder;
  if (!strOutputFolder.endsWith('/') && !strOutputFolder.endsWith('\\'))
    strOutputFile += "/";
  switch (nTurbulenceType) {
  case 0: strOutputFile += "NTM/"; break;
  case 1: strOutputFile += "1ETM/"; break;
  case 2: strOutputFile += "2ETM/"; break;
  case 3: strOutputFile += "3ETM/"; break;
  }

  // Make output path
  QDir dir;
  dir.mkpath(strOutputFile);

  // Set output file name
  QString strFileName;
  strFileName.sprintf("windSpeed-%.2f-rs-%d.inp",fWindSpeed,nRandSeed1);
  strOutputFile += strFileName;

  // Clone template file
  QFile fileIn(strTemplateFile);
  QFile fileOut(strOutputFile);
  if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox msgBox(QMessageBox::Warning, "Error",
                       "Unable to open template file.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }
  else if (!fileOut.open(QIODevice::ReadWrite | QIODevice::Text)) {
    QMessageBox msgBox(QMessageBox::Warning, "Error",
                       "Unable to open output file.",
                       QMessageBox::Ok | QMessageBox::Cancel,
                       this);
    msgBox.exec();
    return;
  }
  while (!fileIn.atEnd()) {
    QByteArray line = fileIn.readLine();
    setTurboSimLineEntryDouble(line, "HubHt", fHubHeight);
    setTurboSimLineEntryDouble(line, "GridHeight", fGridHeight);
    setTurboSimLineEntryDouble(line, "GridWidth", fGridWidth);
    setTurboSimLineEntryInt(line, "NumGrid_Z", nNumGridZ);
    setTurboSimLineEntryInt(line, "NumGrid_Y", nNumGridY);
    setTurboSimLineEntryDouble(line, "TimeStep", fTimeStep);
    setTurboSimLineEntryDouble(line, "AnalysisTime", fDuration);
    setTurboSimLineEntryDouble(line, "UsableTime", fDuration);
    setTurboSimLineEntryStr(line, "IECturbc", strIECturbc);
    setTurboSimLineEntryStr(line, "IEC_WindType", strTurbulenceType);
    setTurboSimLineEntryDouble(line, "URef", fWindSpeed);
    setTurboSimLineEntryDouble(line, "PLExp", fPLExp);
    setTurboSimLineEntryDouble(line, "RefHt", fRefHt);
    setTurboSimLineEntryStr(line, "WrADTWR", QString(bTowerPoints ? "True" : "False"), false);
    setTurboSimLineEntryInt(line, "RandSeed1", nRandSeed1);
    fileOut.write(line);
  }
  fileIn.close();
  fileOut.close();

  // Show output field
  this->setMinimumSize(580,770);

  // Process arguments
  QStringList arguments;
  arguments << strOutputFile;

  // Start process
  textEdit->append("Generating " + strOutputFile + ".. Please wait..");
  pProcess = new QProcess(this);
  connect(pProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
  connect(pProcess, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));
  connect(pProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
  pProcess->start(turbsim_exe.c_str(), arguments);
  btnGenerate->setEnabled(false);
}


void FuiQtTurbWind::onBtnCloseClick()
{
  if (pProcess != NULL)
    pProcess->kill();

  this->close();
}


void FuiQtTurbWind::onBtnHelpClick()
{
  Fui::showCHM("dialogbox/windpower/3d-turbulent-wind.htm");
}


void FuiQtTurbWind::onReadyReadStandardOutput()
{
  QByteArray byteArray = pProcess->readAllStandardOutput();
  QStringList strLines = QString(byteArray).split("\n");
  foreach (QString line, strLines) {
    line.remove('\n');
    line.remove('\r');
    textEdit->append("<font color=#505050>" + line + "</font>");
  }
}


void FuiQtTurbWind::onReadyReadStandardError()
{
  QByteArray byteArray = pProcess->readAllStandardError();
  QStringList strLines = QString(byteArray).split("\n");
  foreach (QString line, strLines) {
    line.remove('\n');
    line.remove('\r');
    textEdit->append("<font color=#505050>" + line + "</font>");
  }
}


void FuiQtTurbWind::onFinished(int status, QProcess::ExitStatus)
{
  btnGenerate->setEnabled(true);
  textEdit->append(status ? "Failed!\n" : "Finished!\n");
}
