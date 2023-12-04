// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/vpmUIQtTopLevels/FuiQtAdvAnalysisOptions.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtDialogButtons.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtTabbedWidgetStack.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"


// Qt implementation of static create method in FuiAdvAnalysisOptions
FuiAdvAnalysisOptions* FuiAdvAnalysisOptions::create(int xpos, int ypos,
						     int width, int height, bool basicMode,
						     const char* title,
						     const char* name)
{
  return new FuiQtAdvAnalysisOptions(NULL,xpos,ypos,width,height,basicMode,title,name);
}


FuiQtAdvAnalysisOptions::FuiQtAdvAnalysisOptions(QWidget* parent,
						 int xpos, int ypos,
						 int width, int height,
						 bool basicMode,
						 const char* title,
						 const char* name)
  : FFuQtTopLevelShell(parent,xpos,ypos,width,height,title,name),
    FuiAdvAnalysisOptions(basicMode)
{
  // Widget creation
  FFuQtTabbedWidgetStack* myTabStack;
  this->tabStack = myTabStack = new FFuQtTabbedWidgetStack(this);
  this->dialogButtons = new FFuQtDialogButtons(this,false);
  this->btnRunCloud = new FFuQtPushButton(this);
  this->btnHelp = new FFuQtPushButton(this);

  // Set basic mode stuff
  this->labImgTop = new FFuQtLabel(this);
  this->labNotesImage = new FFuQtLabel(myTabStack);
  this->labNotesLabel = new FFuQtLabel(myTabStack);
  this->labNotesText = new FFuQtLabel(myTabStack);
  this->btnAdvanced = new FFuQtPushButton(this);

#ifdef FT_HAS_SOLVERS
  const int nOpt = NOPTIONS;
#else
  const int nOpt = OUTPUTOPTIONS;
#endif
  FuiQtAdvAnalysisOptionsSheet* myOptions[nOpt];
  for (int iOpt = 0; iOpt < nOpt; iOpt++)
    this->options[iOpt] = myOptions[iOpt] = new FuiQtAdvAnalysisOptionsSheet(this);

  // Time options
  this->labelFrames[TIMEOPTIONS][TIME_FRAME]    = new FFuQtLabelFrame(myOptions[TIMEOPTIONS]);
  this->labelFrames[TIMEOPTIONS][CUTBACK_FRAME] = new FFuQtLabelFrame(myOptions[TIMEOPTIONS]);
  this->labelFrames[TIMEOPTIONS][RESTART_FRAME] = new FFuQtLabelFrame(myOptions[TIMEOPTIONS]);

  this->doubleFields[TIMEOPTIONS][START]         = new FFuQtIOField(myOptions[TIMEOPTIONS]);
  this->doubleFields[TIMEOPTIONS][STOP]          = new FFuQtIOField(myOptions[TIMEOPTIONS]);
  this->myAdvTimeIncQueryField                   = new FuiQtQueryInputField(myOptions[TIMEOPTIONS]);
  this->doubleFields[TIMEOPTIONS][MIN_TIME_INCR] = new FFuQtIOField(myOptions[TIMEOPTIONS]);

  this->toggleButtons[TIMEOPTIONS][CUTBACK]       = new FFuQtToggleButton(myOptions[TIMEOPTIONS]);
  this->doubleFields[TIMEOPTIONS][CUTBACK_FACTOR] = new FFuQtIOField(myOptions[TIMEOPTIONS]);
  this->integerFields[TIMEOPTIONS][CUTBACK_STEPS] = new FFuQtIOField(myOptions[TIMEOPTIONS]);

  this->toggleButtons[TIMEOPTIONS][RESTART]     = new FFuQtToggleButton(myOptions[TIMEOPTIONS]);
  this->doubleFields[TIMEOPTIONS][RESTART_TIME] = new FFuQtIOField(myOptions[TIMEOPTIONS]);

  this->labels[TIMEOPTIONS][START]          = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][STOP]           = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][INCREMENT]      = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][MIN_TIME_INCR]  = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][CUTBACK_FACTOR] = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][CUTBACK_STEPS]  = new FFuQtLabel(myOptions[TIMEOPTIONS]);
  this->labels[TIMEOPTIONS][RESTART_TIME]   = new FFuQtLabel(myOptions[TIMEOPTIONS]);

  this->degradeSoilButton = new FFuQtPushButton(myOptions[TIMEOPTIONS]);

#ifndef FT_HAS_SOLVERS
  this->labelFrames[TIMEOPTIONS][ADDITIONAL_FRAME] = new FFuQtLabelFrame(myOptions[TIMEOPTIONS]);
  this->labelFrames[TIMEOPTIONS][ADDITIONAL_FRAME]->setLabel("Additional Solver Options");
#endif
  this->addOptions = new FFuQtIOField(myOptions[TIMEOPTIONS]);

  // Integration options
  this->labelFrames[INTOPTIONS][INT_ALG_FRAME]       = new FFuQtLabelFrame(myOptions[INTOPTIONS]);
  this->labelFrames[INTOPTIONS][ITERATION_FRAME]     = new FFuQtLabelFrame(myOptions[INTOPTIONS]);
  this->labelFrames[INTOPTIONS][MATRIX_UPDATE_FRAME] = new FFuQtLabelFrame(myOptions[INTOPTIONS]);

  this->radioButtons[INTOPTIONS][NEWMARK]                   = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][HHT_ALPHA]                 = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][GENERALIZED_ALPHA]         = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][RADIO_USE_TOL]             = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][RADIO_IGNORE_TOL]          = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][RADIO_FIXED_MATRIX_UPDATE] = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->radioButtons[INTOPTIONS][RADIO_VAR_MATRIX_UPDATE]   = new FFuQtRadioButton(myOptions[INTOPTIONS]);
  this->doubleFields[INTOPTIONS][HHT_ALPHA]                 = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->doubleFields[INTOPTIONS][GENERALIZED_ALPHA]         = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->doubleFields[INTOPTIONS][TOL_MATRIX_UPDATE]         = new FFuQtIOField(myOptions[INTOPTIONS]);

  this->toggleButtons[INTOPTIONS][DYN_STRESS_STIFF]  = new FFuQtToggleButton(myOptions[INTOPTIONS]);
  this->toggleButtons[INTOPTIONS][MOMENT_CORRECTION] = new FFuQtToggleButton(myOptions[INTOPTIONS]);

  this->integerFields[INTOPTIONS][NUM_ITERS]            = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->integerFields[INTOPTIONS][MAX_NUM_ITERS]        = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->integerFields[INTOPTIONS][MIN_NUM_ITERS]        = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->integerFields[INTOPTIONS][MIN_MATRIX_UPDATE]    = new FFuQtIOField(myOptions[INTOPTIONS]);
  this->integerFields[INTOPTIONS][MAX_NO_MATRIX_UPDATE] = new FFuQtIOField(myOptions[INTOPTIONS]);

  this->labels[INTOPTIONS][HHT_ALPHA]            = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][GENERALIZED_ALPHA]    = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][NUM_ITERS]            = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][MAX_NUM_ITERS]        = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][MIN_NUM_ITERS]        = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][MIN_MATRIX_UPDATE]    = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][MAX_NO_MATRIX_UPDATE] = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][TOL_MATRIX_UPDATE]    = new FFuQtLabel(myOptions[INTOPTIONS]);
  this->labels[INTOPTIONS][SHADOW_POS_ALG_LABEL] = new FFuQtLabel(myOptions[INTOPTIONS]);

  this->optionMenus[INTOPTIONS][SHADOW_POS_ALG]  = new FFuQtOptionMenu(myOptions[INTOPTIONS]);

  // Convergence options
  for (int i = 0; i < 3; i++) {
    this->radioButtons[CONVOPTIONS][SV_DIS_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][MT_DIS_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][MR_DIS_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][SV_VEL_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][SV_RES_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][MT_RES_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][MR_RES_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][AVG_EN_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->radioButtons[CONVOPTIONS][MAX_EN_1+i] = new FFuQtRadioButton(myOptions[CONVOPTIONS]);
    this->labels[CONVOPTIONS][AOI_DIS_1+i]      = new FFuQtLabel(myOptions[CONVOPTIONS]);
    this->labels[CONVOPTIONS][AOI_VEL_1+i]      = new FFuQtLabel(myOptions[CONVOPTIONS]);
    this->labels[CONVOPTIONS][AOI_RES_1+i]      = new FFuQtLabel(myOptions[CONVOPTIONS]);
    this->labels[CONVOPTIONS][AOI_EN_1+i]       = new FFuQtLabel(myOptions[CONVOPTIONS]);
  }

  this->doubleFields[CONVOPTIONS][SV_DIS] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][MT_DIS] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][MR_DIS] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][SV_VEL] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][SV_RES] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][MT_RES] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][MR_RES] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][AVG_EN] = new FFuQtIOField(myOptions[CONVOPTIONS]);
  this->doubleFields[CONVOPTIONS][MAX_EN] = new FFuQtIOField(myOptions[CONVOPTIONS]);

  this->labels[CONVOPTIONS][SV_DIS]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][MT_DIS]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][MR_DIS]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][SV_VEL]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][SV_RES]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][MT_RES]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][MR_RES]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][AVG_EN]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][MAX_EN]  = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][A_DESCR] = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][O_DESCR] = new FFuQtLabel(myOptions[CONVOPTIONS]);
  this->labels[CONVOPTIONS][I_DESCR] = new FFuQtLabel(myOptions[CONVOPTIONS]);

  this->labelFrames[CONVOPTIONS][DIS_FRAME]    = new FFuQtLabelFrame(myOptions[CONVOPTIONS]);
  this->labelFrames[CONVOPTIONS][VEL_FRAME]    = new FFuQtLabelFrame(myOptions[CONVOPTIONS]);
  this->labelFrames[CONVOPTIONS][RES_FRAME]    = new FFuQtLabelFrame(myOptions[CONVOPTIONS]);
  this->labelFrames[CONVOPTIONS][ENERGY_FRAME] = new FFuQtLabelFrame(myOptions[CONVOPTIONS]);

  // Eigen options
  this->toggleButtons[EIGENOPTIONS][EMODE_SOL]          = new FFuQtToggleButton(myOptions[EIGENOPTIONS]);
  this->toggleButtons[EIGENOPTIONS][EMODE_DAMPED]       = new FFuQtToggleButton(myOptions[EIGENOPTIONS]);
  this->toggleButtons[EIGENOPTIONS][EMODE_BC]           = new FFuQtToggleButton(myOptions[EIGENOPTIONS]);
  this->toggleButtons[EIGENOPTIONS][EMODE_STRESS_STIFF] = new FFuQtToggleButton(myOptions[EIGENOPTIONS]);

  this->doubleFields[EIGENOPTIONS][EMODE_INTV]       = new FFuQtIOField(myOptions[EIGENOPTIONS]);
  this->doubleFields[EIGENOPTIONS][EMODE_SHIFT_FACT] = new FFuQtIOField(myOptions[EIGENOPTIONS]);

  this->integerFields[EIGENOPTIONS][NUM_EMODES] = new FFuQtIOField(myOptions[EIGENOPTIONS]);

  this->labels[EIGENOPTIONS][EMODE_INTV]       = new FFuQtLabel(myOptions[EIGENOPTIONS]);
  this->labels[EIGENOPTIONS][NUM_EMODES]       = new FFuQtLabel(myOptions[EIGENOPTIONS]);
  this->labels[EIGENOPTIONS][EMODE_SHIFT_FACT] = new FFuQtLabel(myOptions[EIGENOPTIONS]);

  // Equilibrium options
  this->toggleButtons[EQOPTIONS][EQL_ITER]         = new FFuQtToggleButton(myOptions[EQOPTIONS]);
  this->toggleButtons[EQOPTIONS][EQL_STRESS_STIFF] = new FFuQtToggleButton(myOptions[EQOPTIONS]);
  this->doubleFields[EQOPTIONS][EQL_ITER_TOL]      = new FFuQtIOField(myOptions[EQOPTIONS]);
  this->doubleFields[EQOPTIONS][ITER_STEP_SIZE]    = new FFuQtIOField(myOptions[EQOPTIONS]);

  this->labels[EQOPTIONS][EQL_ITER_TOL]   = new FFuQtLabel(myOptions[EQOPTIONS]);
  this->labels[EQOPTIONS][ITER_STEP_SIZE] = new FFuQtLabel(myOptions[EQOPTIONS]);
  this->labels[EQOPTIONS][INFO_FIELD]     = new FFuQtLabel(myOptions[EQOPTIONS]);

  this->toggleButtons[EQOPTIONS][RAMP_UP]    = new FFuQtToggleButton(myOptions[EQOPTIONS]);
  this->toggleButtons[EQOPTIONS][RAMP_GRAV]  = new FFuQtToggleButton(myOptions[EQOPTIONS]);
  this->integerFields[EQOPTIONS][RAMP_STEPS] = new FFuQtIOField(myOptions[EQOPTIONS]);
  this->doubleFields[EQOPTIONS][RAMP_VMAX]   = new FFuQtIOField(myOptions[EQOPTIONS]);
  this->doubleFields[EQOPTIONS][RAMP_LENGTH] = new FFuQtIOField(myOptions[EQOPTIONS]);
  this->doubleFields[EQOPTIONS][RAMP_DELAY]  = new FFuQtIOField(myOptions[EQOPTIONS]);

  this->labels[EQOPTIONS][RAMP_STEPS]  = new FFuQtLabel(myOptions[EQOPTIONS]);
  this->labels[EQOPTIONS][RAMP_VMAX]   = new FFuQtLabel(myOptions[EQOPTIONS]);
  this->labels[EQOPTIONS][RAMP_LENGTH] = new FFuQtLabel(myOptions[EQOPTIONS]);
  this->labels[EQOPTIONS][RAMP_DELAY]  = new FFuQtLabel(myOptions[EQOPTIONS]);

  // Output options
#ifdef FT_HAS_SOLVERS
  this->labels[OUTPUTOPTIONS][AUTO_CURVE_EXPORT]        = new FFuQtLabel(myOptions[OUTPUTOPTIONS]);
  this->toggleButtons[OUTPUTOPTIONS][AUTO_CURVE_EXPORT] = new FFuQtToggleButton(myOptions[OUTPUTOPTIONS]);
  this->toggleButtons[OUTPUTOPTIONS][AUTO_VTF_EXPORT]   = new FFuQtToggleButton(myOptions[OUTPUTOPTIONS]);
  this->toggleButtons[OUTPUTOPTIONS][AUTO_ANIM]         = new FFuQtToggleButton(myOptions[OUTPUTOPTIONS]);
  this->toggleButtons[OUTPUTOPTIONS][OVERWRITE]         = new FFuQtToggleButton(myOptions[OUTPUTOPTIONS]);
  this->autoCurveExportField = new FFuQtFileBrowseField(myOptions[OUTPUTOPTIONS]);
  this->autoVTFField         = new FFuQtFileBrowseField(myOptions[OUTPUTOPTIONS]);
#endif

  // Basic options
  this->labelFrames[BASICOPTIONS][IEQ_FRAME]      = new FFuQtLabelFrame(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][IEQ_TOGGLE]   = new FFuQtToggleButton(myOptions[BASICOPTIONS]);

  this->labelFrames[BASICOPTIONS][TIME_FRAME]     = new FFuQtLabelFrame(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][TIME_TOGGLE]  = new FFuQtToggleButton(myOptions[BASICOPTIONS]);
  this->doubleFields[BASICOPTIONS][START]         = new FFuQtIOField(myOptions[BASICOPTIONS]);
  this->doubleFields[BASICOPTIONS][STOP]          = new FFuQtIOField(myOptions[BASICOPTIONS]);
  this->myBasTimeIncQueryField                    = new FuiQtQueryInputField(myOptions[BASICOPTIONS]);
  this->labels[BASICOPTIONS][START]               = new FFuQtLabel(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][STOP]         = new FFuQtToggleButton(myOptions[BASICOPTIONS]);
  this->labels[BASICOPTIONS][INCREMENT]           = new FFuQtLabel(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][QS_TOGGLE]    = new FFuQtToggleButton(myOptions[BASICOPTIONS]);
  this->radioButtons[BASICOPTIONS][QS_COMPLETE]   = new FFuQtRadioButton(myOptions[BASICOPTIONS]);
  this->radioButtons[BASICOPTIONS][QS_UPTOTIME]   = new FFuQtRadioButton(myOptions[BASICOPTIONS]);
  this->doubleFields[BASICOPTIONS][QS_UPTOTIME]   = new FFuQtIOField(myOptions[BASICOPTIONS]);

  this->labelFrames[BASICOPTIONS][MODES_FRAME]    = new FFuQtLabelFrame(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][MODES_TOGGLE] = new FFuQtToggleButton(myOptions[BASICOPTIONS]);
  this->integerFields[BASICOPTIONS][MODES_COUNT]  = new FFuQtIOField(myOptions[BASICOPTIONS]);
  this->labels[BASICOPTIONS][MODES_COUNT]         = new FFuQtLabel(myOptions[BASICOPTIONS]);

#ifdef FT_HAS_FREQDOMAIN
  this->labelFrames[BASICOPTIONS][FRA_FRAME]      = new FFuQtLabelFrame(myOptions[BASICOPTIONS]);
  this->toggleButtons[BASICOPTIONS][FRA_TOGGLE]   = new FFuQtToggleButton(myOptions[BASICOPTIONS]);
#endif

  this->initWidgets();

  myTabStack->setTabBarVisible(!this->myBasicMode);
  myTabStack->setDocumentMode(this->myBasicMode);
}


void FuiQtAdvAnalysisOptions::onAdvBtnClicked()
{
  // Hide/show tab-line
  FFuQtTabbedWidgetStack* myTabStack = static_cast<FFuQtTabbedWidgetStack*>(this->tabStack);
  myTabStack->setTabBarVisible(this->myBasicMode);
  myTabStack->setDocumentMode(!this->myBasicMode);

  this->FuiAdvAnalysisOptions::onAdvBtnClicked();
}
