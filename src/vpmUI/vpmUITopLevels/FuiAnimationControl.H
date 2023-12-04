// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_ANIMATION_CONTROL_H
#define FUI_ANIMATION_CONTROL_H

#include <vector>
#include <string>

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuRadioButton.H"

class FFuToggleButton;
class FFuPushButton;
class FFuLabel;
class FFuLabelFrame;
class FFuIOField;
class FFuOptionMenu;
class FFuDialogButtons;
class FuaQueryBase;
class FmModelMemberBase;
class FuiQueryInputField;
class FFuaQueryBase;


class FuiAnimationControl : virtual public FFuTopLevelShell,
                            public FFuUAExistenceHandler,
                            public FFuUADataHandler,
                            public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiAnimationControl();
  virtual ~FuiAnimationControl() {}
  static FuiAnimationControl* create(int xpos = 100, int ypos  = 100,
                                     int width= 100, int height= 100,
                                     const char* title= "Animation Control",
                                     const char* name = "FuiQtAnimationControl");

  virtual void setSensitivity(bool isSensitive);

protected:
  void initWidgets();
  virtual bool onClose();

private:
  virtual void placeWidgets(int width,int height);
  virtual void onPoppedUp();

  // Inside callback functions
  void onButtonToggled(bool)      { this->updateDBValues(); }
  void onMenuSelected(int)        { this->updateDBValues(); }
  void onFieldValueChanged(char*) { this->updateDBValues(); }

  void onTickMarkCountToggled(bool toggle) {
    this->tickMarkSpaceRadio->setValue(!toggle);
    this->updateDBValues();}
  void onTickMarkSpaceToggled(bool toggle) {
    this->tickMarkCountRadio->setValue(!toggle);
    this->updateDBValues();}

  void onDialogButtonClicked(int button);

  // From datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FFuLabelFrame*      cameraFrame;
  FFuLabel*           cameraLabel;
  FuiQueryInputField* cameraMenu;

  FFuLabelFrame*   motionFrame;
  FFuToggleButton* linkMotionToggle;
  FFuToggleButton* triadMotionToggle;

  FFuLabelFrame*   defFrame;
  FFuToggleButton* defToggle;
  FFuLabel*        defScaleLabel;
  FFuIOField*      defScaleField;

  FFuLabelFrame*   legendFrame;
  FFuToggleButton* fringeToggle;
  FFuToggleButton* legendToggle;

  FFuLabel*      legendColorsLabel;
  FFuOptionMenu* legendColorsMenu;
  FFuLabel*      legendMappingLabel;
  FFuOptionMenu* legendMappingMenu;
  FFuLabel*      legendLookLabel;
  FFuOptionMenu* legendLookMenu;

  FFuLabel*   legendMaxLabel;
  FFuIOField* legendMaxField;
  FFuLabel*   legendMinLabel;
  FFuIOField* legendMinField;

  FFuLabelFrame*  tickMarkFrame;
  FFuRadioButton* tickMarkCountRadio;
  FFuIOField*     tickMarkCountField;
  FFuRadioButton* tickMarkSpaceRadio;
  FFuIOField*     tickMarkSpaceField;

  FFuDialogButtons* dialogButtons;
};
/////////////////////////////////////////////////////////////////////////////

class FuaAnimationControlValues : public FFuaUIValues
{
public:
  FuaAnimationControlValues()
  {
    this->linkMotion         = false;
    this->triadMotion        = false;
    this->def                = false;
    this->defScale           = 0.0;
    this->defScalePossible   = false;
    this->fringe             = false;
    this->legend             = false;
    this->legendRange        = std::make_pair(0.0,0.0);
    this->tickMarkCount      = false;
    this->tickMarkCountVal   = 0;
    this->tickMarkSpacingVal = 0.0;
    this->myLinkQuery        = NULL;
    this->myLinkToFollow     = NULL;
  }
  virtual ~FuaAnimationControlValues() {}

  // Follow-me camera
  FFuaQueryBase*     myLinkQuery;
  FmModelMemberBase* myLinkToFollow;

  // motion
  bool linkMotion,triadMotion;

  // def
  bool   def;
  double defScale;
  bool   defScalePossible;

  // legend
  bool fringe,legend;

  std::vector<std::string> legendColors;   std::string selLegendColor;
  std::vector<std::string> legendMappings; std::string selLegendMapping;
  std::vector<std::string> legendLooks;    std::string selLegendLook;

  std::pair<double,double> legendRange;

  // tick marks
  bool   tickMarkCount;
  int    tickMarkCountVal;
  double tickMarkSpacingVal;
};
/////////////////////////////////////////////////////////////////////////////

#endif
