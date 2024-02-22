// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUACommandHandler.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUACommandHandler.H"


//----------------------------------------------------------------------------

FapUACommandHandler::FapUACommandHandler(FFuUACommandHandler* uic) : 
  permSelReceiver(this), activeWinReceiver(this), activeAnimReceiver(this),
  headerChangedReciever(this), processChanged(this)
{
  this->ui = uic;

  //cb's from ui
  this->ui->setUpdateUICommandsCB(FFaDynCB0M(FapUACommandHandler,this,
					     updateUICommands));
  this->ui->setExecuteCommandCB(FFaDynCB1M(FapUACommandHandler,this,
					   executeCommand,FFuaCmdItem*));
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateUICommands(bool setNew, bool sens, bool toggle)
{ 
  FFuaUICommands* commands = this->getCommands();
  if (!commands) return;

  if (setNew) this->ui->setUICommands(commands);
  if (sens)   this->ui->updateUICommandsSensitivity(commands);
  if (toggle) this->ui->updateUICommandsToggle(commands);
  delete commands;
}

//----------------------------------------------------------------------------

void FapUACommandHandler::updateAllUICommands(bool sens, bool toggle)
{ 
  std::vector<FapUAExistenceHandler*> all;
  FapUAExistenceHandler::getAllOfType(FapUAExistenceHandler::getClassTypeID(),all);

  FapUACommandHandler* tmp;
  for (FapUAExistenceHandler* ua : all)
    if ((tmp = dynamic_cast<FapUACommandHandler*>(ua)))
      tmp->updateUICommands(false,sens,toggle);
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onPermSelectionChanged(const std::vector<FFaViewItem*>&,
						 const std::vector<FFaViewItem*>&,
						 const std::vector<FFaViewItem*>&)
{
  //this->updateUICommands(false,true);
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onActiveWindowChanged(FFuMDIWindow*, FFuMDIWindow*)
{
  this->updateUICommands(false,true);
}
//----------------------------------------------------------------------------
void FapUACommandHandler::onActiveAnimationChanged(FmAnimation*, FmAnimation*)
{
  this->updateUICommands(false,true);
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onRDBHeaderChanged(FFrExtractor*)
{
  this->updateUICommands(false,true);
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onProcessGroupChanged(int)
{
  this->updateUICommands(false,true);
}
//----------------------------------------------------------------------------
