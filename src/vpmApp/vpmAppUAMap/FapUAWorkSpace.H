// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAPUAWORKSPACE_H
#define FAPUAWORKSPACE_H

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"

class FuiWorkSpace;
class FFuMDIWindow;


class FapUAWorkSpace : public FapUAExistenceHandler
{
  Fmd_HEADER_INIT();

public:
  FapUAWorkSpace(FuiWorkSpace* ui);
  virtual ~FapUAWorkSpace() {}

private:
  void setActiveWindow(FFuMDIWindow* win);

  FuiWorkSpace* ui;
};

#endif
