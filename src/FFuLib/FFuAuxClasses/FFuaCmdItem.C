// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"

#include <iostream>
#include <fstream>


FFuaCmdItem::CommandMap* FFuaCmdItem::cmdItemMap = 0;
bool FFuaCmdItem::weAreLoggingCmds = false;

//--------------------------------------------------------------------

void FFuaCmdItem::printCmdListToFile()
{
  if (!cmdItemMap) return;

  std::ofstream liste("FedemCmdList.txt");
  CommandMap::const_iterator it;
  for (it = cmdItemMap->begin(); it != cmdItemMap->end(); it++)
    liste << "@" << it->first
	  << "$" << it->second->getText()
	  << "$" << it->second->getToolTip() << std::endl;
}
//--------------------------------------------------------------------

void FFuaCmdItem::invokeActivatedCB()
{
  if (weAreLoggingCmds)
    std::cout << this->getCmdItemId() << std::endl;

  this->activatedCB.invoke();
}
//--------------------------------------------------------------------

void FFuaCmdItem::invokeToggledCB(bool toggle)
{
  if (weAreLoggingCmds)
    std::cout << this->getCmdItemId() << std::endl;

  this->toggledCB.invoke(toggle);
}
//--------------------------------------------------------------------

void FFuaCmdItem::init()
{
  if (!cmdItemMap)
    cmdItemMap = new CommandMap();
}
//----------------------------------------------------------------------------

FFuaCmdItem* FFuaCmdItem::getCmdItem(const std::string& itemId)
{
  if (itemId.empty() || !cmdItemMap) return 0;

  CommandMap::iterator it = cmdItemMap->find(itemId);
  if (it != FFuaCmdItem::cmdItemMap->end())
    return it->second;

  std::cerr <<"ERROR FFuaCmdItem: \""<< itemId <<"\" does not exist"
	    << std::endl;
  return 0;
}
//----------------------------------------------------------------------------

FFuaCmdItem::FFuaCmdItem(const std::string& itemId)
{
  this->initVars();
  this->cmdItemId = itemId;
  if (itemId.empty() || !cmdItemMap) return;

  CommandMap::iterator it = FFuaCmdItem::cmdItemMap->find(itemId);
  if (it != FFuaCmdItem::cmdItemMap->end()) {
    std::cerr <<"ERROR FFuaCmdItem: \""<< itemId <<"\" already exists"
	      << std::endl;
    *(char*)0 = 'd'; // To make core
  }
  else // unique id
    (*cmdItemMap)[itemId] = this;
}
//----------------------------------------------------------------------------

FFuaCmdItem::~FFuaCmdItem()
{
  if (!this->cmdItemId.empty() && cmdItemMap) // subject to static management
    cmdItemMap->erase(this->cmdItemId);
}
//----------------------------------------------------------------------------

void FFuaCmdItem::initVars()
{
  this->bigIcon = 0;
  this->smallIcon = 0;
  this->pixmap = 0;
  this->accelKey = 0;
  this->toggleAble = false;
  this->behaveAsRadio = false;
  this->toggled = false;
  this->menuButtonPopupMode = false;
}
//----------------------------------------------------------------------------

bool FFuaCmdItem::getSensitivity()
{
  bool sensitivity = true;
  this->invokeGetSensitivityCB(sensitivity);
  return sensitivity;
}
//----------------------------------------------------------------------------

bool FFuaCmdItem::getToggled()
{
  if (this->getToggledCB.empty())
    return this->toggled;

  bool toggle;
  this->invokeGetToggledCB(toggle);
  return toggle;
}
//----------------------------------------------------------------------------

FFuaCmdHeaderItem::FFuaCmdHeaderItem(const std::string& txt) : FFuaCmdItem()
{
  this->setText(txt);
}
//----------------------------------------------------------------------------
