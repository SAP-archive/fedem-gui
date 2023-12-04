/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileFieldDelegate.C
 *
 *  Created on: Feb 21, 2012
 *      Author: runarhr
 */

#include <QPainter>
#include <QDir>

#include "FFuLib/FFuCustom/inputTables/delegates/FileFieldDelegate.H"
#include "FFuLib/FFuCustom/inputTables/delegates/FileField.H"


FileFieldDelegate::FileFieldDelegate(const std::string& defaultPath, QObject* parent)
  : QStyledItemDelegate(parent)
{
  FileField::SetPath(defaultPath.c_str());
}


void FileFieldDelegate::setBladePath(const std::string& bladePath)
{
  if (bladePath.empty() || !QFile::exists(bladePath.c_str())) return;

  QFileInfo bladeFile(bladePath.c_str());
  FileField::SetPath(bladeFile.dir().absolutePath() + "/" +
                     bladeFile.baseName() + "_airfoils");
}


QWidget* FileFieldDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
  QWidget* editor = new FileField(parent);
  connect(editor, SIGNAL(editDone(QWidget*)), this, SLOT(commit(QWidget*)));
  return editor;
}


void FileFieldDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  static_cast<FileField*>(editor)->SetLine(index.model()->data(index,Qt::DisplayRole).toString());
}


void FileFieldDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QVariant value = static_cast<FileField*>(editor)->GetLine();
  if (value.toString().size())
    model->setData(index, value, Qt::EditRole);
}


QSize FileFieldDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
  return QSize(30, 20);
}


QString FileFieldDelegate::displayText(const QVariant& value, const QLocale&) const
{
  return value.toString().split(QDir::separator()).last(); // Only display the filename, not the full path
}


void FileFieldDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  if (index.isValid())
  {
    // Move focus to airfoils-folder
    QDir folder(FileField::GetPath());

    QVariant value = index.model()->data(index,Qt::DisplayRole);
    QString airfoilPath = QDir::toNativeSeparators(value.toString());

    // Check if airfoil exists
    if (folder.exists(airfoilPath)) {
      // Check if path is relative to blades local folder
      QStringList a = airfoilPath.split(QDir::separator());
      if (a.size() == 1) // We have an existing airfoil with relative path
        painter->fillRect(option.rect, QColor(215,255,215));
      else // We have an existing airfoil with absolute path
        painter->fillRect(option.rect, QColor(255,255,208));
    }
    else // not found
      painter->fillRect(option.rect, QColor(255,155,155));
  }

  this->QStyledItemDelegate::paint(painter, option, index);
}


void FileFieldDelegate::commit(QWidget* editor)
{
  emit(commitData(editor));
  emit(closeEditor(editor));
}
