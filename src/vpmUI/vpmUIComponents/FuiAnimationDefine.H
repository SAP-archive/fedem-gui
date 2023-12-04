// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_ANIMATION_DEFINE_H
#define FUI_ANIMATION_DEFINE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuLogicButtonGroup.H"
#include <string>
#include <vector>
#include <set>

class FuiFringeSheet;
class FuiTimeSheet;
class FuiModesSheet;
class FuiQueryInputField;
class FFuTabbedWidgetStack;
class FFuToggleButton;
class FFuRadioButton;
class FFuPushButton;
class FFuLabel;
class FFuLabelFrame;
class FFuIOField;
class FFuOptionMenu;
class FFuaQueryBase;
class FmModelMemberBase;


class FuiAnimationDefine : virtual public FFuMultUIComponent,
			   public FFuUAExistenceHandler,
			   public FFuUADataHandler
{
public:
  FuiAnimationDefine() {}
  virtual ~FuiAnimationDefine() {}

  void setLoadAnimCB(const FFaDynCB0& dynCB) { this->loadAnimCB = dynCB; }

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // Inside callback functions
  void onLoadAnimButtonClicked() { this->loadAnimCB.invoke(); }
  void onTabSheetChanged() { this->updateDBValues(); }
  void onButtonToggled(bool) { this->updateDBValues(); }
  void onRadioGroupToggled(int,bool) { this->updateDBValues(); }

  // From datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FFuLabelFrame* typeFrame;
  FFuRadioButton* timeRadio;
  FFuRadioButton* eigenRadio;
  FFuRadioButton* summaryRadio;
  FFuLogicButtonGroup typeRadioGroup;

  FFuToggleButton* loadFringeToggle;
  FFuToggleButton* loadLineFringeToggle;
  FFuToggleButton* loadDefToggle;

  FFuPushButton* loadAnimButton;

  FFuTabbedWidgetStack* tabStack;
  FuiFringeSheet* fringeSheet;
  FuiTimeSheet* timeSheet;
  FuiModesSheet* modesSheet;

private:
  FFaDynCB0 loadAnimCB;
};
/////////////////////////////////////////////////////////////////////////////

class FuiFringeSheet : virtual public FFuMultUIComponent
{
public:
  FuiFringeSheet() { showAutoExToggle = false; }
  virtual ~FuiFringeSheet() {}

  void setDataChangedCB(const FFaDynCB0& dynCB) { this->dataChangedCB = dynCB; }

  void setUIValues(const FFuaUIValues* values);
  void getUIValues(FFuaUIValues* values);

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // Inside callback functions
  void onMenuSelected(int) { this->dataChangedCB.invoke(); }
  void onButtonToggled(bool) { this->dataChangedCB.invoke(); }
  void onRadioGroupToggled(int,bool) { this->dataChangedCB.invoke(); }
  void onFieldValueChanged(char*) { this->dataChangedCB.invoke(); }

protected:
  FFuLabelFrame* fringeFrame;
  FFuLabel* resultClassLabel;
  FFuOptionMenu* resultClassMenu;
  FFuLabel* resultLabel;
  FFuOptionMenu* resultMenu;
  FFuLabel* resultOperLabel;
  FFuOptionMenu* resultOperMenu;

  FFuLabelFrame* resultSetFrame;
  FFuRadioButton* setByOperRadio;
  FFuOptionMenu* setOperMenu;
  FFuRadioButton* setByNameRadio;
  FFuOptionMenu* setNameMenu;
  FFuLogicButtonGroup resultSetRadioGroup;

  FFuLabelFrame* averageFrame;
  FFuLabel* averageOperLabel;
  FFuOptionMenu* averageOperMenu;
  FFuLabel* averageOnLabel;
  FFuOptionMenu* averageOnMenu;
  FFuLabel* shellAngleLabel;
  FFuIOField* shellAngleField;
  FFuToggleButton* elementToggle;

  FFuLabelFrame* multiFaceFrame;
  FFuLabel* elemGrpOperLabel;
  FFuOptionMenu* elemGrpOperMenu;

  FFuToggleButton* autoExportToggle;

private:
  FFaDynCB0 dataChangedCB;

  bool showAutoExToggle;
};
/////////////////////////////////////////////////////////////////////////////

class FuiTimeSheet : virtual public FFuMultUIComponent
{
public:
  FuiTimeSheet() {}
  virtual ~FuiTimeSheet() {}

public:
  void setDataChangedCB(const FFaDynCB0& dynCB) { this->dataChangedCB = dynCB; }

  void setUIValues(const FFuaUIValues* values);
  void getUIValues(FFuaUIValues* values);

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // Inside callback functions
  void onButtonToggled(bool) { this->dataChangedCB.invoke(); }
  void onFieldValueChanged(char*) { this->dataChangedCB.invoke(); }
  void onRadioGroupToggled(int,bool) { this->dataChangedCB.invoke(); }

protected:
  FFuLabelFrame* timeFrame;
  FFuRadioButton* completeSimRadio;
  FFuRadioButton* timeIntRadio;
  FFuLogicButtonGroup timeRadioGroup;

  FFuLabel* startLabel;
  FFuLabel* stopLabel;
  FFuIOField* startField;
  FFuIOField* stopField;

  FFuLabelFrame* framesFrame;
  FFuRadioButton* mostFramesRadio;
  FFuRadioButton* leastFramesRadio;
  FFuLogicButtonGroup framesRadioGroup;

private:
  FFaDynCB0 dataChangedCB;
};
/////////////////////////////////////////////////////////////////////////////

class FuiModesSheet : virtual public FFuMultUIComponent
{
public:
  FuiModesSheet() { showLinkMenu = false; }
  virtual ~FuiModesSheet() {}

  void setDataChangedCB(const FFaDynCB0& dynCB) { this->dataChangedCB = dynCB; }

  void setUIValues(const FFuaUIValues* values);
  void getUIValues(FFuaUIValues* values);

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // Inside callback functions
  void onMenuSelected(int) { this->dataChangedCB.invoke(); }
  void onButtonToggled(bool) { this->dataChangedCB.invoke(); }
  void onFieldValueChanged(char*) { this->dataChangedCB.invoke(); }
  void onRadioGroupToggled(int,bool) { this->dataChangedCB.invoke(); }

protected:
  FFuLabelFrame* eigenFrame;
  FFuOptionMenu* typeMenu;
  FFuLabel* linkLabel;
  FuiQueryInputField* linkMenu;
  FFuLabel* timeLabel;
  FFuOptionMenu* timeMenu;
  FFuLabel* modeLabel;
  FFuOptionMenu* modeMenu;
  FFuLabel* scaleLabel;
  FFuIOField* scaleField;

  FFuLabelFrame* animFrame;
  FFuLabel* framesPrLabel;
  FFuIOField* framesPrField;

  FFuLabelFrame* lengthFrame;
  FFuRadioButton* timeLengthRadio;
  FFuIOField* timeLengthField;
  FFuRadioButton* nCyclRadio;
  FFuIOField* nCyclField;
  FFuRadioButton* dampedRadio;
  FFuIOField* dampedField;
  FFuLogicButtonGroup lengthRadioGroup;

  bool showLinkMenu;

private:
  FFaDynCB0 dataChangedCB;
};
/////////////////////////////////////////////////////////////////////////////

class FuaAnimationDefineValues : public FFuaUIValues
{
public:
  FuaAnimationDefineValues() {
    this->isModesAnim = false;
    this->isSummaryAnim = false;
    this->loadFringe = false;
    this->loadLineFringe = false;
    this->loadDef = false;
    this->resultSetByName = false;
    this->shellAngle = 0.0;
    this->acrossElemType = false;
    this->acrossMatBorder = false;
    this->acrossPropBorder = false;
    this->autoExport = false;
    this->complSimul = false;
    this->start = 0.0;
    this->stop = 0.0;
    this->mostFrames = false;
    this->modeTyp = 0;
    this->linkQuery = 0;
    this->selLink = 0;
    this->selTime = 0.0;
    this->selMode = 0;
    this->modeScale = 0.0;
    this->framesPrCycle = 0;
    this->timeLength = false;
    this->timeLengthVal = 0.0;
    this->nCycles = false;
    this->nCyclesVal = 0;
    this->untilDamped = false;
    this->untilDampedVal = 0;
  }
  virtual ~FuaAnimationDefineValues() {}

public:
  // COMMON
  bool isModesAnim;
  bool isSummaryAnim;
  bool loadFringe;
  bool loadLineFringe;
  bool loadDef;

  // FRINGE
  // value
  std::vector<std::string> resultClasses; std::string selResultClass;
  std::set<std::string>    results;       std::string selResult;
  std::vector<std::string> resultOpers;   std::string selResultOper;

  bool resultSetByName;
  std::vector<std::string> resultSetOpers; std::string selResultSetOper;
  std::set<std::string>    resultSets;     std::string selResultSet;

  // Averaging
  std::vector<std::string> averOns;   std::string selAverOn;
  std::vector<std::string> averOpers; std::string selAverOper;

  double shellAngle;
  bool acrossElemType;
  bool acrossMatBorder;
  bool acrossPropBorder;

  // multi face
  std::vector<std::string> elemGrps;     std::string selElemGrp;
  std::vector<std::string> elemGrpOpers; std::string selElemGrpOper;

  char autoExport;

  // TIME
  bool   complSimul;
  double start, stop;
  bool   mostFrames;

  // MODES
  int modeTyp;
  FFuaQueryBase*     linkQuery;
  FmModelMemberBase* selLink;
  std::vector<double> times; double selTime;
  std::vector<int>    modes; int    selMode;

  double modeScale;
  int    framesPrCycle;

  bool timeLength;  double timeLengthVal;
  bool nCycles;     int nCyclesVal;
  bool untilDamped; int untilDampedVal;
};
/////////////////////////////////////////////////////////////////////////////

#endif
