// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_CREATE_BEAMSTRING_PAIR_H
#define FAP_UA_CREATE_BEAMSTRING_PAIR_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUADataHandler.H"

class FuiCreateBeamstringPair;
class FmModelMemberBase;


class FapUACreateBeamstringPair : public FapUAExistenceHandler,
                                  public FapUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FapUACreateBeamstringPair(FuiCreateBeamstringPair* ui);
  virtual ~FapUACreateBeamstringPair() {}

private:
  // from datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setDBValues(FFuaUIValues* values);
  virtual void getDBValues(FFuaUIValues* values);

  void createCB(FmModelMemberBase* beam1,
                FmModelMemberBase* beam2,
                FmModelMemberBase* spr, bool radial);
  void deleteCB(FmModelMemberBase* beam1,
                FmModelMemberBase* beam2);

  FuiCreateBeamstringPair* ui;
};

#endif
