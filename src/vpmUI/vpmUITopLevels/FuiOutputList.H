// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIOUTPUTLIST_H
#define FUIOUTPUTLIST_H

#include <vector>

#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFuLib/FFuBase/FFuUACommandHandler.H"
#include "FFuLib/FFuBase/FFuTopLevelShell.H"


class FFuMemo;
class FFuPushButton;

class FuiOutputList : public virtual FFuTopLevelShell, 
                      public FFuUAExistenceHandler, public FFuUAFinishHandler, public FFuUACommandHandler
{
  Fmd_HEADER_INIT();
public:
  FuiOutputList();
  virtual ~FuiOutputList();

  // Static create method to use instead of constructor :
  // Implementation in GUILib Dependenet implementation file 
  static FuiOutputList* create(FFuComponentBase* parent =0,
			       int xpos = 100, int ypos  = 100,
			       int width= 500, int height= 100,
			       const char* title= "Output List",
			       const char* name = "FuiOutputList");

  void addText(const char * text);

  // Slots from commands
  void clearList();
  void selectAll();
  void copySelected();
  
  bool hasText();
  bool hasSelectedText();


  // From command handler
  virtual void setUICommands(const FFuaUICommands* cmds);
  virtual void updateUICommandsSensitivity(const FFuaUICommands* cmds);
  


protected:
  void initWidgets();

  virtual void placeWidgets(int width,int height);

  virtual bool onClose();
 
  FFuMemo * myMemo;

};

/////////////////////////////////////////////////////////////////////////////

class FuaOutputListCommands : public FFuaUICommands
{
public:
  FuaOutputListCommands() {}
  virtual ~FuaOutputListCommands() {}

  std::vector<FFuaCmdItem*> popUpMenu;
};

#endif
