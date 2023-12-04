// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiRDBMEFatigue.H"
#include "vpmUI/vpmUIComponents/FuiItemsListViews.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "vpmUI/Fui.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuTable.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuToggleButton.H"

enum {
  DONE = FFuDialogButtons::LEFTBUTTON,
  HELP = FFuDialogButtons::RIGHTBUTTON
};

Fmd_SOURCE_INIT(FcFUIRDBMEFATIGUE, FuiRDBMEFatigue, FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiRDBMEFatigue::FuiRDBMEFatigue()
{
  Fmd_CONSTRUCTOR_INIT(FuiRDBMEFatigue);
  this->dialogButtons = NULL;
}
//----------------------------------------------------------------------------

void FuiRDBMEFatigue::initWidgets()
{
  this->dialogButtons->setButtonClickedCB(FFaDynCB1M(FuiRDBMEFatigue,this,
						     onDialogButtonClicked,int));

  this->useProbToggle->setLabel("Use probability weighted results");
  this->useProbToggle->setValue(true);
  this->startTimeField->setLabel("Start time");
  this->stopTimeField->setLabel("Stop time");
  this->standardField->setLabel("Standard");
  this->snCurveField->setLabel("S-N curve");
  this->copyDataButton->setLabel("Copy data");
  this->startTimeField->setSensitivity(false);
  this->stopTimeField->setSensitivity(false);
  this->standardField->setSensitivity(false);
  this->snCurveField->setSensitivity(false);

  this->copyDataButton->setActivateCB(FFaDynCB0M(FuiRDBMEFatigue,this,onCopyDataClicked));

  this->notesImage->setPixMap(info_xpm);
  this->notesLabel->setLabel("<b>Notes</b>");
  this->notesText->setLabel("This table shows a fatigue summary of all\n"
			    "events and curves. Click to toggle whether\n"
			    "the row is included in the sum.");

  this->dialogButtons->setButtonLabel(DONE,"Close");
  this->dialogButtons->setButtonLabel(HELP,"Help");

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiRDBMEFatigue::placeWidgets(int width,int height)
{
  int border = this->getBorder();
  int dbTop = height - this->dialogButtons->getHeightHint();

  this->tableMain->setEdgeGeometry(border, width-border, border, dbTop-border-165);

  int y = dbTop-border-165+5;
  this->useProbToggle->setEdgeGeometry(border, width-border, y, y+20);
  this->copyDataButton->setEdgeGeometry(width-border-80, width-border, y, y+20);
  y += 22;
  this->startTimeField->setEdgeGeometry(border, border+220, y, y+20);
  this->startTimeField->setLabelWidth(50);
  y += 22;
  this->stopTimeField->setEdgeGeometry(border, border+220, y, y+20);
  this->stopTimeField->setLabelWidth(50);
  y += 22;
  this->standardField->setEdgeGeometry(border, border+220, y, y+20);
  this->standardField->setLabelWidth(50);
  y += 22;
  this->snCurveField->setEdgeGeometry(border, border+220, y, y+20);
  this->snCurveField->setLabelWidth(50);

  int glbl = border;
  this->notesImage->setEdgeGeometry(glbl,    glbl+16,  dbTop-55,    dbTop-55+16);
  this->notesLabel->setEdgeGeometry(glbl+20, glbl+300, dbTop-55,    dbTop-55+16);
  this->notesText->setEdgeGeometry( glbl,    glbl+300, dbTop-55+17, dbTop-55+17+39);

  this->dialogButtons->setEdgeGeometry(0, border+230, dbTop, height);
}
//----------------------------------------------------------------------------

void FuiRDBMEFatigue::onDialogButtonClicked(int button)
{
  switch (button) {
  case DONE:
    this->invokeFinishedCB();
    break;
  case HELP:
    // Display the topic in the help file
    Fui::showCHM("dialogbox/fatigue-summary.htm");
    break;
  }
}
//----------------------------------------------------------------------------

bool FuiRDBMEFatigue::onClose()
{
  this->onDialogButtonClicked(DONE);
  return false;
}
