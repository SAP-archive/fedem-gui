// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_UA_COMMAND_HANDLER_H
#define FFU_UA_COMMAND_HANDLER_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuaCmdItem;
class FFuaUICommands;


class FFuUACommandHandler
{
public:
  FFuUACommandHandler() {}
  virtual ~FFuUACommandHandler() {}

public:
  // These callbacks are set by FapUACommandHandler
  void setUpdateUICommandsCB(const FFaDynCB0& dynCB)
    {this->updateUICommandsCB = dynCB;}
  void setExecuteCommandCB(const FFaDynCB1<FFuaCmdItem*>& dynCB)
    {this->executeCommandCB = dynCB;}

  // These methods should be reimplemented if you want the class to work as expected
  virtual void setUICommands(const FFuaUICommands*) {}
  virtual void updateUICommandsSensitivity(const FFuaUICommands*) {}
  virtual void updateUICommandsToggle(const FFuaUICommands*) {}

  void updateUICommands() { this->invokeUpdateUICommandsCB(); }

protected:
  void invokeUpdateUICommandsCB()
    {this->updateUICommandsCB.invoke();}
  void invokeExecuteCommandCB(FFuaCmdItem* command)
    {this->executeCommandCB.invoke(command);}

private:
  FFaDynCB0 updateUICommandsCB;
  FFaDynCB1<FFuaCmdItem*> executeCommandCB;
};
////////////////////////////////////////////////////////////////////////

class FFuaUICommands
{
public:
  FFuaUICommands(){}
  virtual ~FFuaUICommands(){}
};
////////////////////////////////////////////////////////////////////////

#endif
