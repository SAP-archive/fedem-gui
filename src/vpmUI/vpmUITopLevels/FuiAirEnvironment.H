// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_AIR_ENVIRONMENT_H
#define FUI_AIR_ENVIRONMENT_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include <string>

class FFuOptionMenu;
class FFuToggleButton;
class FFuPushButton;
class FFuLabel;
class FFuLabelFrame;
class FFuLabelField;
class FFuFileBrowseField;
class FFuDialogButtons;


class FuiAirEnvironment : virtual public FFuTopLevelShell,
			  public FFuUAExistenceHandler,
			  public FFuUADataHandler,
			  public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiAirEnvironment();
  virtual ~FuiAirEnvironment() {}

  static FuiAirEnvironment* create(int xpos = 100, int ypos = 100,
				   int width = 100, int height = 100,
				   const char* title= "Aerodynamic Setup",
				   const char* name = "FuiAirEnvironment");

  virtual void setSensitivity(bool isSensitive);

protected:
  void initWidgets();
  virtual bool onClose();

private:
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();

  void onStallChanged(int);
  void onInflowChanged(int);
  void onInductionChanged(int);
  void onTLossChanged(int);
  void onHLossChanged(int);
  void onWindToggled(bool);
  void onWindTurbClicked(void);
  void onTowerToggled(bool);
  void onDtToggled(bool);
  void onDialogButtonClicked(int button);

  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FFuLabel*           stallModLabel;
  FFuOptionMenu*      stallModMenu;
  FFuToggleButton*    useCMToggle;
  FFuLabel*           infModLabel;
  FFuOptionMenu*      infModMenu;
  FFuLabel*           indModLabel;
  FFuOptionMenu*      indModMenu;
  FFuLabelField*      aTolerField;
  FFuLabel*           tipLossLabel;
  FFuOptionMenu*      tipLossMenu;
  FFuLabel*           hubLossLabel;
  FFuOptionMenu*      hubLossMenu;
  FFuLabelFrame*      windFrame;
  FFuToggleButton*    windToggle;
  FFuPushButton*      windTurbButton;
  FFuLabelField*      windSpeedField;
  FFuLabelField*      windDirField;
  FFuFileBrowseField* windField;
  FFuLabelFrame*      towerFrame;
  FFuToggleButton*    towerPotToggle;
  FFuToggleButton*    towerShdToggle;
  FFuFileBrowseField* towerField;
  FFuLabelField*      airDensField;
  FFuLabelField*      kinViscField;
  FFuLabelField*      dtAeroField;
  FFuToggleButton*    dtAeroToggle;
  FFuDialogButtons*   dialogButtons;

private:
  double myAeroDt;
  double windTurbHubHeight;
  double windTurbGridSize;
  double windTurbDuration;
  double windTurbTimeInc;
  std::string windTurbOutputPath;
};
////////////////////////////////////////////////////////////////////////////////

class FuaAirEnvironmentValues : public FFuaUIValues
{
public:
  FuaAirEnvironmentValues() {
    this->stallMod = 0;
    this->useCM = false;
    this->infMod = this->indMod = 0;
    this->aToler = 0.0;
    this->tlMod = this->hlMod = 0;
    this->constWnd = false;
    this->windVel = this->windDir = 0.0;
    this->twrPot = this->twrShad = false;
    this->airDens = this->kinVisc = this->dtAero = 0.0;
    this->useDSdt = false;
    this->isSensitive = true;
    this->windTurbHubHeight = 0.0;
    this->windTurbGridSize = 0.0;
    this->windTurbDuration = 0.0;
    this->windTurbTimeInc = 0.0;
  }
  virtual ~FuaAirEnvironmentValues() {}

  int         stallMod; //!< Dynamic stall model
  bool        useCM;    //!< Use aerodynamic pitching moment model?
  int         infMod;   //!< Inflow model
  int         indMod;   //!< Induction-factor model
  double      aToler;   //!< Induction-factor tolerance
  int         tlMod;    //!< Tip-loss model (EQUIL only)
  int         hlMod;    //!< Hub-loss model (EQUIL only)
  bool        constWnd; //!< Use constant wind?
  double      windVel;  //!< Constant wind speed
  double      windDir;  //!< Constant wind direction
  std::string windFile; //!< Name of wind data file
  double      windTurbHubHeight;  //!< Used by TurbWind.exe
  double      windTurbGridSize;   //!< Used by TurbWind.exe
  double      windTurbDuration;   //!< Used by TurbWind.exe
  double      windTurbTimeInc;    //!< Used by TurbWind.exe
  bool        twrPot;   //!< Calculate tower potential flow?
  bool        twrShad;  //!< Calculate tower shadow?
  std::string twrFile;  //!< Name of tower drag file
  double      airDens;  //!< Air density (kg/m^3)
  double      kinVisc;  //!< Kinematic air viscosity
  double      dtAero;   //!< Time interval for aerodynamic calculations
  bool        useDSdt;  //!< Use dynamics solver time interval?

  std::string modelFilePath; //!< Path to current model file
  bool        isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
