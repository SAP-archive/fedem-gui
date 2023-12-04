/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * DoubleFieldDelegate.H
 *
 *  Created on: May 31, 2012
 *      Author: runarhr
 */

#ifndef DOUBLE_FIELD_DELEGATE_H
#define DOUBLE_FIELD_DELEGATE_H

#include <QStyledItemDelegate>


/*!
 * StyledItemDelegate-class for custom display of double-fields in a spreadsheet.
 */

class DoubleFieldDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	DoubleFieldDelegate(int numOfDecimals=2, double step=0.0, QObject* parent=NULL);
	virtual ~DoubleFieldDelegate();

	virtual QString displayText(const QVariant& value, const QLocale& locale) const;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;

private:
	int aNumOfDecimals;
	double aStep;
};

#endif /* DOUBLEFIELDDELEGATE_H */
