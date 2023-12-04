// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuUADataHandler.H"


/*!
  \class FFuUADataHandler FFuUADataHandler.H
  \brief Plug-in interface to handle data transfer between UI and UA.

  UADataHandler's task is to handle the datatransfer between UI and UA.
  It interacts with FapUADataHandler. Plugin whenever needed that fuctionallity.

  \author  Dag R. Christensen
*/

//----------------------------------------------------------------------------

bool FFuUADataHandler::updateDBValues(bool updateui)
{
  FFuaUIValues* values = this->createValuesObject();
  if (values) {
    this->getUIValues(values);
    this->invokeSetAndGetDBValuesCB(values);
    if (updateui)
      this->setUIValues(values);

    delete values;
    return true;
  }
  return false;
}  
//----------------------------------------------------------------------------

/*!
  \fn  virtual void FFuUADataHandler::setUIValues(const FFuaUIValues* values)
   Method to set values in ui, which is expected to be re-impl for the ui's 
*/


/*!
  \class FFuaUIValues FFuUADataHandler.H
  \brief Base class for value storage.
  FFuaUIValues is used together with FFuUADataHandler to transfer values
  between UI and DB.

  \author Dag R. Christensen
*/
