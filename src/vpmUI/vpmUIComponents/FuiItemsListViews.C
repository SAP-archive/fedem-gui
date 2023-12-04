// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiItemsListViews.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdPickedPoints.H"
#endif


static void onLMBPressed(FFuListViewItem*)
{
#ifdef USE_INVENTOR
  FdPickedPoints::deselectNode(); // In case previous selection was in modeller
#endif
  FuiItemsListView::mouseSelected = true; // As opposed to using the arrow keys
}

static void onLMBRelease()
{
  FuiItemsListView::mouseSelected = false;
}

//----------------------------------------------------------------------------

void FuiSimModelListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->setLeftMouseBPressedCB(FFaDynCB1S(onLMBPressed,FFuListViewItem*));
  this->setLeftMouseBReleaseCB(FFaDynCB0S(onLMBRelease));
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------

void FuiResultListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->setLeftMouseBPressedCB(FFaDynCB1S(onLMBPressed,FFuListViewItem*));
  this->setLeftMouseBReleaseCB(FFaDynCB0S(onLMBRelease));
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------

void FuiRDBListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------

void FuiSimModelRDBListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->setLeftMouseBPressedCB(FFaDynCB1S(onLMBPressed,FFuListViewItem*));
  this->setLeftMouseBReleaseCB(FFaDynCB0S(onLMBRelease));
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------

void FuiCrossSectionListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------

void FuiMaterialListView::initWidgets()
{
  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);

  // viewSession init
  this->setUpdateOnChangesWhenInMem(true);
  this->updateSession();

  // initial command update
  this->updateUICommands();
}
//----------------------------------------------------------------------------
