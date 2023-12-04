// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuUAItemsViewHandler.H"


//----------------------------------------------------------------------------

void FFuUAItemsViewHandler::setUpdateOnChangesWhenInMem(bool update)
{
  this->invokeSetUpdateOnChangesWhenInMemCB(update);
}
//----------------------------------------------------------------------------

bool FFuUAItemsViewHandler::getUpdateOnChangesWhenInMem()
{
  bool update = false;
  this->invokeGetUpdateOnChangesWhenInMemCB(update);
  return update;
}
//----------------------------------------------------------------------------

void FFuUAItemsViewHandler::updateSession()
{
  this->invokeUpdateSessionCB();
}
//----------------------------------------------------------------------------

void FFuUAItemsViewHandler::clearSession()
{
  this->invokeClearSessionCB();
}
//----------------------------------------------------------------------------

void FFuUAItemsViewHandler::onPoppedUpFromMemory()
{
  if (!this->getUpdateOnChangesWhenInMem()) 
    this->updateSession();
}
//----------------------------------------------------------------------------

void FFuUAItemsViewHandler::onPoppedDownToMemory()
{ 
  if (!this->getUpdateOnChangesWhenInMem())
    this->clearSession();
}
//----------------------------------------------------------------------------
