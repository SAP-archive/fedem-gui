/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * HeaderDelegate.H
 *
 *  Created on: May 23, 2012
 *      Author: runarhr
 */

#ifndef HEADER_DELEGATE_H
#define HEADER_DELEGATE_H

#include <QStyledItemDelegate>

class QPainter;


/*!
  StyledItemDelegate-class for making a regular spreadsheet-cell
  look like a header.
*/

class HeaderDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  HeaderDelegate(QObject* parent = NULL) : QStyledItemDelegate(parent) {}
  virtual ~HeaderDelegate() {}

  // Inherited from QStyledItemDelegate
  virtual void paint(QPainter* painter,
                     const QStyleOptionViewItem& option,
                     const QModelIndex& index) const;
};

#endif
