// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiSeaEnvironment.H"
#include "vpmUI/vpmUITopLevels/FuiModelPreferences.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "vpmUI/vpmUIComponents/Fui3DPoint.H"
#include "vpmUI/Fui.H"
#include "vpmPM/FpPM.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuFrame.H"
#include "vpmDB/FmDB.H"


enum {
  APPLY  = FFuDialogButtons::LEFTBUTTON,
  CANCEL = FFuDialogButtons::MIDBUTTON,
  HELP =   FFuDialogButtons::RIGHTBUTTON
};

Fmd_SOURCE_INIT(FUI_SEAENVIRONMENT,FuiSeaEnvironment,FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiSeaEnvironment::FuiSeaEnvironment()
{
  Fmd_CONSTRUCTOR_INIT(FuiSeaEnvironment);
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::setSensitivity(bool isSensitive)
{
  this->dialogButtons->setButtonSensitivity(APPLY,isSensitive);
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::initWidgets()
{
  this->dialogButtons->setButtonClickedCB(FFaDynCB1M(FuiSeaEnvironment,this,
						     onDialogButtonClicked,int));

  this->dialogButtons->setButtonLabel(APPLY,"Save");
  this->dialogButtons->setButtonLabel(CANCEL,"Close");
  this->dialogButtons->setButtonLabel(HELP,"Help");

  this->waterDensityField->setLabel("Water density");
  this->waterDensityField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->waterDensityField->myField->setDoubleDisplayPrecision(6);

  this->seaDepthField->setLabel("Water depth");
  this->seaDepthField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->seaDepthField->myField->setDoubleDisplayPrecision(6);
  this->seaDepthField->setToolTip("Depth<=0 will be interpreted as deep water");

  this->meanSeaLevelField->setLabel("Mean sea level");
  this->meanSeaLevelField->setToolTip("Height of the sea surface above global origin\n"
                                      "in opposite direction of the gravity vector");
  this->meanSeaLevelField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->meanSeaLevelField->myField->setDoubleDisplayPrecision(6);

  this->gravitationFrame->setLabel("Gravitation");
  this->gravitationVector->setLook(FFuFrame::FLAT);
  this->gravitationVector->setToolTip("The normal vector of the calm sea surface\n"
                                      "has opposite direction of this vector");

  this->waveDirectionFrame->setLabel("Wave direction");
  this->waveDirectionVector->setLook(FFuFrame::FLAT);
  this->waveDirectionVector->setToolTip("The wave propagation vector. "
					"Not used if the Wave function\n"
					"also is used in a Vessel motion (RAO). "
					"In that case, the initial local axes of\n"
					"the Vessel Triad are used instead.");

  this->marineGrowthFrame->setLabel("Marine growth");
  this->marineGrowthDensityField->setLabel("Density");
  this->marineGrowthDensityField->setLabelWidth(50);
  this->marineGrowthDensityField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->marineGrowthDensityField->myField->setDoubleDisplayPrecision(6);
  this->marineGrowthThicknessField->setLabel("Thickness");
  this->marineGrowthThicknessField->setLabelWidth(50);
  this->marineGrowthThicknessField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->marineGrowthThicknessField->myField->setDoubleDisplayPrecision(6);
  this->marineGrowthUpperLimitField->setLabel("Upper limit");
  this->marineGrowthUpperLimitField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->marineGrowthUpperLimitField->myField->setDoubleDisplayPrecision(6);
  this->marineGrowthLowerLimitField->setLabel("Lower limit");
  this->marineGrowthLowerLimitField->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->marineGrowthLowerLimitField->myField->setDoubleDisplayPrecision(6);

  this->waveLabel->setLabel("Wave function");
  this->waveQueryField->setBehaviour(FuiQueryInputField::REF_NONE);
  this->waveQueryField->setButtonMeaning(FuiQueryInputField::EDIT);
  this->waveQueryField->setToolTip("Press the \"Help\" button for details on the\n"
				   "reference coordinate system of the wave kinematics.");
  this->waveQueryField->setRefSelectedCB(FFaDynCB1M(FuiSeaEnvironment,this,
						    onWaveSelected,FmModelMemberBase*));

  this->currLabel->setLabel("Current function");
  this->currQueryField->setBehaviour(FuiQueryInputField::REF_NONE);
  this->currQueryField->setButtonMeaning(FuiQueryInputField::EDIT);
  this->currQueryField->setToolTip("Sea current magnitude as function of Z (and time).\n"
				   "Press the \"Help\" button for details on the\n"
				   "reference coordinate system of the wave kinematics,\n"
				   "which also applies to the current functions.");
  this->currQueryField->setRefSelectedCB(FFaDynCB1M(FuiSeaEnvironment,this,
						    onCurrentSelected,FmModelMemberBase*));

  this->currDirLabel->setLabel("Current direction");
  this->currDirQueryField->setBehaviour(FuiQueryInputField::REF_NONE);
  this->currDirQueryField->setTextForNoRefSelected("0.0");
  this->currDirQueryField->setButtonMeaning(FuiQueryInputField::EDIT);
  this->currDirQueryField->setToolTip("Angle (in radians) between the wave direction "
				      "and current direction as function of Z (and time).\n"
				      "A zero angle implies that the current is in the "
				      "direction of the wave propagation direction.");

  this->currScaleLabel->setLabel("Current scale");
  this->currScaleQueryField->setBehaviour(FuiQueryInputField::REF_NONE);
  this->currScaleQueryField->setButtonMeaning(FuiQueryInputField::EDIT);
  this->currScaleQueryField->setToolTip("Optional scaling of the sea current magnitude");

  this->hdfScaleLabel->setLabel("Hydrodynamic force scale");
  this->hdfScaleQueryField->setBehaviour(FuiQueryInputField::REF_NONE);
  this->hdfScaleQueryField->setButtonMeaning(FuiQueryInputField::EDIT);
  this->hdfScaleQueryField->setToolTip("Optional scaling of the hydrodynamic forces");

  this->placeWidgets(this->getWidth(),this->getHeight());

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::placeWidgets(int width, int height)
{
  int border = this->getBorder();
  int buttonsTop = height - this->dialogButtons->getHeightHint();

  int fontHeight = this->getFontHeigth();
  int fieldHeight = this->waterDensityField->myField->getHeightHint();
  int vectorHeight = fontHeight + 81*fieldHeight/25 + 3*border/2;

  int v1 = border;
  int v2 = width - border;
  int v3 = (width - border)/2;
  int v4 = v3 + border;
  int v5 = v1 + this->currDirLabel->getWidthHint();
  int v6 = v5 + border;
  int v7 = v1 + this->hdfScaleLabel->getWidthHint();
  int v8 = v7 + border;

  int h1 = border;
  int h2 = h1 + fieldHeight;
  int h3 = h2 + border;
  int h4 = h3 + fieldHeight;
  int h5 = h4 + border;
  int h6 = h5 + vectorHeight;
  int h7 = h5 + border/2 + fontHeight;
  int h8 = h6 - border;

  int h9a = h6 + border;
  int h9b = h9a + 75;

  int h10 = h9b  + border;
  int h11 = h10 + fieldHeight;
  int h12 = h11 + border;
  int h13 = h12 + fieldHeight;
  int h14 = h13 + border;
  int h15 = h14 + fieldHeight;
  int h16 = h15 + border;
  int h17 = h16 + fieldHeight;
  int h18 = h17 + 2*border;
  int h19 = h18 + fieldHeight;

  this->waterDensityField->setEdgeGeometry(v1, v3, h1, h2);
  this->waterDensityField->setLabelWidth(v5-v1);
  this->meanSeaLevelField->setEdgeGeometry(v1, v3, h3, h4);
  this->meanSeaLevelField->setLabelWidth(v5-v1);
  this->seaDepthField->setEdgeGeometry(v4,v2, h3, h4);

  this->gravitationFrame ->setEdgeGeometry(v1,  v3,  h5, h6);
  this->gravitationVector->setEdgeGeometry(v1+2,v3-2,h7, h8);

  this->waveDirectionFrame ->setEdgeGeometry(v4,  v2,  h5, h6);
  this->waveDirectionVector->setEdgeGeometry(v4+2,v2-2,h7, h8);

  this->marineGrowthFrame->setEdgeGeometry(v1, v2, h9a, h9b);
  this->marineGrowthDensityField->setEdgeGeometry(v1+9,   v3-10,  h9a+20, h9a+20+18);
  this->marineGrowthThicknessField->setEdgeGeometry(v1+9, v3-10,  h9a+42, h9a+42+18);
  this->marineGrowthUpperLimitField->setEdgeGeometry(v4,  v2-10,  h9a+20, h9a+20+18);
  this->marineGrowthLowerLimitField->setEdgeGeometry(v4,  v2-10,  h9a+42, h9a+42+18);

  this->waveLabel     ->setEdgeGeometry(v1, v5, h10, h11);
  this->waveQueryField->setEdgeGeometry(v6, v2, h10, h11);

  this->currLabel     ->setEdgeGeometry(v1, v5, h12, h13);
  this->currQueryField->setEdgeGeometry(v6, v2, h12, h13);

  this->currDirLabel     ->setEdgeGeometry(v1, v5, h14, h15);
  this->currDirQueryField->setEdgeGeometry(v6, v2, h14, h15);

  this->currScaleLabel     ->setEdgeGeometry(v1, v5, h16, h17);
  this->currScaleQueryField->setEdgeGeometry(v6, v2, h16, h17);

  this->hdfScaleLabel     ->setEdgeGeometry(v1, v7, h18, h19);
  this->hdfScaleQueryField->setEdgeGeometry(v8, v2, h18, h19);

  this->dialogButtons->setEdgeGeometry(0,width,buttonsTop,height);
}
//-----------------------------------------------------------------------------

void FuiSeaEnvironment::onPoppedUp()
{
  this->placeWidgets(this->getWidth(),this->getHeight());
  this->updateUIValues();
}
//----------------------------------------------------------------------------

bool FuiSeaEnvironment::onClose()
{
  this->invokeFinishedCB();
  return false;
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::onDialogButtonClicked(int button)
{
  switch (button)
  {
    case APPLY:
      FpPM::vpmSetUndoPoint("Sea environment");
      this->updateDBValues();
      FmDB::drawSea();
      break;

    case CANCEL:
      this->invokeFinishedCB();
      return;

    case HELP:
      // Display the topic in the help file
      Fui::showCHM("dialogbox/marine/sea-environment.htm");
      break;
  }

  // Also update the model preferences UI,
  // since the Gravitation vector are in both UI's
  FFuTopLevelShell* pref = FFuTopLevelShell::getInstanceByType(FuiModelPreferences::getClassTypeID());
  if (pref) dynamic_cast<FuiModelPreferences*>(pref)->updateUIValues();
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::onCurrentSelected(FmModelMemberBase* current)
{
  this->currDirQueryField->setSensitivity(current != NULL);
  this->currScaleQueryField->setSensitivity(current != NULL);
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::onWaveSelected(FmModelMemberBase* wave)
{
  this->seaDepthField->setSensitivity(wave != NULL);
  this->hdfScaleQueryField->setSensitivity(wave != NULL);
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiSeaEnvironment::createValuesObject()
{
  return new FuaSeaEnvironmentValues();
}
//----------------------------------------------------------------------------

void FuiSeaEnvironment::setUIValues(const FFuaUIValues* values)
{
  FuaSeaEnvironmentValues* envValues = (FuaSeaEnvironmentValues*) values;

  this->waterDensityField->setValue(envValues->waterDensity);
  this->meanSeaLevelField->setValue(envValues->seaLevelValue);
  this->seaDepthField->setValue(envValues->seaDepth);
  this->gravitationVector->setValue(envValues->gravitation);
  this->waveDirectionVector->setValue(envValues->waveDirection);

  this->marineGrowthDensityField->setValue(envValues->marineGrowthDensity);
  this->marineGrowthThicknessField->setValue(envValues->marineGrowthThickness);
  this->marineGrowthUpperLimitField->setValue(envValues->marineGrowthUpperLimit);
  this->marineGrowthLowerLimitField->setValue(envValues->marineGrowthLowerLimit);

  this->waveQueryField->setQuery(envValues->waveQuery);
  this->waveQueryField->setSelectedRef(envValues->waveFunction);
  this->waveQueryField->setButtonCB(envValues->editCB);

  this->currQueryField->setQuery(envValues->currQuery);
  this->currQueryField->setSelectedRef(envValues->currFunction);
  this->currQueryField->setButtonCB(envValues->editCB);

  this->currDirQueryField->setQuery(envValues->currQuery);
  this->currDirQueryField->setSelectedRef(envValues->currDirFunction);
  this->currDirQueryField->setButtonCB(envValues->editCB);

  this->currScaleQueryField->setQuery(envValues->scaleQuery);
  this->currScaleQueryField->setSelectedRef(envValues->currScaleEngine);
  this->currScaleQueryField->setButtonCB(envValues->editCB);

  this->hdfScaleQueryField->setQuery(envValues->scaleQuery);
  this->hdfScaleQueryField->setSelectedRef(envValues->hdfScaleEngine);
  this->hdfScaleQueryField->setButtonCB(envValues->editCB);

  this->waveDirectionVector->setSensitivity(envValues->waveDirSens);
  this->onCurrentSelected(envValues->currFunction);
  this->onWaveSelected(envValues->waveFunction);
  this->setSensitivity(envValues->isSensitive);
}
//-----------------------------------------------------------------------------

void FuiSeaEnvironment::getUIValues(FFuaUIValues* values)
{
  FuaSeaEnvironmentValues* envValues = (FuaSeaEnvironmentValues*) values;

  envValues->waterDensity    = this->waterDensityField->getValue();
  envValues->seaLevelValue   = this->meanSeaLevelField->getValue();
  envValues->seaDepth        = this->seaDepthField->getValue();
  envValues->gravitation     = this->gravitationVector->getValue();
  envValues->waveDirection   = this->waveDirectionVector->getValue();

  envValues->marineGrowthDensity    = this->marineGrowthDensityField->getValue();
  envValues->marineGrowthThickness  = this->marineGrowthThicknessField->getValue();
  envValues->marineGrowthLowerLimit = this->marineGrowthLowerLimitField->getValue();
  envValues->marineGrowthUpperLimit = this->marineGrowthUpperLimitField->getValue();

  envValues->waveFunction    = this->waveQueryField->getSelectedRef();
  envValues->currFunction    = this->currQueryField->getSelectedRef();
  envValues->currDirFunction = this->currDirQueryField->getSelectedRef();
  envValues->currScaleEngine = this->currScaleQueryField->getSelectedRef();
  envValues->hdfScaleEngine  = this->hdfScaleQueryField->getSelectedRef();
}
