// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtTabbedWidgetStack.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtAnimationDefine.H"

//----------------------------------------------------------------------------

FuiQtAnimationDefine::FuiQtAnimationDefine(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->typeFrame = new FFuQtLabelFrame(this);
  this->timeRadio = new FFuQtRadioButton(this);
  this->eigenRadio = new FFuQtRadioButton(this);
  this->summaryRadio = new FFuQtRadioButton(this);

  this->loadFringeToggle = new FFuQtToggleButton(this);
  this->loadLineFringeToggle = new FFuQtToggleButton(this);
  this->loadDefToggle = new FFuQtToggleButton(this);
  this->loadAnimButton = new FFuQtPushButton(this);

  this->tabStack = new FFuQtTabbedWidgetStack(this);
  this->fringeSheet = new FuiQtFringeSheet(this);
  this->timeSheet = new FuiQtTimeSheet(this);
  this->modesSheet = new FuiQtModesSheet(this);

  this->initWidgets();
}

/////////////////////////////////////////////////////////////////////////////

FuiQtFringeSheet::FuiQtFringeSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->fringeFrame = new FFuQtLabelFrame(this);
  this->resultClassLabel = new FFuQtLabel(this);
  this->resultClassMenu = new FFuQtOptionMenu(this);
  this->resultLabel = new FFuQtLabel(this);
  this->resultMenu = new FFuQtOptionMenu(this);
  this->resultOperLabel = new FFuQtLabel(this);
  this->resultOperMenu = new FFuQtOptionMenu(this);

  this->resultSetFrame = new FFuQtLabelFrame(this);
  this->setByOperRadio = new FFuQtRadioButton(this);
  this->setOperMenu = new FFuQtOptionMenu(this);
  this->setByNameRadio = new FFuQtRadioButton(this);
  this->setNameMenu = new FFuQtOptionMenu(this);

  this->averageFrame = new FFuQtLabelFrame(this);
  this->averageOperLabel = new FFuQtLabel(this);
  this->averageOperMenu = new FFuQtOptionMenu(this);
  this->averageOnLabel = new FFuQtLabel(this);
  this->averageOnMenu = new FFuQtOptionMenu(this);
  this->shellAngleLabel = new FFuQtLabel(this);
  this->shellAngleField = new FFuQtIOField(this);
  this->elementToggle = new FFuQtToggleButton(this);

  this->multiFaceFrame = new FFuQtLabelFrame(this);
  this->elemGrpOperLabel = new FFuQtLabel(this);
  this->elemGrpOperMenu = new FFuQtOptionMenu(this);

  this->autoExportToggle = new FFuQtToggleButton(this);

  this->initWidgets();
}

/////////////////////////////////////////////////////////////////////////////

FuiQtTimeSheet::FuiQtTimeSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->timeFrame = new FFuQtLabelFrame(this);
  this->completeSimRadio = new FFuQtRadioButton(this);
  this->timeIntRadio = new FFuQtRadioButton(this);
  this->startField = new FFuQtIOField(this);
  this->stopField = new FFuQtIOField(this);
  this->startLabel = new FFuQtLabel(this);
  this->stopLabel = new FFuQtLabel(this);

  this->framesFrame = new FFuQtLabelFrame(this);
  this->mostFramesRadio = new FFuQtRadioButton(this);
  this->leastFramesRadio = new FFuQtRadioButton(this);

  this->initWidgets();
}

/////////////////////////////////////////////////////////////////////////////

FuiQtModesSheet::FuiQtModesSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  this->eigenFrame = new FFuQtLabelFrame(this);
  this->typeMenu = new FFuQtOptionMenu(this);
  this->linkLabel = new FFuQtLabel(this);
  this->linkMenu = new FuiQtQueryInputField(this);
  this->timeLabel = new FFuQtLabel(this);
  this->timeMenu = new FFuQtOptionMenu(this);
  this->modeLabel = new FFuQtLabel(this);
  this->modeMenu = new FFuQtOptionMenu(this);
  this->scaleLabel = new FFuQtLabel(this);
  this->scaleField = new FFuQtIOField(this);

  this->animFrame = new FFuQtLabelFrame(this);
  this->framesPrLabel = new FFuQtLabel(this);
  this->framesPrField = new FFuQtIOField(this);

  this->lengthFrame = new FFuQtLabelFrame(this);
  this->timeLengthRadio = new FFuQtRadioButton(this);
  this->timeLengthField = new FFuQtIOField(this);
  this->nCyclRadio = new FFuQtRadioButton(this);
  this->nCyclField = new FFuQtIOField(this);
  this->dampedRadio = new FFuQtRadioButton(this);
  this->dampedField = new FFuQtIOField(this);

  this->initWidgets();
}
