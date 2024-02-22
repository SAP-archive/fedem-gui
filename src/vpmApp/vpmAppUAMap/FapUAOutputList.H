// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_OUTPUT_LIST_H
#define FAP_UA_OUTPUT_LIST_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUACommandHandler.H"

class FuiOutputList;


class FapUAOutputList : public FapUAExistenceHandler, public FapUAFinishHandler,
			public FapUACommandHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAOutputList(FuiOutputList* ui);
  virtual ~FapUAOutputList() {}

private:
  virtual void finishUI(); 
  virtual FFuaUICommands* getCommands();

private:
  FuiOutputList* ui;
};

#endif

