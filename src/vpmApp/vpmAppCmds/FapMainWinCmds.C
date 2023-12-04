// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppCmds/FapMainWinCmds.H"
#include "vpmApp/vpmAppUAMap/vpmAppUAMapHandlers/FapUACommandHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "vpmUI/vpmUITopLevels/FuiMainWindow.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "vpmUI/Fui.H"

//----------------------------------------------------------------------------

void FapMainWinCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showModelManager");
  cmdItem->setSmallIcon(modelManager_xpm);
  cmdItem->setText("Model Manager");
  cmdItem->setToolTip("Model Manager");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showModelManager,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getModelManagerToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showProperties");
  cmdItem->setSmallIcon(propertyEditor_xpm);
  cmdItem->setText("Property Editor");
  cmdItem->setToolTip("Property Editor");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showProperties,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getPropertiesToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showStdToolBar");
  cmdItem->setText("Standard");
  cmdItem->setToolTip("Standard");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showStdToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getStdToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showWindowsToolBar");
  cmdItem->setText("Windows");
  cmdItem->setToolTip("Windows");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showWindowsToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getWindowsToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showSolveToolBar");
  cmdItem->setText("Solve");
  cmdItem->setToolTip("Solve");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showSolveToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getSolveToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showViewCtrlToolBar");
  cmdItem->setText("View Control");
  cmdItem->setToolTip("View Control");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showViewCtrlToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getViewCtrlToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showThreeDViewsToolBar");
  cmdItem->setText("3D Views");
  cmdItem->setToolTip("3D Views");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showThreeDViewsToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getThreeDViewsToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showMechWindToolBar");
  cmdItem->setText("Windpower Creation");
  cmdItem->setToolTip("Windpower Creation");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showMechWindToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getMechWindToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showMechCreateToolBar");
  cmdItem->setText("Mechanism Creation");
  cmdItem->setToolTip("Mechanism Creation");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showMechCreateToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getMechCreateToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showMechModellingToolsToolBar");
  cmdItem->setText("Mechanism Modelling Tools");
  cmdItem->setToolTip("Mechanism Modelling Tools");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showMechModellingToolsToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getMechModellingToolsToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showCtrlCreateToolBar");
  cmdItem->setText("Control System Create");
  cmdItem->setToolTip("Control System Create Toolbar");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showCtrlCreateToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getCtrlCreateToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_mainWin_showCtrlModellingToolsToolBar");
  cmdItem->setText("Control System Modelling Tools");
  cmdItem->setToolTip("Control System Modelling Tools Toolbar");
  cmdItem->setToggledCB(FFaDynCB1S(FapMainWinCmds::showCtrlModellingToolsToolBar,bool));
  cmdItem->setGetToggledCB(FFaDynCB1S(FapMainWinCmds::getCtrlModellingToolsToolBarToggle,bool&));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));
}
//----------------------------------------------------------------------------

void FapMainWinCmds::showModelManager(bool show)
{
  Fui::getMainWindow()->showModelManager(show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getModelManagerToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isModelManagerShown();
}

void FapMainWinCmds::showProperties(bool show)
{
  Fui::getMainWindow()->showProperties(show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getPropertiesToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isPropertiesShown();
}

void FapMainWinCmds::showStdToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::STD,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getStdToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::STD);
}

void FapMainWinCmds::showWindowsToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::WINDOWS,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getWindowsToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::WINDOWS);
}

void FapMainWinCmds::showSolveToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::SOLVE,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getSolveToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::SOLVE);
}

void FapMainWinCmds::showViewCtrlToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::VIEWCTRL,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getViewCtrlToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::VIEWCTRL);
}

void FapMainWinCmds::showThreeDViewsToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::THREEDVIEWS,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getThreeDViewsToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::THREEDVIEWS);
}

void FapMainWinCmds::showMechCreateToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::MECHCREATE,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getMechCreateToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::MECHCREATE);
}

void FapMainWinCmds::showMechModellingToolsToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::MECHMODELLINGTOOLS,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getMechModellingToolsToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::MECHMODELLINGTOOLS);
}

void FapMainWinCmds::showCtrlCreateToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::CTRLCREATE,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getCtrlCreateToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::CTRLCREATE);
}

void FapMainWinCmds::showCtrlModellingToolsToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::CTRLMODELLINGTOOLS,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getCtrlModellingToolsToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::CTRLMODELLINGTOOLS);
}

void FapMainWinCmds::showMechWindToolBar(bool show)
{
  Fui::getMainWindow()->showToolBar(FuiMainWindow::MECHWIND,show);
  FapUACommandHandler::updateAllUICommandsToggle();
}

void FapMainWinCmds::getMechWindToolBarToggle(bool& toggle)
{
  toggle = Fui::getMainWindow()->isToolBarShown(FuiMainWindow::MECHWIND);
}
