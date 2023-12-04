/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * EventParameter.H
 *
 *  Created on: May 11, 2012
 *      Author: runarhr
 */

#ifndef EVENT_PARAMETER_H
#define EVENT_PARAMETER_H

#include <string>
#include <QVariant>

class EventParameter {
public:
	typedef std::string  stringT;
	typedef QVariant 	 valueT;

	EventParameter(size_t eventID, size_t objectID, stringT name, QVariant value);
	virtual ~EventParameter();

	stringT		getName()		{ return aName; }
	size_t		getObjectID()	{ return aObjectID; }
	size_t		getEventID()	{ return aEventID; }
	QVariant	getValue()		{ return aValue; }

	bool		touched()		{ return aTouched; }

	void		touch()			{ aTouched = true; }
	void		unTouch()		{ aTouched = false; }

	bool		setName( stringT name );
	bool		setValue( QVariant value );

private:
	stringT  aName;
	size_t   aEventID;
	size_t   aObjectID;
	QVariant aValue;

	bool 	 aTouched;
};
#endif /* EVENT_PARAMETER_H */
