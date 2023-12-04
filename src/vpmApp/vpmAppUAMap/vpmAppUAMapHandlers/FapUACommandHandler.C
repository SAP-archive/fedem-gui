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

void FapUACommandHandler::updateUICommands()
{ 
  FFuaUICommands* commands = this->createCommandsObject();
  if (commands) {
    this->getCommands(commands);
    this->ui->setUICommands(commands);
    delete commands;
  }
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateUICommandsSensitivity()
{ 
  FFuaUICommands* commands = this->createCommandsObject();
  if (commands) {
    this->getCommands(commands);
    this->ui->updateUICommandsSensitivity(commands);
    delete commands;
  }
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateUICommandsToggle()
{ 
  FFuaUICommands* commands = this->createCommandsObject();
  if (commands) {
    this->getCommands(commands);
    this->ui->updateUICommandsToggle(commands);
    delete commands;
  }
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateAllUICommands()
{
  std::vector<FapUAExistenceHandler*> all;
  FapUACommandHandler* tmp;
  
  FapUAExistenceHandler::getAllOfType(FapUAExistenceHandler::getClassTypeID(),all);
  
  for (unsigned int i = 0; i < all.size(); i++) 
    if ((tmp = dynamic_cast<FapUACommandHandler*>(all[i])))
      tmp->updateUICommands();
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateAllUICommandsSensitivity()
{ 
  std::vector<FapUAExistenceHandler*> all;
  FapUACommandHandler* tmp;
  
  FapUAExistenceHandler::getAllOfType(FapUAExistenceHandler::getClassTypeID(),all);
  
  for (unsigned int i = 0; i < all.size(); i++) 
    if ((tmp = dynamic_cast<FapUACommandHandler*>(all[i])))
      tmp->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------

void FapUACommandHandler::updateAllUICommandsToggle()
{
  std::vector<FapUAExistenceHandler*> all;
  FapUACommandHandler* tmp;
  
  FapUAExistenceHandler::getAllOfType(FapUAExistenceHandler::getClassTypeID(),all);
  
  for (unsigned int i = 0; i < all.size(); i++) 
    if ((tmp = dynamic_cast<FapUACommandHandler*>(all[i])))
      tmp->updateUICommandsToggle();  
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onPermSelectionChanged(const std::vector<FFaViewItem*>&,
						 const std::vector<FFaViewItem*>&,
						 const std::vector<FFaViewItem*>&)
{
  //  cout<<"\\\\\\\\\\\\\\\\FapUACommandHandler::onSelectionChanged"<<endl;
  //this->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onActiveWindowChanged(FFuMDIWindow*, FFuMDIWindow*)
{
  //  cout<<"\\\\\\\\\\\\\\\\FapUACommandHandler::onActiveWindowChanged"<<endl;
  this->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------
void FapUACommandHandler::onActiveAnimationChanged(FmAnimation*, FmAnimation*)
{
  this->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onRDBHeaderChanged(FFrExtractor*)
{
  this->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------

void FapUACommandHandler::onProcessGroupChanged(int)
{
  this->updateUICommandsSensitivity();
}
//----------------------------------------------------------------------------
