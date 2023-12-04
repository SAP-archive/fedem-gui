/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * FileSelectorDelegate.C
 *
 *  Created on: Mar 6, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/inputTables/delegates/FileSelectorDelegate.H"
#include "FFuLib/FFuCustom/mvcModels/AirfoilSelectionModel.H"

#include <QVBoxLayout>
#include <QComboBox>
#include <QDir>
#include <QPainter>


QWidget* FileSelectorDelegate::createEditor(QWidget* parent,
                                            const QStyleOptionViewItem&,
                                            const QModelIndex&) const
{
  return new QComboBox(parent);
}


void FileSelectorDelegate::setEditorData(QWidget* editor,
                                         const QModelIndex& index) const
{
  // Create a pulldown-menu as editor-widget.
  // Fill it with entries, based on .dat files in AeroData-folder
  QComboBox* pPullDown = static_cast<QComboBox*>(editor);

  std::vector<std::string> airfoilPaths;
  AirfoilSelectionModel::instance()->getAllItems(airfoilPaths);

  for (const std::string& path : airfoilPaths)
  {
    QStringList stringParts = QString(path.c_str()).split(QDir::separator());
    // Only display the filename, not the full path
    pPullDown->addItem(QString(stringParts.last()), path.c_str());
  }

  // Set selected item based on value in spreadsheet
  QVariant value = index.model()->data(index,Qt::DisplayRole);
  if (value == "") return;

  pPullDown->setCurrentIndex(pPullDown->findText(value.toString().split(QDir::separator()).last()));
}


void FileSelectorDelegate::setModelData(QWidget* editor,
                                        QAbstractItemModel* model,
                                        const QModelIndex& index) const
{
  QComboBox* comboBox = static_cast<QComboBox*>(editor);
  QVariant value = comboBox->itemData(comboBox->currentIndex());

  std::vector<std::string> airfoilPaths;
  AirfoilSelectionModel::instance()->getAllItems(airfoilPaths);

  for (const std::string& path : airfoilPaths)
    if (QString(path.c_str()) == value)
      model->setData(index,QDir::toNativeSeparators(path.c_str()),Qt::EditRole);
}


QSize FileSelectorDelegate::sizeHint(const QStyleOptionViewItem&,
                                     const QModelIndex&) const
{
  return QSize(30, 20);
}


QString FileSelectorDelegate::displayText(const QVariant& value,
                                          const QLocale&) const
{
  // Only display the filename, not the full path
  return value.toString().split(QDir::separator()).last();
}


void FileSelectorDelegate::paint(QPainter* painter,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
  QVariant value = index.model()->data(index,Qt::DisplayRole);
  if (!QFile::exists(value.toString()))
    painter->fillRect(option.rect,QColor(255,51,51));

  this->QStyledItemDelegate::paint(painter,option,index);
}
