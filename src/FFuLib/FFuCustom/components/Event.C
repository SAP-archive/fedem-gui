// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuCustom/components/Event.H"
#include <iostream>

Event::Event(size_t ID, stringT name, double probability ){
	aID = ID;
	aName = name;
	aProbability = probability;

	aTouched = false;
}

Event::~Event(){
}


bool Event::setName(stringT name){
	if(name == "")
		return false;

	aName = name;
	return true;
}

bool Event::setID(size_t ID){
	aID = ID;
	return true;
}

bool Event::setProbability(double probability){
	aProbability = probability;
	return true;
}

void Event::touch(){
	aTouched = true;
}

void Event::unTouch(){
	aTouched = false;
}
