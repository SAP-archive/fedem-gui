// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_PLUGINS_H
#define FUI_PLUGINS_H

#include "FFuLib/FFuBase/FFuModalDialog.H"
#include <vector>
#include <string>

class FFuLabel;
class FFuToggleButton;
class FFuDialogButtons;


class FuiPlugins : virtual public FFuModalDialog
{
  Fmd_HEADER_INIT();

protected:
  FuiPlugins();
  virtual ~FuiPlugins() {}

  static FuiPlugins* create(int xpos = 100, int ypos  = 100,
			    int width= 100, int height= 100,
			    const char* title= "Plug-Ins",
			    const char* name = "FuiPlugins");
public:
  static FuiPlugins* getUI(bool onScreen = true);

protected:
  void initWidgets();

  virtual bool onClose();
  virtual void setNoPlugins(unsigned int nPlugin) = 0;

private:
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();
  virtual void onDialogButtonClicked(int);

protected:
  std::vector<FFuToggleButton*> pluginToggle;
  std::vector<FFuLabel*>        pluginLabel;

  FFuDialogButtons* dialogButtons;

private:
  std::vector<std::string> myPlugins;
};

#endif
