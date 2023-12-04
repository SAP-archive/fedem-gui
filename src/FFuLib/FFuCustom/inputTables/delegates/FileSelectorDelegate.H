/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileSelectorDelegate.H
 *
 *  Created on: Mar 6, 2012
 *      Author: runarhr
 */

#ifndef FILE_SELECTOR_DELEGATE_H
#define FILE_SELECTOR_DELEGATE_H

#include <QStyledItemDelegate>

class QVBoxLayout;


/*!
  StyledItemDelegate-class for selecting a file of a certain type from
  a pulldown menu. Can be used as a editor e.g. in a spreadsheet.
  Contains a path to the folder to be searched,
  and a list of filters for the files to be searched for.
*/

class FileSelectorDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  FileSelectorDelegate(QObject* parent = NULL) : QStyledItemDelegate(parent) {}
  virtual ~FileSelectorDelegate() {}

  // Inherited from QStyledItemDelegate
  virtual void paint(QPainter* painter,
                     const QStyleOptionViewItem& option,
                     const QModelIndex& index) const;
  virtual QWidget* createEditor(QWidget* parent,
                                const QStyleOptionViewItem&,
                                const QModelIndex&) const;
  virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
  virtual QString displayText(const QVariant& value, const QLocale&) const;
  virtual void setModelData(QWidget* editor, QAbstractItemModel* model,
                            const QModelIndex& index) const;
  QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const;

  void setReferencePath(const QString& path) { aReferencePath = path; }
  void setFolderPaths(const QStringList& paths) { aFolderPaths = paths; }
  void setFilterList(const QStringList& filters) { aFilterList = filters; }

  QStringList getFolderPaths() const { return aFolderPaths; }
  QStringList getFilterList() const { return aFilterList; }

private:
  QVBoxLayout* apMainLayout;
  QStringList  aFolderPaths;
  QStringList  aFilterList;
  QString      aReferencePath;
};

#endif
