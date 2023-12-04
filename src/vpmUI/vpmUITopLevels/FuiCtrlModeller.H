// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUICTRLMODELLER_H
#define FUICTRLMODELLER_H


#include "FFuLib/FFuBase/FFuMDIWindow.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FuiCtrlGridAttributes;

class FuiCtrlModeller : public virtual FFuMDIWindow,
                        public FFuUAExistenceHandler,public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();
public:

  FuiCtrlModeller();
  virtual ~FuiCtrlModeller();

  // Static create method to use instead of constructor :
  // Implementation in GUILib Dependenet implementation file 
  
  static FuiCtrlModeller * create (FFuComponentBase* parent=0,
				   int xpos  = 100, int ypos   = 100,
				   int width = 100, int height = 100,
				   const char *title="Control Editor",
				   const char* name="FuiCtrlModeller");

  // Member UI Interface :
  
  FFuComponentBase * activeViewer()       { return myQtViewer; }
  FuiCtrlGridAttributes * getGridAttributesUI(){ return myCtrlGridAttributes; }

  void showGridUI(bool yes);
 
  virtual void onPoppedUp();
  
protected:

  // Init method to be called by constructor of 
  // UILib dependent Subclass :

  void initWidgets();

  // Reimpelmented methods :
  virtual bool onClose();
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedDownToMem();
  

  // Widgets :
  FuiCtrlGridAttributes* myCtrlGridAttributes;
  FFuComponentBase *myQtViewer;

private :
};

#endif
