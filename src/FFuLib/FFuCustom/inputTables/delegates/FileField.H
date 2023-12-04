/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileField.H
 *
 *  Created on: Feb 9, 2012
 *      Author: runarhr
 */

#ifndef _FILE_FIELD_H
#define _FILE_FIELD_H

#include <QWidget>

class QLineEdit;


/*!
 * A widget that contains a line-edit field for displaying/editing a file path
 * pointing to a .dat-file, and a button for launching a file dialog that will
 * set its returned value in the line-edit field.
 *
 * Intended to be used in an InputTable, with a delegate.
 */

class FileField : public QWidget
{
  Q_OBJECT

public:
  FileField(QWidget* parent);
  virtual ~FileField() {}

  static void SetPath(const QString& cwd);
  static const QString& GetPath() { return workingDirectory; }

  void SetLine(const QString& line);
  QString GetLine() const;

private slots:
  void launchFileBrowser();

private:
  QLineEdit* apEdit;

  static QString workingDirectory;

signals:
  void editDone(QWidget*);
};

#endif
