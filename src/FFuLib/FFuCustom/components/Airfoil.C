/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * Airfoil.C
 *
 *  Created on: May 2, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/Airfoil.H"

Airfoil::Airfoil() {
	apTableData = new QVector<QVector<QVariant>*>;
}

Airfoil::~Airfoil() {
	apTableData->clear();
	delete apTableData;
}


void Airfoil::Touch(){
	touched = true;
}

void Airfoil::UnTouch(){
	touched = false;
}

void Airfoil::SetIsTemplate(bool exists){
	isTemplate = exists;
}

void Airfoil::SetFileExists(bool exists){
	fileExists = exists;
}
