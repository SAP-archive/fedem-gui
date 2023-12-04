// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPUAOUTPUTLIST_H
#define FAPUAOUTPUTLIST_H

//include
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUACommandHandler.H"


//define

//Typedefs and fwd declarations
class FuiOutputList;

class FapUAOutputList : public FapUAExistenceHandler, public FapUAFinishHandler,
			public FapUACommandHandler
{     
  Fmd_HEADER_INIT();
public:
  FapUAOutputList(FuiOutputList* ui);
  virtual ~FapUAOutputList();
  
// Operations  
public:

private:
  // from FapUAFinishHandler
  virtual void finishUI(); 

  // from command handler
  virtual FFuaUICommands* createCommandsObject();
  virtual void getCommands(FFuaUICommands* commands);


// Attributes
private:
  FuiOutputList*  ui;

};
////////////////////////////////////////////////////////////////////////
#endif

