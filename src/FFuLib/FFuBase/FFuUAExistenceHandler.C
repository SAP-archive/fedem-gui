// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"


FFaDynCB1<FFuUAExistenceHandler*> FFuUAExistenceHandler::createUACB;

//----------------------------------------------------------------------------

FFuUAExistenceHandler::~FFuUAExistenceHandler()
{
  this->invokeDestructUACB();
}
//----------------------------------------------------------------------------

bool FFuUAExistenceHandler::invokeCreateUACB(FFuUAExistenceHandler* ui)
{
  if (FFuUAExistenceHandler::createUACB.empty()) return false; 
  FFuUAExistenceHandler::createUACB.invoke(ui);
  return true;
}
//----------------------------------------------------------------------------

bool FFuUAExistenceHandler::invokeDestructUACB()
{
  if (this->destructUACB.empty()) return false; 
  this->destructUACB.invoke();
  return true;
}
//----------------------------------------------------------------------------

void FFuUAExistenceHandler::invokeGetUACB(FapUAExistenceHandler*& ua)
{
  this->getUACB.invoke(ua);
}
//----------------------------------------------------------------------------
