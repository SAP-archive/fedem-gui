// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPUASTRESSOPTIONS_H
#define FAPUASTRESSOPTIONS_H

//include
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "vpmUI/vpmUITopLevels/FuiStressOptions.H"

//define

//Typedefs and fwd declarations

class FapUAStressOptions : public FapUAExistenceHandler, public FapUADataHandler, public FapUAFinishHandler
{     
  Fmd_HEADER_INIT();
public:
  FapUAStressOptions(FuiStressOptions* ui);
  virtual ~FapUAStressOptions();
  
// Operations  
public:

  
private:
  // from datahandler
  virtual FFuaUIValues* createValuesObject(); 
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  //from finishhandler
  virtual void finishUI(); 
  
  //cbs
  void resetTime();
  // Attributes
private:
  FuiStressOptions* ui;
 
};
/////////////////////////////////////////////////////////////////////////////
#endif
