// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
	typedef std::string stringT;

	Event(size_t ID, stringT name, double probability);
	~Event();


	stringT  getName() { return aName; }
	size_t		getID() { return aID; }
	double		getProbability() {return aProbability; }

	bool touched() { return aTouched; }


	bool setName(stringT name);
	bool setID(size_t ID);
	bool setProbability(double probability);

	void touch();
	void unTouch();

private:
	stringT aName;
	size_t aID;
	double aProbability;

	bool aTouched;
};


#endif
