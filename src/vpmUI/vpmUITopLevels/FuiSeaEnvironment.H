// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_SEA_ENVIRONMENT_H
#define FUI_SEA_ENVIRONMENT_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFaLib/FFaAlgebra/FFaVec3.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <vector>
#include <string>

class FFuLabelFrame;
class FFuLabelField;
class FFuLabel;
class FFuDialogButtons;
class Fui3DPoint;
class FuiQueryInputField;
class FuiQueryInputFieldValues;
class FmModelMemberBase;
class FFuaQueryBase;


class FuiSeaEnvironment : virtual public FFuTopLevelShell,
			  public FFuUAExistenceHandler,
			  public FFuUADataHandler,
			  public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiSeaEnvironment();
  virtual ~FuiSeaEnvironment() {}

  static FuiSeaEnvironment* create(int xpos = 100, int ypos = 100,
				   int width = 100, int height = 100,
				   const char* title= "Sea Environment",
				   const char* name = "FuiSeaEnvironment");

  virtual void setSensitivity(bool isSensitive);

protected:
  void initWidgets();
  virtual bool onClose();

private:
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();

  void onCurrentSelected(FmModelMemberBase*);
  void onWaveSelected(FmModelMemberBase*);
  void onDialogButtonClicked(int button);

  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FFuLabelField* waterDensityField;
  FFuLabelField* meanSeaLevelField;
  FFuLabelField* seaDepthField;

  FFuLabelFrame* gravitationFrame;
  Fui3DPoint*    gravitationVector;

  FFuLabelFrame* waveDirectionFrame;
  Fui3DPoint*    waveDirectionVector;

  FFuLabelFrame* marineGrowthFrame;
  FFuLabelField* marineGrowthDensityField;
  FFuLabelField* marineGrowthThicknessField;
  FFuLabelField* marineGrowthUpperLimitField;
  FFuLabelField* marineGrowthLowerLimitField;

  FFuLabel*           waveLabel;
  FuiQueryInputField* waveQueryField;

  FFuLabel*           currLabel;
  FuiQueryInputField* currQueryField;

  FFuLabel*           currDirLabel;
  FuiQueryInputField* currDirQueryField;

  FFuLabel*           currScaleLabel;
  FuiQueryInputField* currScaleQueryField;

  FFuLabel*           hdfScaleLabel;
  FuiQueryInputField* hdfScaleQueryField;

  FFuDialogButtons* dialogButtons;
};
////////////////////////////////////////////////////////////////////////////////

class FuaSeaEnvironmentValues : public FFuaUIValues
{
public:
  FuaSeaEnvironmentValues() {
    this->waterDensity = 0.0;
    this->seaLevelValue = 0.0;
    this->seaDepth = 0.0;
    this->waveQuery = 0;
    this->currQuery = 0;
    this->scaleQuery = 0;
    this->marineGrowthDensity = 0;
    this->marineGrowthThickness = 0;
    this->marineGrowthUpperLimit = 0;
    this->marineGrowthLowerLimit = 0;
    this->waveFunction = 0;
    this->currFunction = 0;
    this->currDirFunction = 0;
    this->currScaleEngine = 0;
    this->hdfScaleEngine = 0;
    this->waveDirSens = true;
    this->isSensitive = true;
  }
  virtual ~FuaSeaEnvironmentValues() {}

  FFuaQueryBase* waveQuery;
  FFuaQueryBase* currQuery;
  FFuaQueryBase* scaleQuery;

  FmModelMemberBase* waveFunction;
  FmModelMemberBase* currFunction;
  FmModelMemberBase* currDirFunction;
  FmModelMemberBase* currScaleEngine;
  FmModelMemberBase* hdfScaleEngine;

  FFaDynCB1<FuiQueryInputFieldValues&> editCB;

  double waterDensity;
  double seaLevelValue;
  double seaDepth;
  FaVec3 gravitation;
  FaVec3 waveDirection;

  double marineGrowthDensity;
  double marineGrowthThickness;
  double marineGrowthUpperLimit;
  double marineGrowthLowerLimit;

  bool waveDirSens;
  bool isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
