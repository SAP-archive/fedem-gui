/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * DoubleFieldDelegate.C
 *
 *  Created on: May 31, 2012
 *      Author: runarhr
 */

#include <QDoubleSpinBox>

#include "FFuLib/FFuCustom/inputTables/delegates/DoubleFieldDelegate.H"

DoubleFieldDelegate::DoubleFieldDelegate(int numOfDecimals, double step, QObject* parent) :
QStyledItemDelegate(parent){
	aNumOfDecimals = numOfDecimals;
	aStep = step;
}

DoubleFieldDelegate::~DoubleFieldDelegate() {
	// TODO Auto-generated destructor stub
}


QString DoubleFieldDelegate::displayText ( const QVariant & value, const QLocale & locale ) const{
	if(qAbs(value.toDouble()) < 1000){
		return locale.toString(value.toDouble(), 'f', aNumOfDecimals);
	}
	else{
		return locale.toString(value.toDouble(), 'E', aNumOfDecimals);
	}

}


void DoubleFieldDelegate::setEditorData(QWidget *editor, const QModelIndex& index ) const{
	QDoubleSpinBox* pSpinBox = static_cast<QDoubleSpinBox*>( editor );
	pSpinBox->setDecimals(4);
	pSpinBox->setSingleStep(aStep);
	pSpinBox->setValue(index.model()->data(index, Qt::DisplayRole).toDouble());
}
