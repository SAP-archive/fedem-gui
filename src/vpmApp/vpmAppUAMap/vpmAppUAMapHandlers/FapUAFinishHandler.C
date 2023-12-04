// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAFinishHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


FapUAFinishHandler::FapUAFinishHandler(FFuUAFinishHandler* ui)
{
  ui->setFinishedCB(FFaDynCB0M(FapUAFinishHandler,this,finishUI));
}
