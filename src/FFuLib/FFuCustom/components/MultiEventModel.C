/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * MultiEventModel.C
 *
 *  Created on: May 11, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/MultiEventModel.H"

MultiEventModel::MultiEventModel() {
	apEvents = new std::map<size_t, eventT*>;
	apObjects = new std::map<size_t, objectT*>;
	apParameters = new std::multimap<parameterForeignKeyT, parameterT*>;
	apObjectToEventConnections = new std::multimap<size_t, size_t>;
}

MultiEventModel::~MultiEventModel() {
	this->clean();
	delete apEvents;
	delete apObjects;
	delete apParameters;
	delete apObjectToEventConnections;
}

bool MultiEventModel::addEvent(size_t eventID, stringT eventName, double probability){
	eventT* pEvent = new Event(eventID, eventName, probability);
	apEvents->insert(std::make_pair(eventID, pEvent));

	return true;
}

bool MultiEventModel::addObject( size_t objectID, stringT objectName){
	objectT* pObject = new EventObject(objectID, objectName);
	apObjects->insert(std::make_pair(objectID, pObject));

	return true;
}

bool MultiEventModel::addParameter( parameterForeignKeyT foreignKey, stringT parameterName, valueT value ){
	parameterT* pParameter = new EventParameter(foreignKey.eventID, foreignKey.objectID, parameterName, value);
	apParameters->insert(std::make_pair(foreignKey, pParameter));

	apObjects->find(foreignKey.objectID)->second->addUsedParameterName(parameterName);

	return true;
}

bool MultiEventModel::objectToEventConnection(size_t objectID, size_t eventID){
	size_t prevSize = apObjectToEventConnections->size();
	apObjectToEventConnections->insert(std::make_pair(objectID, eventID ));
	size_t currSize = apObjectToEventConnections->size();

	return currSize > prevSize;
}

void MultiEventModel::clean(){
	for(std::map<size_t, eventT*>::iterator eventIt = apEvents->begin(); eventIt != apEvents->end(); ++eventIt)
		delete (*eventIt).second;

	apEvents->clear();

	for(std::map<size_t, objectT*>::iterator objIt = apObjects->begin(); objIt != apObjects->end(); ++objIt)
		delete (*objIt).second;

	apObjects->clear();

	for(std::multimap<parameterForeignKeyT, parameterT*>::iterator paramIt = apParameters->begin(); paramIt != apParameters->end(); ++paramIt)
		delete (*paramIt).second;

	apParameters->clear();

	apObjectToEventConnections->clear();
}

size_t MultiEventModel::getTableIndexOfEvent(size_t eventID){
	size_t count = 0;
	for(std::map<size_t,eventT*>::iterator eventIt = apEvents->begin(); eventIt != apEvents->end(); ++eventIt, count++)
		if((*eventIt).first == eventID)
			return count;

	return -1;
}
