/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * EventObject.C
 *
 *  Created on: May 10, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/EventObject.H"

EventObject::EventObject(size_t ID, stringT name) {
	aID = ID;
	aName = name;

	aTouched = false;
}

EventObject::~EventObject() {
	// TODO Auto-generated destructor stub
}

bool EventObject::setName(stringT name){
	if(name == "")
		return false;

	aName = name;
	return true;
}

bool EventObject::setID(size_t ID){
	aID = ID;
	return true;
}

void EventObject::touch(){
	aTouched = true;
}

void EventObject::unTouch(){
	aTouched = false;
}

bool EventObject::addUsedParameterName(stringT parameterName){
	// Check if parameter is already in use.
	for (const std::string& param : aUsedParameterNames)
		if (param == parameterName)
			return false;

	// If not, then add it.
	aUsedParameterNames.push_back(parameterName);

	return true;
}

int EventObject::getPosOfParameterType(std::string parameterType){
	for (size_t i = 0; i < aUsedParameterNames.size(); i++)
		if (aUsedParameterNames.at(i) == parameterType)
			return i;

	return -1;
}
