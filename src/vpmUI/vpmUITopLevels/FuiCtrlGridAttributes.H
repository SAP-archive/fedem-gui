// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_CTRL_GRID_ATTRIBUTES_H
#define FUI_CTRL_GRID_ATTRIBUTES_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"

class FFuPushButton;
class FFuLabel;
class FFuIOField;
class FFuToggleButton;
class FFuFrame;


class FuiCtrlGridAttributes : virtual public FFuTopLevelShell,
			      public FFuUAExistenceHandler,
			      public FFuUADataHandler
{
public:
  FuiCtrlGridAttributes() {}
  virtual ~FuiCtrlGridAttributes() {}

  // Method to set the values provided into the ui:

  virtual void setUIValues(const FFuaUIValues* values);

protected:

  // Standard init method to be called from subclass constructor :

  void initWidgets();

  // Geometry management from MultUIComponent :

  virtual void placeWidgets(int width, int height);

  virtual void onPoppedUp() { this->updateUIValues(); }

private:

  // This pulls out the data from the fields, etc.
  // and calls setAndGetDBValuesCB on FFuUADataHandler:

  void onValuesChanged();

  // CB's to forward changes to "onValuesChanged" :

  void onToggeled(bool) { this->onValuesChanged(); }
  void onDoubleChanged(double) { this->onValuesChanged(); }

protected:
  FFuLabel*        myGridSizeLabel;
  FFuToggleButton* myGridToggleButton;
  FFuLabel*        myGXLabel;
  FFuLabel*        myGYLabel;
  FFuIOField*      myGXField;
  FFuIOField*      myGYField;

  FFuFrame* myGridSnapSeparator;

  FFuLabel*        mySnapDistLabel;
  FFuToggleButton* mySnapToggleButton;
  FFuLabel*        mySXLabel;
  FFuLabel*        mySYLabel;
  FFuIOField*      mySXField;
  FFuIOField*      mySYField;

  FFuFrame* myCloseSeparator;

  FFuPushButton* myCloseButton;
};


class FuaCtrlGridValues : public FFuaUIValues
{
public:
  bool   gridOn;
  double gridXSpacing;
  double gridYSpacing;
  bool   snapOn;
  double snapXSpacing;
  double snapYSpacing;
};

#endif
