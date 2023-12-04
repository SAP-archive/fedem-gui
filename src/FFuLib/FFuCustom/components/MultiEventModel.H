/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * MultiEventModel.H
 *
 *  Created on: May 11, 2012
 *      Author: runarhr
 */

#ifndef MULTIEVENTMODEL_H
#define MULTIEVENTMODEL_H

#include <map>

#include <QVariant>

#include "FFuLib/FFuCustom/components/Event.H"
#include "FFuLib/FFuCustom/components/EventObject.H"
#include "FFuLib/FFuCustom/components/EventParameter.H"

struct parameterForeignKeyT{
	parameterForeignKeyT(size_t eID, size_t oID) : eventID(eID), objectID(oID){}
	bool operator<(const parameterForeignKeyT& key) const { return (eventID < key.eventID) || ( (eventID == key.eventID) && (objectID < key.objectID) ); }
	size_t eventID;
	size_t objectID;
};

class MultiEventModel {
public:
	typedef std::string 				stringT;
	typedef QVariant 					valueT;
	typedef Event						eventT;
	typedef EventObject					objectT;
	typedef EventParameter				parameterT;

	MultiEventModel();
	virtual ~MultiEventModel();

	bool addEvent( size_t eventID, stringT eventName,  double probability);
	bool addObject( size_t objectID, stringT objectName);
	bool addParameter( parameterForeignKeyT foreignKey, stringT parameterName, valueT value );

	std::map<size_t, eventT*>* getEvents(){ return apEvents; }
	std::map<size_t, objectT*>* getObjects(){ return apObjects; }
	std::multimap<size_t, size_t>* getObjectToEventConnections(){return apObjectToEventConnections; }
	std::multimap<parameterForeignKeyT, parameterT*>* getParameters(){ return apParameters; }

	size_t getTableIndexOfEvent(size_t eventID);

	bool objectToEventConnection(size_t objectID, size_t eventID);

	void clean();

private:
	std::map<size_t, eventT*>* apEvents;
	std::map<size_t, objectT*>* apObjects;
	std::multimap<parameterForeignKeyT, parameterT*>* apParameters;
	std::multimap<size_t, size_t>* apObjectToEventConnections;
};

#endif /* MULTIEVENTMODEL_H */
