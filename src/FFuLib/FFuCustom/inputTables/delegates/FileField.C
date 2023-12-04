/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileField.C
 *
 *  Created on: Feb 9, 2012
 *      Author: runarhr
 */

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>

#include "FFuLib/FFuCustom/inputTables/delegates/FileField.H"


QString FileField::workingDirectory(QDir::homePath());


FileField::FileField(QWidget* parent) : QWidget(parent)
{
  apEdit = new QLineEdit();
  apEdit->setFrame(false);

  QPushButton* apBrowseButton = new QPushButton("...");
  apBrowseButton->setMaximumHeight(18);
  apBrowseButton->setMaximumWidth(24);

  QHBoxLayout* apLayout = new QHBoxLayout(this);
  apLayout->addWidget(apEdit);
  apLayout->addWidget(apBrowseButton);
  apLayout->setContentsMargins(0, 0, 0, 0);

  this->setLayout(apLayout);
  this->setAutoFillBackground(true); //If not set, the text in the cell will be seen behind the edit-display

  connect(apBrowseButton, SIGNAL(clicked()), this, SLOT(launchFileBrowser()));
}


void FileField::SetPath(const QString& cwd)
{
  if (QFile::exists(cwd)) workingDirectory = cwd;
}


void FileField::SetLine(const QString& line)
{
  apEdit->setText(line);
  emit(editDone(this));
}


QString FileField::GetLine() const
{
  return apEdit->text();
}


void FileField::launchFileBrowser()
{
  QFileInfo file(QFileDialog::getOpenFileName(this, tr("Select airfoil file"),
                                              workingDirectory, tr("Airfoil (*.dat)")));
  if (file.exists())
  {
    this->SetLine(file.absoluteFilePath());
    workingDirectory = file.absolutePath();
  }
}
