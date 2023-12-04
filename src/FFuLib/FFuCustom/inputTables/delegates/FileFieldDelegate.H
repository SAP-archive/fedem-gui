/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileFieldDelegate.H
 *
 *  Created on: Feb 21, 2012
 *      Author: runarhr
 */

#ifndef _FILE_FIELD_DELEGATE_H
#define _FILE_FIELD_DELEGATE_H

#include <QStyledItemDelegate>
#include <string>


/*!
 * StyledItemDelegate-class for entering a file-name in a QlineEdit, or selecting a file with file-dialog
 * Can be used as a editor e.g. in a spreadsheet.
 */

class FileFieldDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  FileFieldDelegate(const std::string& ddefaultPath, QObject* parent);
  virtual ~FileFieldDelegate() {}

  void setBladePath(const std::string& bladePath);

  // Inherited from QStyledItemDelegate
  virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const;
  virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
  virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
  virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  virtual QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const;
  virtual QString displayText(const QVariant& value, const QLocale&) const;

public slots:
  void commit(QWidget* editor);
};

#endif
