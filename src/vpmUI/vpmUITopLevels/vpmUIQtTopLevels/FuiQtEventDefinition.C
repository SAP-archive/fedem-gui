// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QCloseEvent>

#include "FuiQtEventDefinition.H"
#include "vpmUI/Fui.H"

#include "vpmDB/FmDB.H"
#include "vpmDB/FmSimulationEvent.H"
#include "FFaLib/FFaContainers/FFaFieldBase.H"

#include "FFuLib/FFuCustom/components/MultiEventModel.H"
#include "FFuLib/FFuCustom/inputTables/delegates/HeaderDelegate.H"


FuiEventDefinition* FuiEventDefinition::create(int xpos, int ypos, int width, int height,
					       const char* title, const char* name)
{
  return new FuiQtEventDefinition(NULL, xpos, ypos, width, height, title, name);
}

FuiQtEventDefinition::FuiQtEventDefinition(QWidget* parent,
					   int xpos, int ypos, int width, int height,
					   const char* title, const char* name) :
  FFuQtTopLevelShell(parent, xpos, ypos, width, height, title, name)
{
	// ** Create Widgets **
	pTable = new QTableWidget(this);
	apCloseButton = new QPushButton("Close");
	apHelpButton = new QPushButton("Help");

	// ** Create layouts **
	apMainLayout = new QVBoxLayout();
	apDialogButtonLayout = new QHBoxLayout();
	apMultiEventModel = NULL;

	// ** Initialize layouts **
	apDialogButtonLayout->addWidget(apCloseButton);
	apDialogButtonLayout->addWidget(apHelpButton);
	apDialogButtonLayout->insertStretch(-1);

	apMainLayout->addWidget(pTable);
	apMainLayout->addLayout(apDialogButtonLayout);
	apMainLayout->setContentsMargins(0, 0, 0, 0);

	this->setLayout(apMainLayout);

	// Buttons
	QObject::connect( apCloseButton, SIGNAL(clicked()), this, SLOT( close() ) );
	QObject::connect( apHelpButton, SIGNAL(clicked()), this, SLOT( help() ) );
}


// ************SLOTS**********

void FuiQtEventDefinition::showEvent(QShowEvent*)
{
	std::vector<FmSimulationEvent*> apSimulationEvents;
	FmDB::getAllSimulationEvents(apSimulationEvents);
	if (apSimulationEvents.empty()) return;

	pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	apMultiEventModel = new MultiEventModel();

	// Create model of all simulation-events.
	for (std::vector<FmSimulationEvent*>::const_iterator eit = apSimulationEvents.begin(); eit != apSimulationEvents.end(); ++eit) {
		int eventID = (*eit)->getID();
		apMultiEventModel->addEvent(eventID, (*eit)->getItemDescr(), (*eit)->getProbability());

		// Get list of all Fm-objects in the FmSimulationEvent. pShadowObjects contains the objects with fields to change.
		// pObjectsToChange contains the actual simulation-objects the changes will be applied to. The latter is used to get the id of the object
		std::vector<FmSimulationModelBase*> pObjectsToChange, pShadowObjects;
		(*eit)->getObjects(pObjectsToChange);
		(*eit)->getManipulatorObjects(pShadowObjects);

		// Create objects in MultiEventModel, based on Fm-objects
		for (size_t i = 0; i < pShadowObjects.size() && i < pObjectsToChange.size(); i++) {
			int objectID = pObjectsToChange.at(i)->getBaseID();

			// Check if object already exists
			if (apMultiEventModel->getObjects()->find(objectID) == apMultiEventModel->getObjects()->end())
			  apMultiEventModel->addObject(objectID, std::string(pShadowObjects.at(i)->getTypeIDName()) + " " + pObjectsToChange.at(i)->getIdPath(false));
			apMultiEventModel->objectToEventConnection(objectID, eventID);

			// Add fields from Fm-objects to MultiEventModel as EventParameter objects
			std::map<std::string,FFaFieldBase*> fieldMap;
			pShadowObjects.at(i)->FFaFieldContainer::getFields(fieldMap);

			for (std::map<std::string,FFaFieldBase*>::const_iterator fieldIt = fieldMap.begin(); fieldIt != fieldMap.end(); ++fieldIt)
			  if (fieldIt->second) {
				std::ostringstream fieldBfr;
				fieldBfr << *(fieldIt->second);
				apMultiEventModel->addParameter(parameterForeignKeyT(eventID, objectID), fieldIt->first, MultiEventModel::valueT(fieldBfr.str().c_str()) );
			  }
		}
	}

	pTable->setRowCount((int)apMultiEventModel->getEvents()->size()+2);
	pTable->setColumnCount((int)apMultiEventModel->getParameters()->size()+3); //Note. To big, gets resized later when correct number is known.
	pTable->horizontalHeader()->setVisible(false);
	pTable->verticalHeader()->setVisible(false);

	//Fill spreadsheet-model according to the following algorithm:
	//For each object
	// 	find all events connected to/manipulating the object
	//	For each such event
	//		find the parameters the event changes in the object
	//		For each of these parameters
	//			set the corresponding cell in the spreadsheet
	//		End for
	//	End For
	//  set the headers corresponding to the correct Object and parameter names
	//End For
	size_t totParameterOffset = 0; //Objects contains various number of parameters. This variable ensures correct offset for the next objects in the sheet
	for(std::map<size_t,MultiEventModel::objectT*>::iterator objIt = apMultiEventModel->getObjects()->begin(); objIt != apMultiEventModel->getObjects()->end(); ++objIt){
		size_t objIndex = objIt->first;
		std::pair<std::multimap<size_t, size_t>::iterator, std::multimap<size_t, size_t>::iterator> events;
		events = apMultiEventModel->getObjectToEventConnections()->equal_range(objIndex);

		// For all events connected to the current object
		for(std::multimap<size_t, size_t>::iterator eventIt = events.first; eventIt != events.second; ++eventIt){
			size_t eventIndex = eventIt->second;

			// Get all parameters connected to a given object and event pair.
			std::pair<std::multimap<parameterForeignKeyT,MultiEventModel::parameterT*>::iterator, std::multimap<parameterForeignKeyT,MultiEventModel::parameterT*>::iterator> ret;
			ret = apMultiEventModel->getParameters()->equal_range(parameterForeignKeyT(eventIndex, objIndex));

			// For all parameters in the current object and event
			int parameterOffset = 0;
			for(std::multimap<parameterForeignKeyT,MultiEventModel::parameterT*>::iterator retIt = ret.first; retIt != ret.second; ++retIt){
				parameterOffset = objIt->second->getPosOfParameterType(retIt->second->getName());
				// Set the spreadsheet cell corresponding to parameter
				pTable->setItem(apMultiEventModel->getTableIndexOfEvent(eventIndex)+2, parameterOffset + totParameterOffset +3, new QTableWidgetItem(retIt->second->getValue().toString()));
			}
		}

		//Horizontal Headers(Object names)
		if (objIt->second->getUsedParameterNames().size() > 1)
		  pTable->setSpan(0, totParameterOffset+3, 1, objIt->second->getUsedParameterNames().size());

		pTable->setItem(0, totParameterOffset+3, new QTableWidgetItem(QString(objIt->second->getName().c_str())));

		//Horizontal Sub-headers(Parameter names)
		for (size_t i = 0; i < objIt->second->getUsedParameterNames().size(); ++i)
		  pTable->setItem(1, totParameterOffset+i+3, new QTableWidgetItem(QString(objIt->second->getUsedParameterNames().at(i).c_str())));

		totParameterOffset += objIt->second->getUsedParameterNames().size();
	}

	// Set ID-numbers and names for events
	std::map<size_t,MultiEventModel::eventT*>::iterator evtIt = apMultiEventModel->getEvents()->begin();
	for (int count = 2; evtIt != apMultiEventModel->getEvents()->end(); ++evtIt, count++) {
	  pTable->setItem(count, 0, new QTableWidgetItem(QString::number(evtIt->second->getID())));
	  pTable->setItem(count, 1, new QTableWidgetItem(QString(evtIt->second->getName().c_str())));
	  pTable->setItem(count, 2, new QTableWidgetItem(QString::number(evtIt->second->getProbability(),'f',2)));
	}

	//Event header
	pTable->setSpan(0, 0, 1, 3);
	pTable->setItem(0, 0, new QTableWidgetItem("Events"));
	//Sub-header
	pTable->setItem(1, 0, new QTableWidgetItem("ID"));
	pTable->setItem(1, 1, new QTableWidgetItem("Descr."));
	pTable->setItem(1, 2, new QTableWidgetItem("Prob."));

	pTable->setColumnCount(totParameterOffset+3);

	//Delegate for headers. Headers are really just cells, painted by the delegate to look like a header
	HeaderDelegate* pHeaderDelegate = new HeaderDelegate(pTable);
	pTable->setItemDelegateForRow(0, pHeaderDelegate);
	pTable->setItemDelegateForRow(1, pHeaderDelegate);

	pTable->resizeColumnsToContents();
	pTable->setAlternatingRowColors(true);
}


void FuiQtEventDefinition::closeEvent(QCloseEvent* event)
{
  event->accept();
  pTable->clear();
  if (apMultiEventModel) {
    apMultiEventModel->clean();
    delete apMultiEventModel;
  }
}


void FuiQtEventDefinition::help()
{
  // Display the topic in the help file
  Fui::showCHM("dialogbox/event-definition.htm");
}
