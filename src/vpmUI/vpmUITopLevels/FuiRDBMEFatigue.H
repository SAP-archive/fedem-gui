// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_RDB_ME_FATIGUE_H
#define FUI_RDB_ME_FATIGUE_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"

class FFuDialogButtons;
class FFuLabel;
class FFuTable;
class FFuToggleButton;
class FFuLabelField;
class FFuPushButton;


class FuiRDBMEFatigue : virtual public FFuTopLevelShell,
                        public FFuUAExistenceHandler, public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiRDBMEFatigue();
  virtual ~FuiRDBMEFatigue() {}

  static FuiRDBMEFatigue* create(int xpos = 100, int ypos  = 100,
				 int width= 100, int height= 100,
				 const char* title= "Fatigue summary",
				 const char* name = "FuiRDBMEFatigue");

protected:
  void initWidgets();
  virtual void placeWidgets(int width,int height);
  virtual bool onClose();

private:
  virtual void onCopyDataClicked() = 0;
  void onDialogButtonClicked(int button);

public:
  FFuTable* tableMain;
  FFuToggleButton* useProbToggle;
  FFuLabelField* startTimeField;
  FFuLabelField* stopTimeField;
  FFuLabelField* standardField;
  FFuLabelField* snCurveField;
  FFuPushButton* copyDataButton;
  FFuLabel* notesImage;
  FFuLabel* notesLabel;
  FFuLabel* notesText;
  FFuDialogButtons* dialogButtons;
};

#endif
