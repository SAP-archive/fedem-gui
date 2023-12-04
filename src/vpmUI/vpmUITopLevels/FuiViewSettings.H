// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_VIEW_SETTINGS_H
#define FUI_VIEW_SETTINGS_H

#include <array>
#include <map>

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuLogicButtonGroup.H"
#include "FFuLib/FFuColor.H"

class FFuIOField;
class FFuPushButton;
class FFuToggleButton;
class FFuFrame;
class FFuLabelFrame;
class FFuLabel;
class FFuScale;
class FFuColorDialog;
class FuaViewSettingsValues;


class FuiViewSettings : virtual public FFuTopLevelShell,
			public FFuUAExistenceHandler,
			public FFuUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FuiViewSettings();
  virtual ~FuiViewSettings();

  static FuiViewSettings* create(int xpos=100, int ypos=100,
				 int width=100,int height=100,
				 const char* title = "General Appearance",
				 const char* name  = "FuiViewSettings");

  virtual void setUIValues(const FFuaUIValues* values);
  bool getValues(FuaViewSettingsValues* values) const;

  // Symbol fields

  enum {
    JOINT,
    SPR_DA,
    GEAR,
    LOAD,
    SENSOR,
    STRAIN_ROSETTE,
    STICKER,
    TIRES,
    TRIADS,
    NSYMBOLS};

protected:
  void initWidgets(void);

  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();
  virtual void onPoppedDown();
  virtual bool onClose();

private:
  void onColorEditClicked(FFuComponentBase*);
  void onColDlgChanged(FFuColor aColor, FFuComponentBase*);
  void onColDlgClosed(FFuColor aColor, FFuComponentBase*);

  void placeSymbols(int width, int height);
  void placeDefaultColors(int width, int height);
  void placeViewerOptions(int width, int height);

  // Actions
  virtual bool updateDBValues(bool updateui=true);

  // callbacks
  void toggleValueChanged(int,bool) { this->updateDBValues(); }
  void sliderValueChanged(int)      { this->updateDBValues(); }
  void fieldValueChanged(double)    { this->updateDBValues(); }
  void onCloseButtonClicked()       { this->onClose(); }

protected:
  // Main frames

  FFuLabelFrame *mySymbolsFrame;
  FFuLabelFrame *myDefaultColorFrame;
  FFuLabelFrame *myViewerOptionsFrame;

  // Dialog button:

  FFuPushButton* myCloseButton;

  // Symbols:

  FFuLabel *myOnOffLabel;
  FFuLabel *myColorLabel;
  FFuLabel *mySymbolSizeLabel;
  FFuLabel *myLineWidthLabel;

  FFuToggleButton *myRevoluteJointToggle;
  FFuToggleButton *myBallJointToggle;
  FFuToggleButton *myRigidJointToggle;
  FFuToggleButton *myFreeJointToggle;
  FFuToggleButton *myPrismaticJointToggle;
  FFuToggleButton *myCylindricJointToggle;
  FFuToggleButton *myCamJointToggle;

  FFuToggleButton *myBeamTriadsToggle;
  FFuToggleButton *myBeamsToggle;
  FFuToggleButton *myBeamCSToggle;
  FFuToggleButton *myPartsToggle;
  FFuToggleButton *myPartCSToggle;
  FFuToggleButton *myInternalPartCSsToggle;
  FFuToggleButton *myPartCoGCSToggle;
  FFuToggleButton *myRefPlaneToggle;
  FFuToggleButton *mySeaStateToggle;
  FFuToggleButton *myWavesToggle;

  FFuIOField* mySymbolSizeField;
  FFuScale*   myLineWidthScale;

  std::array<FFuToggleButton*,NSYMBOLS> mySymbolToggles;
  std::array<FFuFrame*       ,NSYMBOLS> mySymbolColFrames;
  std::array<FFuPushButton*  ,NSYMBOLS> mySymbolColEditButtons;
  std::array<FFuColorDialog* ,NSYMBOLS> mySymbolColDialog;

  // Default colors:

  FFuLabel *myGroundedColLabel;
  FFuLabel *myUnattacedColLabel;
  FFuLabel *myBackgroundColLabel;

  FFuFrame *myGroundedColFrame;
  FFuFrame *myUnattachedColFrame;
  FFuFrame *myBackgroundColFrame;

  FFuPushButton *myGroundedColEditButton;
  FFuPushButton *myUnattachedColEditButton;
  FFuPushButton *myBackgroundColEditButton;

  FFuColorDialog *myGroundedColDialog;
  FFuColorDialog *myUnattachedColDialog;
  FFuColorDialog *myBackgroundColDialog;

  // Viewer options

  FFuToggleButton *myFogToggle;
  FFuScale *myFogScale;
  FFuLabel *myFogVisibilityLabel;
  FFuToggleButton *mySimpleTransparencyToggle;
  FFuToggleButton *myAntialiazingToggle;

  // Toggle groups
  FFuLogicButtonGroup myToggleButtonGroup;
  FFuLogicButtonGroup myColorEditButtonGroup;

  // Mapping of the color dialogs and frames
  std::map<FFuColorDialog*,FFuFrame*> myColorDialogMap;

private:
  bool showTireSettings;
};


////////////////////////////////////////////////////////////////////////////////

class FuaViewSettingsValues : public FFuaUIValues
{
  // toggles, symbol size, line width and fog visibility are transfered.
  // Colors are set directly from each color-selector.

public:
  FuaViewSettingsValues() {}
  virtual ~FuaViewSettingsValues() {}

  // Viewer options
  bool isFogOn;
  bool isAntialiazingOn;
  bool isSimpleTransparencyOn;
  double myFogVisibility;

  // symbols
  std::array<bool,FuiViewSettings::NSYMBOLS> isSymbolOn;

  bool isRevoluteJointsOn;
  bool isBallJointsOn;
  bool isRigidJointsOn;
  bool isFreeJointsOn;
  bool isPrismaticJointsOn;
  bool isCylindricJointsOn;
  bool isCamJointsOn;

  bool isBeamTriadsOn;
  bool isBeamsOn;
  bool isBeamCSOn;
  bool isPartsOn;
  bool isPartCSOn;
  bool isInternalPartCSsOn;
  bool isPartCoGCSOn;
  bool isRefPlaneOn;
  bool isSeaStateOn;
  bool isWavesOn;
  double mySymbolSize;
  int myLineWidth;

  // colors
  std::array<FFuColor,FuiViewSettings::NSYMBOLS> mySymbolColor;
  FFuColor myGroundedColor;
  FFuColor myUnattachedColor;
  FFuColor myBackgroundColor;

  bool showTireSettings;
};

#endif
