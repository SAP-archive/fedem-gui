// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_UA_EXISTENCE_HANDLER_H
#define FFU_UA_EXISTENCE_HANDLER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FapUAExistenceHandler;//just to getUA (a bit ugly)

class FFuUAExistenceHandler
{
public:
  FFuUAExistenceHandler() {}
  virtual ~FFuUAExistenceHandler();

// Operations  
public:
  FapUAExistenceHandler* getUA()
    {FapUAExistenceHandler* ua = 0;
     this->invokeGetUACB(ua);
     return ua;}

  // Callbacks are set by FapUAExistenceHandler
  static void setCreateUACB(FFaDynCB1<FFuUAExistenceHandler*> dynCB)
    {FFuUAExistenceHandler::createUACB = dynCB;}
  void setDestructUACB(FFaDynCB0 dynCB)
    {this->destructUACB = dynCB;}
  void setGetUACB(FFaDynCB1<FapUAExistenceHandler*&> dynCB)
    {this->getUACB = dynCB;}

protected:
  // This CB creates the UI's UA objects. It should be  
  // invoked when the ui is ready for initiation
  static bool invokeCreateUACB(FFuUAExistenceHandler* ui);
  
private:
  // This CB destructs the UI's UA objects. It is invoked
  // from this class' destructor.
  bool invokeDestructUACB();
  void invokeGetUACB(FapUAExistenceHandler*& ua);

// Attributes
private:
  static FFaDynCB1<FFuUAExistenceHandler*> createUACB;
  FFaDynCB0 destructUACB;
  FFaDynCB1<FapUAExistenceHandler*&> getUACB;
};
////////////////////////////////////////////////////////////////////////
#endif
