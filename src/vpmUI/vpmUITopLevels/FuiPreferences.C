// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiPreferences.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuRadioButton.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <iostream>


Fmd_SOURCE_INIT(FUI_PREFERENCES, FuiPreferences, FFuTopLevelShell);


//----------------------------------------------------------------------------

FuiPreferences::FuiPreferences()
{
  Fmd_CONSTRUCTOR_INIT(FuiPreferences);

  this->optFields.fill(NULL);
  this->labels.fill(NULL);

  this->reducerFrame = NULL;
  this->eqSolverToggle     = this->recMatrixToggle = NULL;
  this->eqSolverCacheLabel = this->recMatrixCacheLabel = NULL;
  this->eqSolverAutomatic  = this->eqSolverManual  = NULL;
  this->recMatrixAutomatic = this->recMatrixManual = NULL;

  this->isRestartActive = false;
  this->isSensitive = true;
}
//----------------------------------------------------------------------------

void FuiPreferences::initWidgets()
{
  for (FFuIOField* field : this->optFields) {
    field->setInputCheckMode(FFuIOField::NOCHECK);
    field->setAcceptPolicy(FFuIOField::ENTERONLY);
  }

  this->optFields[MAX_CONC_PROC]->setInputCheckMode(FFuIOField::INTEGERCHECK);
  this->optFields[EQ_SOLVER_SWAP]->setInputCheckMode(FFuIOField::INTEGERCHECK);
  this->optFields[REC_MATRIX_SWAP]->setInputCheckMode(FFuIOField::INTEGERCHECK);

  this->labels[REDUCER]->setLabel("FE model Reducer");
  this->labels[SOLVER]->setLabel("Dynamics Solver");
  this->labels[STRESS]->setLabel("Stress Recovery");
  this->labels[MODES]->setLabel("Mode Shape Recovery");
  this->labels[GAGE]->setLabel("Strain Rosette Recovery");
  this->labels[FPP]->setLabel("Strain Coat Recovery Summary");
  this->labels[MAX_CONC_PROC]->setLabel("Max concurrent processes");
  this->labels[EQ_SOLVER_SWAP]->setLabel("[MB]");
  this->labels[REC_MATRIX_SWAP]->setLabel("[MB]");
  this->labels[SOLVER_PREFIX]->setLabel("Remote shell command prefix");
  this->labels[SOLVER_PATH]->setLabel("Model path on remote system");

  this->reducerFrame->setLabel("FE model Reducer Out-of-core Options ");
  this->eqSolverToggle->setLabel("Equation solver out-of-core");
  this->eqSolverToggle->setToggleCB(FFaDynCB1M(FuiPreferences,this,
					       onEqSolverToggeled,bool));
  this->eqSolverCacheLabel->setLabel("Cache size:");
  this->recMatrixCacheLabel->setLabel("Cache size:");

  this->eqSolverAutomatic->setLabel("Automatic");
  this->eqSolverManual->setLabel("Manual");
  this->eqSolverBtnGroup.insert(this->eqSolverAutomatic);
  this->eqSolverBtnGroup.insert(this->eqSolverManual);
  this->eqSolverBtnGroup.setValue(this->eqSolverAutomatic,true);
  this->eqSolverBtnGroup.setGroupToggleCB(FFaDynCB2M(FuiPreferences,this,
                                                     onEqSolverGroupToggeled,
                                                     int,bool));

  this->recMatrixToggle->setLabel("Recovery matrix out-of-core");
  this->recMatrixToggle->setToggleCB(FFaDynCB1M(FuiPreferences,this,
						onRecMatrixToggeled,bool));
  this->recMatrixAutomatic->setLabel("Automatic");
  this->recMatrixManual->setLabel("Manual");
  this->recMatrixBtnGroup.insert(this->recMatrixAutomatic);
  this->recMatrixBtnGroup.insert(this->recMatrixManual);
  this->recMatrixBtnGroup.setValue(this->recMatrixAutomatic,true);
  this->recMatrixBtnGroup.setGroupToggleCB(FFaDynCB2M(FuiPreferences,this,
                                                      onRecMatrixGroupToggeled,
                                                      int,bool));

  this->remoteSolveFrame->setLabel("Remote solve options");
  this->solverPrefixToggle->setLabel("Perform remote solve");
  this->solverPrefixToggle->setToggleCB(FFaDynCB1M(FuiPreferences,this,
						   onSolvePrefixToggeled,bool));
  this->solverPathToggle->setToggleCB(FFaDynCB1M(FuiPreferences,this,
						 onSolvePathToggeled,bool));

  this->FuiTopLevelDialog::initWidgets();
}
//----------------------------------------------------------------------------

void FuiPreferences::placeWidgets(int width, int height)
{
  //l-left, r-right, t-top, b-bottom,
  int border      = this->getBorder();
  int labH        = this->labels[0]->getHeightHint();
  int linefieldH  = this->optFields[0]->getHeightHint();
  int buttonH     = this->dialogButtons->getHeightHint();
  int mcpWidth    = this->labels[MAX_CONC_PROC]->getWidthHint();
  int autoWidth   = this->eqSolverAutomatic->getWidthHint();
  int manualWidth = this->eqSolverManual->getWidthHint();
  int swapWidth   = this->labels[EQ_SOLVER_SWAP]->getWidthHint();
  int cacheWidth  = this->eqSolverCacheLabel->getWidthHint();
  int toggleWidth = this->recMatrixToggle->getHeightHint();;

  //GridLines
  //vertical borders
  int glvL  = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_START);
  int glvL2 = glvL + border; // for fields with toggle buttons
  int glvL3 = glvL2 + toggleWidth + 0*border; // for fields with toggle buttons
  int glvL4 = glvL + mcpWidth + border;
  int glvL45 = glvL3 + cacheWidth + border;
  int glvL5 = glvL45 + autoWidth + border;
  int glvL6 = glvL5 + manualWidth + border/2;
  int glvR  = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_END);
  int glvR2 = glvR - border;
  int glvR3 = glvR2 - swapWidth;

  //horisontal borders
  int fieldH  = labH + linefieldH;
  int glhTop  = this->getGridLinePos(height,border,FFuMultUIComponent::FROM_START);
  int glhDiaB = this->getGridLinePos(height,buttonH,FFuMultUIComponent::FROM_END);
  int nFields = FapLicenseManager::isProEdition() ? NFIELDS : MAX_CONC_PROC;
  int stretch = glhDiaB - glhTop - nFields*fieldH;
  if (FapLicenseManager::isProEdition()) stretch -= 3*labH + 5*border;

  //Shrink labH and linefieldH in order to avoid overlap if negative stretch
  if (stretch < 0) {
    stretch    /= nFields+1;
    fieldH     += stretch;
    linefieldH += stretch/2;
    labH       += stretch/2;
    stretch     = 0;
  }
  else {
    stretch /= nFields+4;
    fieldH  += stretch;
  }

  int iField;
  int glh[NFIELDS];
  glh[0] = glhTop;
  for (iField = 1; iField < NFIELDS; iField++)
    glh[iField] = glh[iField-1] + fieldH;

  glh[MAX_CONC_PROC] += border;
  glh[EQ_SOLVER_SWAP] += labH + 2*stretch + 2*border;
  glh[REC_MATRIX_SWAP] += labH + 3*stretch + 3*border;
  for (iField = SOLVER_PREFIX; iField < NFIELDS; iField++)
    glh[iField] += 3*labH + 5*stretch + 4*border;

  //Place widgets
  for (iField = REDUCER; iField <= FPP; iField++) {
    this->labels[iField]->setSizeGeometry(glvL,glh[iField], glvR-glvL,labH);
    this->optFields[iField]->setSizeGeometry(glvL,glh[iField]+labH, glvR-glvL,linefieldH);
  }

  iField = MAX_CONC_PROC;
  this->labels[iField]->setSizeGeometry(glvL,glh[iField], mcpWidth,labH);
  this->optFields[iField]->setSizeGeometry(glvL4,glh[iField], glvR-glvL4,linefieldH);

  for (iField = EQ_SOLVER_SWAP; iField <= REC_MATRIX_SWAP; iField++) {
    this->labels[iField]->setSizeGeometry(glvR3,glh[iField], swapWidth,labH);
    this->optFields[iField]->setSizeGeometry(glvL6,glh[iField], glvR3-glvL6-border/2,linefieldH);
  }

  for (iField = SOLVER_PREFIX; iField <= SOLVER_PATH; iField++) {
    this->labels[iField]->setSizeGeometry(glvL3,glh[iField], glvR2-glvL3,labH);
    this->optFields[iField]->setSizeGeometry(glvL3,glh[iField]+labH, glvR2-glvL3,linefieldH);
  }

  this->eqSolverToggle->setSizeGeometry(glvL2, glh[EQ_SOLVER_SWAP]-labH-stretch,
					glvR2-glvL2, labH);
  this->eqSolverCacheLabel->setSizeGeometry(glvL3, glh[EQ_SOLVER_SWAP], cacheWidth, labH);
  this->eqSolverAutomatic->setSizeGeometry(glvL45, glh[EQ_SOLVER_SWAP], autoWidth, labH);
  this->eqSolverManual->setSizeGeometry(glvL5, glh[EQ_SOLVER_SWAP], manualWidth, labH);

  this->recMatrixToggle->setSizeGeometry(glvL2, glh[REC_MATRIX_SWAP]-labH-stretch,
					 glvR2-glvL2, labH);

  this->recMatrixCacheLabel->setSizeGeometry(glvL3, glh[REC_MATRIX_SWAP], cacheWidth, labH);
  this->recMatrixAutomatic->setSizeGeometry(glvL45, glh[REC_MATRIX_SWAP], autoWidth, labH);
  this->recMatrixManual->setSizeGeometry(glvL5, glh[REC_MATRIX_SWAP], manualWidth, labH);

  this->reducerFrame->setEdgeGeometry(glvL, glvR,
				      glh[EQ_SOLVER_SWAP]-2*labH-2*stretch,
				      glh[REC_MATRIX_SWAP]+linefieldH+border);
  this->reducerFrame->toBack();

  this->solverPrefixToggle->setSizeGeometry(glvL2, glh[SOLVER_PREFIX]-labH-stretch,
					    glvR2-glvL2, labH);
  this->solverPathToggle->setSizeGeometry(glvL2, glh[SOLVER_PATH]+labH, toggleWidth, labH);

  this->remoteSolveFrame->setEdgeGeometry(glvL, glvR,
					  glh[SOLVER_PREFIX]-2*labH-2*stretch,
					  glh[SOLVER_PATH]+labH+linefieldH+border);
  this->remoteSolveFrame->toBack();

  if (FapLicenseManager::isProEdition()) {
    // Show fields that are available in the pro-edition only
    this->optFields[FPP]->setSensitivity(true);
    for (iField = EQ_SOLVER_SWAP; iField <= SOLVER_PATH; iField++) {
      this->labels[iField]->popUp();
      this->optFields[iField]->popUp();
    }
    this->reducerFrame->popUp();
    this->eqSolverToggle->popUp();
    this->eqSolverCacheLabel->popUp();
    this->eqSolverAutomatic->popUp();
    this->eqSolverManual->popUp();
    this->recMatrixToggle->popUp();
    this->recMatrixCacheLabel->popUp();
    this->recMatrixAutomatic->popUp();
    this->recMatrixManual->popUp();
    this->remoteSolveFrame->popUp();
    this->solverPrefixToggle->popUp();
    this->solverPathToggle->popUp();
  }
  else {
    // Hide fields that are available in the pro-edition only
    this->optFields[FPP]->setSensitivity(false);
    for (iField = EQ_SOLVER_SWAP; iField <= SOLVER_PATH; iField++) {
      this->labels[iField]->popDown();
      this->optFields[iField]->popDown();
    }
    this->reducerFrame->popDown();
    this->eqSolverToggle->popDown();
    this->eqSolverCacheLabel->popDown();
    this->eqSolverAutomatic->popDown();
    this->eqSolverManual->popDown();
    this->recMatrixToggle->popDown();
    this->recMatrixCacheLabel->popDown();
    this->recMatrixAutomatic->popDown();
    this->recMatrixManual->popDown();
    this->remoteSolveFrame->popDown();
    this->solverPrefixToggle->popDown();
    this->solverPathToggle->popDown();
  }

  this->dialogButtons->setEdgeGeometry(0,width,glhDiaB,height);
}
//-----------------------------------------------------------------------------

bool FuiPreferences::updateDBValues(bool)
{
  //unhighligh fields since qt enables mult field highlighting (qt bug ?)
  for (FFuIOField* field : this->optFields)
    field->unHighlight();

  //get ui values
  FuaPreferencesValues values;
  for (int iField = 0; iField < NFIELDS; iField++)
    values.options[iField] = this->optFields[iField]->getValue();

  values.useEqSolverBuffer = this->eqSolverToggle->getValue();
  values.autoEqSolverBuffer = this->eqSolverAutomatic->getValue();

  values.useRecMatrixBuffer = this->recMatrixToggle->getValue();
  values.autoRecMatrixBuffer = this->recMatrixAutomatic->getValue();

  values.useSolverPrefix = this->solverPrefixToggle->getValue();
  values.useSolverPath = this->solverPathToggle->getValue();

  // Lambda function checking that an integer field has a valid value
  auto&& isValid = [this,&values](int iField, int minVal = 0)
  {
    bool& status = values.optionStatus[iField];
    if (!this->optFields[iField]->isInt())
      status = false;
    else if (this->optFields[iField]->getInt() < minVal)
      status = false;
    else
      status = true;

    return status;
  };

  if (isValid(MAX_CONC_PROC,1) & isValid(EQ_SOLVER_SWAP) & isValid(REC_MATRIX_SWAP)) {
    //all values are ok for the ui
    this->invokeSetAndGetDBValuesCB(&values);
    //Reset values to ensure value correspondance between ui and db
    for (int iField = 0; iField < NFIELDS; iField++)
      if (values.optionStatus.find(iField) == values.optionStatus.end())
        this->optFields[iField]->setValue(values.options[iField]);
    for (const std::pair<const int,bool>& status : values.optionStatus)
      if (status.second)
        this->optFields[status.first]->setValue(values.options[status.first]);
  }

  //check the values
  for (const std::pair<const int,bool>& status : values.optionStatus)
    if (!status.second) {
      this->optFields[status.first]->highlight();
      std::cout << '\a' << std::flush; //bleep
      return false;
    }

  return true;
}
//----------------------------------------------------------------------------

void FuiPreferences::setUIValues(const FFuaUIValues* values)
{
  FuaPreferencesValues* prefValues = (FuaPreferencesValues*) values;

  for (int iField = 0; iField < NFIELDS; iField++)
    this->optFields[iField]->setValue(prefValues->options[iField]);

  this->eqSolverToggle->setValue(prefValues->useEqSolverBuffer);
  this->eqSolverAutomatic->setValue(prefValues->autoEqSolverBuffer);
  this->eqSolverManual->setValue(!prefValues->autoEqSolverBuffer);

  this->recMatrixToggle->setValue(prefValues->useRecMatrixBuffer);
  this->recMatrixAutomatic->setValue(prefValues->autoRecMatrixBuffer);
  this->recMatrixManual->setValue(!prefValues->autoRecMatrixBuffer);

  this->solverPrefixToggle->setValue(prefValues->useSolverPrefix);
  this->solverPathToggle->setValue(prefValues->useSolverPath);
  this->onSolvePrefixToggeled(prefValues->useSolverPrefix);

  this->isRestartActive = prefValues->isRestarted;
  this->setSensitivity(prefValues->isSensitive);

  this->dialogButtons->setButtonSensitivity(FFuDialogButtons::LEFTBUTTON,prefValues->isTouchable);
}
//----------------------------------------------------------------------------

void FuiPreferences::setSensitivity(bool sens)
{
  // The reducer and solver additional options should be locked on results
  this->optFields[REDUCER]->setSensitivity(sens);
  this->optFields[SOLVER]->setSensitivity(sens || this->isRestartActive);
  this->eqSolverToggle->setSensitivity(sens);
  this->onEqSolverToggeled(sens && this->eqSolverToggle->getValue());
  this->recMatrixToggle->setSensitivity(sens);
  this->onRecMatrixToggeled(sens && this->recMatrixToggle->getValue());
  this->isSensitive = sens;
}
//----------------------------------------------------------------------------

void FuiPreferences::onEqSolverToggeled(bool isOn)
{
  this->eqSolverAutomatic->setSensitivity(isOn);
  this->eqSolverManual->setSensitivity(isOn);
  this->optFields[EQ_SOLVER_SWAP]->setSensitivity(isOn && this->eqSolverManual->getValue());
}
//----------------------------------------------------------------------------

void FuiPreferences::onEqSolverGroupToggeled(int button, bool isOn)
{
  if (button == 1)
    this->optFields[EQ_SOLVER_SWAP]->setSensitivity(isOn);
  else if (isOn)
    this->optFields[EQ_SOLVER_SWAP]->setSensitivity(false);
}
//----------------------------------------------------------------------------

void FuiPreferences::onRecMatrixToggeled(bool isOn)
{
  this->recMatrixAutomatic->setSensitivity(isOn);
  this->recMatrixManual->setSensitivity(isOn);
  this->optFields[REC_MATRIX_SWAP]->setSensitivity(isOn && this->recMatrixManual->getValue());
}
//----------------------------------------------------------------------------

void FuiPreferences::onRecMatrixGroupToggeled(int button, bool isOn)
{
  if (button == 1)
    this->optFields[REC_MATRIX_SWAP]->setSensitivity(isOn);
  else if (isOn)
    this->optFields[REC_MATRIX_SWAP]->setSensitivity(false);
}
//----------------------------------------------------------------------------

void FuiPreferences::onSolvePrefixToggeled(bool isOn)
{
  this->optFields[SOLVER_PREFIX]->setSensitivity(isOn);
  this->solverPathToggle->setSensitivity(isOn);
  this->optFields[SOLVER_PATH]->setSensitivity(isOn && this->solverPathToggle->getValue());
}
//----------------------------------------------------------------------------

void FuiPreferences::onSolvePathToggeled(bool isOn)
{
  this->optFields[SOLVER_PATH]->setSensitivity(isOn);
}
//----------------------------------------------------------------------------

void FuiPreferences::onRestartToggeled(bool isOn)
{
  this->isRestartActive = isOn;
  this->optFields[SOLVER]->setSensitivity(isSensitive || isRestartActive);
}
//----------------------------------------------------------------------------
