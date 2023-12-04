// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

#include <cassert>

//----------------------------------------------------------------------------

/*!
  The constructor sets up the FFuUADataHandler callbacks.
  \param ui the UI side data handler
*/
FapUADataHandler::FapUADataHandler(FFuUADataHandler* uic)
{
  this->ui = uic;
  if (!uic) return;

  this->ui->setSetAndGetDBValuesCB(FFaDynCB1M(FapUADataHandler,this,
					      setAndGetDBValues,FFuaUIValues*));
  this->ui->setUpdateUIValuesCB(FFaDynCB0M(FapUADataHandler,this,
					   updateUIValues));
}
//----------------------------------------------------------------------------

/*!
  Updates DB and fills the FFuaUIValues object.
  \param values The value FFuaUIValues to be updated
*/
void FapUADataHandler::setAndGetDBValues(FFuaUIValues* values)
{
  this->setDBValues(values);
  this->getDBValues(values);
}
//----------------------------------------------------------------------------

/*!
  Does a complete update of the user interface with data it gets from the DB.
  It does update the dynamic widgets in the UI.
  \sa getDBValues
  \sa setUIValues
  \sa buildDynamicWidgets
*/
void FapUADataHandler::updateUI()
{
  assert(this->ui);
  FFuaUIValues* values = this->createValuesObject();
  if (values) {
    this->getDBValues(values);
    this->ui->buildDynamicWidgets(values);
    this->ui->setUIValues(values);
    delete values;
  }
}

//----------------------------------------------------------------------------

/*!
  Updates the user interface with data it gets from the DB.
  It does not update the dynamic widgets in the UI.
  \sa getDBValues
  \sa setUIValues
*/
void FapUADataHandler::updateUIValues()
{
  assert(this->ui);
  FFuaUIValues* values = this->createValuesObject();
  if (values) {
    this->getDBValues(values);
    this->ui->setUIValues(values);
    delete values;
  }
}
//----------------------------------------------------------------------------

void FapUADataHandler::setUIValues(const FFuaUIValues* values)
{
  assert(this->ui);
  this->ui->setUIValues(values);
}
//----------------------------------------------------------------------------

void FapUADataHandler::getUIValues(FFuaUIValues* values)
{
  assert(this->ui);
  this->ui->getUIValues(values);
}
//----------------------------------------------------------------------------

void FapUADataHandler::updateDBValues()
{
  assert(this->ui);
  FFuaUIValues* values = this->createValuesObject();
  if (values) {
    this->ui->getUIValues(values);
    this->setDBValues(values);
    delete values;
  }
}
//----------------------------------------------------------------------------

void FapUADataHandler::clearUIValues()
{
  assert(this->ui);
  this->ui->clearUIValues();
}
