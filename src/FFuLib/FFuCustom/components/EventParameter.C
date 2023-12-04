/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * EventParameter.C
 *
 *  Created on: May 11, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/EventParameter.H"

EventParameter::EventParameter(size_t eventID, size_t objectID, stringT name, QVariant value) {
	aEventID = eventID;
	aObjectID = objectID;
	name.size() ? aName = name : aName = "No Name";
	value.isValid() ? aValue = value : aValue = QVariant("No value");
}

EventParameter::~EventParameter() {
	// TODO Auto-generated destructor stub
}

bool EventParameter::setName( stringT name ){
	if(!name.size())
		return false;

	aName = name;
	return true;
}

bool EventParameter::setValue( QVariant value ){
	if(!value.isValid())
		return false;

	aValue = value;
	return true;
}
