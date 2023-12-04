// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtScale.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtTable.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtFileBrowseField.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtRadioButton.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtPositionData.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQt3DPoint.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtLinkTabs.H"


FuiQtLinkModelSheet::FuiQtLinkModelSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->suppressInSolverLabel = new FFuQtLabel(this);
  this->suppressInSolverToggle = new FFuQtToggleButton(this);

  this->feModelFrame = new FFuQtLabelFrame(this);
  this->structDampFrame = new FFuQtLabelFrame(this);
  this->dynPropFrame = new FFuQtLabelFrame(this);

  this->feModelBtn = new FFuQtRadioButton(this);
  this->genPartBtn = new FFuQtRadioButton(this);

  this->repositoryFileField = new FFuQtLabelField(this);
  this->changeLinkBtn = new FFuQtPushButton(this);
  this->importedFileField = new FFuQtLabelField(this);
  this->unitConversionLabel = new FFuQtLabel(this);
  this->needsReductionFrame = new FFuQtFrame(this);

  this->vizFrame = new FFuQtLabelFrame(this);
  this->vizField = new FFuQtLabelField(this);
  this->vizChangeBtn = new FFuQtPushButton(this);
  this->vizLabel = new FFuQtLabel(this);

  FFuQtLabel* lab;
  this->needsReductionLabel = lab = new FFuQtLabel(this);
  lab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  this->massProportionalField = new FFuQtLabelField(this);
  this->stiffProportionalField = new FFuQtLabelField(this);

  this->stiffScaleField = new FFuQtLabelField(this);
  this->massScaleField = new FFuQtLabelField(this);

  this->initWidgets();
}


FuiQtLinkOriginSheet::FuiQtLinkOriginSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->posData = new FuiQtPositionData(this);
}


FuiQtLinkNodeSheet::FuiQtLinkNodeSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->myFENodeField = new FFuQtLabelField(this);
  this->myNodePosition = new FuiQt3DPoint(this);

  this->initWidgets();
}


FuiQtLinkRedOptSheet::FuiQtLinkRedOptSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->eigValFactFrame = new FFuQtLabelFrame(this);
  this->recoveryMatrixPrecisionFrame = new FFuQtLabelFrame(this);

  this->singCriterionField = new FFuQtLabelField(this);
  this->componentModesField = new FFuQtLabelField(this);
  this->eigValToleranceField = new FFuQtLabelField(this);

  this->consistentMassBtn = new FFuQtToggleButton(this);
  this->ignoreCSBtn = new FFuQtToggleButton(this);
  this->expandMSBtn = new FFuQtToggleButton(this);

  this->massFactBtn = new FFuQtRadioButton(this);
  this->stiffFactBtn = new FFuQtRadioButton(this);

  this->singlePrecisionBtn = new FFuQtRadioButton(this);
  this->doublePrecisionBtn = new FFuQtRadioButton(this);

  this->needsReductionFrame = new FFuQtFrame(this);
  FFuQtLabel* lab;
  this->needsReductionLabel = lab = new FFuQtLabel(this);
  lab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  this->initWidgets();
}


FuiQtLinkLoadSheet::FuiQtLinkLoadSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->label = new FFuQtLabel(this);
  this->table = new FFuQtTable(this);

  this->initWidgets();
}

void FuiQtLinkLoadSheet::setNoLoadCases(unsigned int nlc)
{
  QWidget* qPtr = dynamic_cast<QWidget*>(this->table);

  unsigned int olc = this->loadFact.size();
  this->loadFact.resize(nlc,NULL);
  this->delay.resize(nlc,NULL);

  for (unsigned int i = olc; i < nlc; i++) {
    this->delay[i] = new FFuQtIOField(qPtr);
    this->loadFact[i] = new FuiQtQueryInputField(qPtr);
    this->loadFact[i]->setBehaviour(FuiQueryInputField::REF_NUMBER);
  }
}


FuiQtGenericPartCGSheet::FuiQtGenericPartCGSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->posData = new FuiQtPositionData(this);
  this->condenseCGToggle = new FFuQtToggleButton(this);

  this->initWidgets();
}


FuiQtGenericPartMassSheet::FuiQtGenericPartMassSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->massField = new FFuQtLabelField(this);
  this->inertiaRefLabel = new FFuQtLabel(this);
  this->massInertiaFrame = new FFuQtLabelFrame(this);
  this->inertiaRefMenu = new FFuQtOptionMenu(this);
  this->calculateMassPropExplicitBtn = new FFuQtRadioButton(this);
  this->calculateMassPropFEBtn = new FFuQtRadioButton(this);
  this->calculateMassPropGeoBtn = new FFuQtRadioButton(this);
  this->materialLabel = new FFuQtLabel(this);
  this->materialField = new FuiQtQueryInputField(this);

  for (FFuIOField*& field : this->inertias)
    field = new FFuQtIOField(this);

  for (FFuLabel*& label : this->inertiaLabels)
    label = new FFuQtLabel(this);

  this->initWidgets();
}


FuiQtGenericPartStiffSheet::FuiQtGenericPartStiffSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->stiffTypeFrame = new FFuQtLabelFrame(this);
  this->stiffPropFrame = new FFuQtLabelFrame(this);

  this->defaultStiffTypeBtn = new FFuQtRadioButton(this);
  this->nodeStiffTypeBtn    = new FFuQtRadioButton(this);

  this->ktField = new FFuQtLabelField(this);
  this->krField = new FFuQtLabelField(this);

  this->stiffDescrLabel = new FFuQtLabel(this);

  this->initWidgets();
}


FuiQtHydrodynamicsSheet::FuiQtHydrodynamicsSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->buoyancyToggle = new FFuQtToggleButton(this);
  this->buoyancyLabel = new FFuQtLabel(this);

  this->initWidgets();
}


FuiQtMeshingSheet::FuiQtMeshingSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->materialLabel = new FFuQtLabel(this);
  this->materialField = new FuiQtQueryInputField(this);
  this->minsizeField = new FFuQtLabelField(this);

  this->linearBtn = new FFuQtRadioButton(this);
  this->parabolicBtn = new FFuQtRadioButton(this);

  FFuQtScale* qtScale;
  this->qualityScale = qtScale = new FFuQtScale(this);
  qtScale->setOrientation(Qt::Horizontal);

  for (FFuLabel*& label : this->qualityLabel)
    label = new FFuQtLabel(this);

  this->meshBtn = new FFuQtPushButton(this);

  this->noElmsLabel = new FFuQtLabel(this);
  this->noNodesLabel = new FFuQtLabel(this);

  this->initWidgets();
}


FuiQtAdvancedLinkOptsSheet::FuiQtAdvancedLinkOptsSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->coordSysLabel = new FFuQtLabel(this);
  this->coordSysOptionMenu = new FFuQtOptionMenu(this);

  this->centripLabel = new FFuQtLabel(this);
  this->centripOptionMenu = new FFuQtOptionMenu(this);

  this->recoverStressToggle = new FFuQtToggleButton(this);
  this->recoverGageToggle = new FFuQtToggleButton(this);

  this->extResToggle = new FFuQtToggleButton(this);
  this->extResField = new FFuQtFileBrowseField(this);

  this->initWidgets();
}


FuiQtNonlinearLinkOptsSheet::FuiQtNonlinearLinkOptsSheet(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->nonlinearDescrLabel = new FFuQtLabel(this);
  this->useNonlinearToggle = new FFuQtToggleButton(this);
  this->numberOfSolutionsField = new FFuQtLabelField(this);
  this->nonlinearInputFileField = new FFuQtFileBrowseField(this);

  this->initWidgets();
}
