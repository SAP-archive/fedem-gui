// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAWorkSpace.H"
#include "vpmApp/FapEventManager.H"
#include "vpmUI/vpmUIComponents/FuiWorkSpace.H"
#include "FFuLib/FFuBase/FFuMDIWindow.H"


Fmd_SOURCE_INIT(FAPUAWORKSPACE, FapUAWorkSpace, FapUAExistenceHandler);

//----------------------------------------------------------------------------

FapUAWorkSpace::FapUAWorkSpace(FuiWorkSpace* uic) : FapUAExistenceHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUAWorkSpace);

  this->ui = uic;
  this->ui->setWindowActivatedCB(FFaDynCB1M(FapUAWorkSpace,this,
					    setActiveWindow,FFuMDIWindow*));
}
//----------------------------------------------------------------------------

void FapUAWorkSpace::setActiveWindow(FFuMDIWindow* win)
{
  if (win) win->onWindowActivated();

  FapEventManager::setActiveWindow(win);
}
//----------------------------------------------------------------------------
