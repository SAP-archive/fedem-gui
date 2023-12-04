// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_CMD_ITEM_H
#define FFUA_CMD_ITEM_H

#include <string>
#include <vector>
#include <map>

#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FFuaCmdItem
{
public:
  // A FFuaCmdItem subject to static management must have a cmdItemId string
  // otherwise it escapes the static management
  FFuaCmdItem(const std::string& cmdItemId = "");

  // A FFuaCmdItem must not be deleted as long as it is in use
  virtual ~FFuaCmdItem();

  static FFuaCmdItem* getCmdItem(const std::string& cmdItemId);
  static void enableCmdLogging(bool doEnable) { weAreLoggingCmds = doEnable; }

  const std::string& getCmdItemId() const { return this->cmdItemId; }

  // callbacks
  // activation/toggle
  // if toggleable you get a ToggledCB otherwise you get an ActivatedCB
  void setActivatedCB(const FFaDynCB0& dynCB) {
    this->setToggleAble(false);
    this->activatedCB = dynCB;
  }
  void invokeActivatedCB() ;
  void setToggledCB(const FFaDynCB1<bool>& dynCB) {
    this->setToggleAble(true);
    this->toggledCB = dynCB;
  }
  void invokeToggledCB(bool toggled);

  void setGetSensitivityCB(const FFaDynCB1<bool&>& dynCB) {this->getSensitivityCB = dynCB;}
  // If you dont set this callback you have to initiate the toggle status (setToggled)
  // You should set this cb if possible, ie if the db stores the toggle statuses
  void setGetToggledCB(const FFaDynCB1<bool&>& dynCB) {this->getToggledCB = dynCB;}

private:
  void invokeGetSensitivityCB(bool& sensitivity)
  {this->getSensitivityCB.invoke(sensitivity);}
  void invokeGetToggledCB(bool& toggle)
  {this->getToggledCB.invoke(toggle);}

  static void printCmdListToFile();

  void initVars();

public:
  // item attributes
  // icons are used in front of popupmenu text entries and on toolbuttons
  // small should be < 23 pix
  // popupmenues do always require a small icon, if not it a bigone is scaled
  void setBigIcon(const char** pixMap) { this->bigIcon = pixMap; }
  const char** getBigIcon() const { return this->bigIcon; }

  void setSmallIcon(const char** pixMap) { this->smallIcon = pixMap; }
  const char** getSmallIcon() const { return this->smallIcon; }

  bool hasIcon() const { return this->bigIcon || this->smallIcon; }

  // pixmaps are used as a substitute for the text on popupmenu entries
  void setPixmap(const char** pixMap) { this->pixmap = pixMap; }
  const char** getPixmap() const { return this->pixmap; }

  void setText(const std::string& txt) { this->text = txt; }
  const std::string& getText() const { return this->text; }

  void setToolTip(const std::string& tooltip) { this->toolTip = tooltip; }
  const std::string& getToolTip() const { return this->toolTip; }

  //see FFuaKeyCode
  void setAccelKey(int accelkey) { this->accelKey = accelkey; }
  int getAccelKey() const { return this->accelKey; }

  bool getSensitivity();
  // toggle
  void setToggleAble(bool toggleable) { this->toggleAble = toggleable; }
  bool getToggleAble() const { return this->toggleAble; }

  void setToggled(bool toggle) {
    this->setToggleAble(true);
    this->toggled = toggle;
  }
  bool getToggled();

  void setToggleBehaveAsRadio(bool radio) {
    this->setToggleAble(true);
    this->behaveAsRadio = radio; }
  bool getToggleBehaveAsRadio() const { return this->behaveAsRadio; }

  // menuButtonPopupMode
  void setMenuButtonPopupMode(bool val) { this->menuButtonPopupMode = val; }
  bool getMenuButtonPopupMode() const { return this->menuButtonPopupMode; }

  // FFaInitializer init - used for the cmdItemMap;
  static void init();

private:
  typedef std::map<std::string,FFuaCmdItem*> CommandMap;

  static CommandMap* cmdItemMap;
  static bool weAreLoggingCmds;

  std::string cmdItemId;

  FFaDynCB0        activatedCB;
  FFaDynCB1<bool>  toggledCB;
  FFaDynCB1<bool&> getSensitivityCB;
  FFaDynCB1<bool&> getToggledCB;

  const char** bigIcon;
  const char** smallIcon;
  const char** pixmap;
  std::string text;
  std::string toolTip;
  int  accelKey;
  bool toggleAble;
  bool behaveAsRadio;
  bool toggled;
  bool menuButtonPopupMode;
};
/////////////////////////////////////////////////////////////////////////////

class FFuaCmdHeaderItem : public FFuaCmdItem
{
public:
  // A FFuaCmdHeaderItem is NOT book-kept (in static management)
  FFuaCmdHeaderItem(const std::string& text = "");
  // A FFuaCmdHeaderItem can be deleted even if it is used
  virtual ~FFuaCmdHeaderItem() {}

  void push_back(FFuaCmdItem* child) { myChildren.push_back(child); }
  void clear() { myChildren.clear(); }

  const std::vector<FFuaCmdItem*>& getChildren() const { return myChildren; }

private:
  std::vector<FFuaCmdItem*> myChildren; //!< Leaf FFuaCmdItem objects
};
/////////////////////////////////////////////////////////////////////////////

class FFuaCmdSeparatorItem : public FFuaCmdItem
{
public:
  // A FFuaCmdSeparatorItem is NOT book-kept (in static management)
  FFuaCmdSeparatorItem() {}
  // A FFuaCmdSeparatorItem can be deleted even if it is used
  virtual ~FFuaCmdSeparatorItem() {}
};
/////////////////////////////////////////////////////////////////////////////

static FFaInitialisation<FFuaCmdItem> cmdItemInit;

#endif
