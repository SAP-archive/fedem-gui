// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPALLIGNCSCMDS_H
#define FAPALLIGNCSCMDS_H
#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"

class SoEventCallback;
class FaMat34;

class FapAllignCSCmds: public FapCmdsBase
{
 private:
  static void init();
  
  static void getSensitivity(bool & isSensitive);
  
  static void allignCS();
 public:
  static void allignCS( const FaMat34 & mx);
 private:
  static void allignRotations();
  static void allignRotations( const FaMat34 & mx);

  static void setState(int newState);
  static void eventCB(void *,SoEventCallback *eventCallbackNode);
 
 public:
  static void enterMode();
  static void cancelMode();
  static void allignCSDone();
 
// Attributes
private:
   static FaMat34 ourAllignCS;  
   static int myState;

   friend class FFaInitialisation<FapAllignCSCmds>;
};

static FFaInitialisation<FapAllignCSCmds> FapAllignCSCmds_Init;

#endif




