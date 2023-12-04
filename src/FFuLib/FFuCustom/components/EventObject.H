/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * EventObject.H
 *
 *  Created on: May 10, 2012
 *      Author: runarhr
 */

#ifndef EVENT_OBJECT_H
#define EVENT_OBJECT_H

#include <string>
#include <vector>

class EventObject {
public:
	typedef std::string  stringT;

	EventObject(size_t ID, stringT name);
	virtual ~EventObject();

	stringT  	getName() { return aName; }
	size_t		getID() { return aID; }
	std::vector<stringT>& getUsedParameterNames() { return aUsedParameterNames; }
	int 		getPosOfParameterType(std::string parameterType);

	bool touched() { return aTouched; }


	bool setName(stringT name);
	bool setID(size_t ID);
	bool addUsedParameterName(stringT parameterName);

	void touch();
	void unTouch();

private:
	stringT aName;
	size_t aID;

	bool aTouched;

	// Vector that contains all of the object-parameters actually changed by an event.
	// Is used to ensure the correcting positioning of subheaders and values within the spreadsheet
	std::vector<stringT> aUsedParameterNames;
};


#endif
