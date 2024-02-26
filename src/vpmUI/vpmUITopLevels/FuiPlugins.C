// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiPlugins.H"
#include "vpmUI/Fui.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuDialogButtons.H"
#include "vpmPM/FpPM.H"
#include "vpmDB/FmFuncAdmin.H"
#include "vpmApp/vpmAppUAMap/FapUAFunctionProperties.H"


enum {
  OK = FFuDialogButtons::LEFTBUTTON,
  CANCEL = FFuDialogButtons::MIDBUTTON,
  HELP = FFuDialogButtons::RIGHTBUTTON
};

Fmd_SOURCE_INIT(FUI_PLUGINS, FuiPlugins, FFuTopLevelShell);


FuiPlugins::FuiPlugins()
{
  Fmd_CONSTRUCTOR_INIT(FuiPlugins);
}


void FuiPlugins::initWidgets()
{
  std::vector<FpPM::PluginLib> plugins;
  FpPM::getPluginList(plugins);

  myPlugins.resize(plugins.size());
  this->setNoPlugins(plugins.size());
  for (size_t i = 0; i < plugins.size(); i++)
  {
    myPlugins[i] = plugins[i].name;
    pluginToggle[i]->setLabel(plugins[i].name.c_str());
    pluginToggle[i]->toBack();
    pluginLabel[i]->setLabel(plugins[i].sign.c_str());
    pluginLabel[i]->toBack();
  }

  dialogButtons->setButtonClickedCB(FFaDynCB1M(FuiPlugins,this,
                                               onDialogButtonClicked,int));
  dialogButtons->setButtonLabel(OK,    "OK");
  dialogButtons->setButtonLabel(CANCEL,"Cancel");
  dialogButtons->setButtonLabel(HELP,  "Help");

  this->placeWidgets(this->getWidth(),this->getHeight());
}


void FuiPlugins::placeWidgets(int width, int height)
{
  if (!pluginToggle.empty())
  {
    int border = this->getBorder();
    int fieldH = pluginToggle.front()->getHeightHint();
    int yPos = border;
    for (size_t i = 0; i < pluginToggle.size(); i++)
    {
      pluginToggle[i]->setEdgeGeometry(border,width-border,yPos,yPos+fieldH);
      yPos += fieldH;
      pluginLabel[i]->setEdgeGeometry(border+fieldH,width-border,yPos,yPos+fieldH);
      yPos += fieldH+border;
    }
  }

  int dialogBtns = height - dialogButtons->getHeightHint();
  dialogButtons->setEdgeGeometry(0,width,dialogBtns,height);
}


void FuiPlugins::onPoppedUp()
{
  this->placeWidgets(this->getWidth(),this->getHeight());

  std::vector<FpPM::PluginLib> plugins;
  FpPM::getPluginList(plugins);

  for (size_t i = 0; i < plugins.size() && i < pluginToggle.size(); i++)
    pluginToggle[i]->setValue(plugins[i].loaded);
}


bool FuiPlugins::onClose()
{
  this->closeDialog(false);
  return false;
}


void FuiPlugins::onDialogButtonClicked(int button)
{
  bool changed = false;
  switch (button) {
  case OK:
    for (size_t i = 0; i < pluginToggle.size(); i++)
      if (FpPM::togglePlugin(myPlugins[i],pluginToggle[i]->getValue()))
        changed = true;

  case CANCEL:
    this->closeDialog(button == OK);
    break;

  case HELP:
    Fui::showCHM("plugins/plugin-architecture.htm");
  }

  if (changed) {
    FmFuncAdmin::clearInfoTable();
    FapUAExistenceHandler::doUpdateUI(FapUAFunctionProperties::getClassTypeID());
    Fui::updateUICommands();
  }
}


FuiPlugins* FuiPlugins::getUI(bool onScreen)
{
  FuiPlugins* plg = NULL;
  FFuTopLevelShell* uic = FFuTopLevelShell::getInstanceByType(FuiPlugins::getClassTypeID());
  if (!uic)
    uic = plg = FuiPlugins::create(100,100,400,400);
  else
    plg = dynamic_cast<FuiPlugins*>(uic);

  uic->manage(onScreen,true);

  return plg;
}
