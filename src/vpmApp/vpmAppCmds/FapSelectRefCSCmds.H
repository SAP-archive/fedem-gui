// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPSELECTREFCSCMDS_H
#define FAPSELECTREFCSCMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class FuiPositionData;


class FapSelectRefCSCmds: public FapCmdsBase
{
 private:
  static void init();
  

  static void setState(int newState);
 
 public:
  static void selectRefCS(FuiPositionData * ActivePosUI);

  static void enterMode();
  static void cancelMode();
  static void done();
  
private:
   static int myState;
   enum
     { START,                
       REF_SELECTED,         
       REF_ACCEPTED
     };    
   
   static FuiPositionData * ourActiveUI;
   friend class FFaInitialisation<FapSelectRefCSCmds>;
};

static FFaInitialisation<FapSelectRefCSCmds> FapSelectRefCSCmds_Init;

#endif



