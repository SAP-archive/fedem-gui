// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_WORK_SPACE_H
#define FUI_WORK_SPACE_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuMDIWindow;


class FuiWorkSpace : virtual public FFuComponentBase, public FFuUAExistenceHandler
{
public:
  FuiWorkSpace() {}
  virtual ~FuiWorkSpace() {}

// Operations  
public:  
  void setWindowActivatedCB(const FFaDynCB1<FFuMDIWindow*>& aDynCB)
    {this->windowActivatedCB = aDynCB;} 

  // Functionallity
  virtual void cascadeWins() {}
  virtual void tileWins() {}
  virtual void tabWins() {}
  virtual void subWins() {}
 
  virtual FFuMDIWindow* getActiveWindow() {return 0;}
  virtual void sendWindowActivated() {}

protected:
  void initWidgets() { FFuUAExistenceHandler::invokeCreateUACB(this); }
  void invokeWindowActivatedCB(FFuMDIWindow* win)
    {this->windowActivatedCB.invoke(win);}
  
private:
  FFaDynCB1<FFuMDIWindow*> windowActivatedCB;
};

#endif
