// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FuiQtPlugins.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"


FuiPlugins* FuiPlugins::create(int xpos, int ypos,
			       int width, int height,
			       const char* title,
			       const char* name)
{
  return new FuiQtPlugins(xpos,ypos,width,height,title,name);
}


FuiQtPlugins::FuiQtPlugins(int xpos, int ypos,
			   int width, int height,
			   const char* title,
			   const char* name)
  : FFuQtModalDialog(xpos,ypos,width,height,title,name,
                     Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  this->dialogButtons = new FFuQtDialogButtons(this);

  this->initWidgets();
}


void FuiQtPlugins::setNoPlugins(unsigned int nPlugins)
{
  pluginToggle.reserve(nPlugins);
  pluginLabel.reserve(nPlugins);
  while (pluginToggle.size() < nPlugins)
  {
    pluginToggle.push_back(new FFuQtToggleButton(this));
    pluginLabel.push_back(new FFuQtLabel(this));
  }
}
