// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiModelPreferences.H"
#include "vpmUI/vpmUITopLevels/FuiSeaEnvironment.H"
#include "vpmUI/vpmUIComponents/Fui3DPoint.H"
#include "vpmUI/Fui.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuMemo.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuFileBrowseField.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuFrame.H"
#include "vpmApp/FapLicenseManager.H"


enum {
  SAVE  = FFuDialogButtons::LEFTBUTTON,
  CLOSE = FFuDialogButtons::MIDBUTTON,
  HELP  = FFuDialogButtons::RIGHTBUTTON
};

Fmd_SOURCE_INIT(FUI_MODELPREFERENCES,FuiModelPreferences,FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiModelPreferences::FuiModelPreferences()
{
  Fmd_CONSTRUCTOR_INIT(FuiModelPreferences);

  this->IAmInternalRepository = false;;
}
//----------------------------------------------------------------------------

void FuiModelPreferences::setSensitivity(bool isSensitive)
{
  this->changeButton->setSensitivity(isSensitive);
  this->switchButton->setSensitivity(isSensitive);
  this->extFuncFileButton->setSensitivity(isSensitive);
  this->extFuncFileField->setSensitivity(isSensitive && this->extFuncFileButton->getValue());

  this->dialogButtons->setButtonSensitivity(SAVE,isSensitive);
}
//----------------------------------------------------------------------------

void FuiModelPreferences::setUpdateDescriptionCB(const FFaDynCB1<const std::string&>& dynCB)
{
  this->updateDescriptionCB = dynCB;
}
//----------------------------------------------------------------------------

void FuiModelPreferences::setChangeRepositoryCB(const FFaDynCB1<bool>& dynCB)
{
  this->changeRepositoryCB = dynCB;
}
//----------------------------------------------------------------------------

void FuiModelPreferences::initWidgets()
{
  this->dialogButtons->setButtonClickedCB(FFaDynCB1M(FuiModelPreferences,this,
						     onDialogButtonClicked,int));
  this->changeButton->setActivateCB(FFaDynCB0M(FuiModelPreferences,this,
					       onChangeButtonPushed));
  this->switchButton->setActivateCB(FFaDynCB0M(FuiModelPreferences,this,
					       onSwitchButtonPushed));
  this->extFuncFileButton->setToggleCB(FFaDynCB1M(FFuComponentBase,extFuncFileField,
						  setSensitivity,bool));

  this->dialogButtons->setButtonLabel(SAVE,"Save");
  this->dialogButtons->setButtonLabel(CLOSE,"Close");
  this->dialogButtons->setButtonLabel(HELP,"Help");

  this->descriptionFrame->setLabel("Model description");
  this->descriptionMemo->setEditable(true);
  this->descriptionMemo->setToolTip("Enter any text describing the model in this field.\n"
				    "Note: Changes in this field are saved also when the dialog is Canceled or Closed");

  this->repositoryFrame->setLabel("FE model repository");
  this->repositoryField->setSensitivity(false);
  this->changeButton->setLabel("Change...");
  this->changeButton->setToolTip("Select or create a new external FE model repository");
  this->overwriteButton->setLabel("Overwrite existing reduced FE data");
  this->overwriteButton->setToolTip("If enabled, a new reduction of an FE part will overwrite\n"
                                    "the current existing and invalid data, instead of creating a\n"
                                    "new directory. Use this to save disk space for larger FE parts.");

  this->unitsFrame->setLabel("Units");
  this->unitsLabel->setLabel("Model database units");

  this->modelingTolFrame->setLabel("Modeling tolerance");
  this->modelingTolLabel->setLabel("Absolute modeling tolerance");

  this->modelingTolField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->modelingTolField->setDoubleDisplayMode(FFuIOField::AUTO);
  this->modelingTolField->setDoubleDisplayPrecision(3);
  this->modelingTolField->setZeroDisplayPrecision(1);

  this->gravitationFrame->setLabel("Gravitation");
  this->gravitationVector->setLook(FFuFrame::FLAT);

  this->initialVelFrame->setLabel("Initial translational velocity");
  this->initialVelVector->setLook(FFuFrame::FLAT);

  this->extFuncFileFrame->setLabel("File for external function evaluation");
  this->extFuncFileButton->setLabel("Use external function file");
  this->extFuncFileField->setAbsToRelPath("yes");
  this->extFuncFileField->setDialogType(FFuFileDialog::FFU_OPEN_FILE);
  std::vector<std::string> ascii({"asc","txt"});
  this->extFuncFileField->addDialogFilter("ASCII curve data file",ascii,true);
  this->extFuncFileField->addDialogFilter("Comma-separated values file","csv");
  this->extFuncFileField->addAllFilesFilter(true);
  this->extFuncFileField->setDialogRememberKeyword("ExternalFuncFileField");

  this->placeWidgets(this->getWidth(),this->getHeight());

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiModelPreferences::placeWidgets(int width, int height)
{
  bool showLinkRepFrame = FapLicenseManager::isProEdition();

  int border = this->getBorder();
  int buttonsTop = height - this->dialogButtons->getHeightHint();

  int fontHeight = this->getFontHeigth();
  int fieldHeight = this->unitsMenu->getHeightHint();
  int vectorHeight = fontHeight + 13*fieldHeight/4 + 3*border/2;

  int v1 = border;
  int v2 = v1 + border;
  int v3 = v2 + this->modelingTolLabel->getWidthHint() + border;

  int v6 = width - border;
  int v5 = v6 - border;

  int v7 = (width - border)/2;
  int v8 = v7 + border;

  int h0 = 7*border/2 + fontHeight + fieldHeight;
  int h1 = buttonsTop - 17*border/2 - 3*fontHeight - 4*fieldHeight - vectorHeight;
  if (showLinkRepFrame) h1 -= 9*border/2 + fontHeight + 3*fieldHeight;
  if (h1 < h0) h1 = h0;

  int h2 = h1 + border/2 + fontHeight;
  int h3 = h2 + fieldHeight;
  int h4 = h3 + border;

  int h5 = h4 + border;
  int h6 = h5 + border/2 + fontHeight;
  int h7 = h6 + fieldHeight;
  int h8 = h7 + border;

  int h9  = h8  + border;
  int h10 = h9  + vectorHeight;
  int h11 = h9  + border/2 + fontHeight;
  int h12 = h10 - border;

  int h13 = h10 + border;
  int h14 = h13 + border/2 + fontHeight;
  int h15 = h14 + fieldHeight;
  int h16 = h15 + border;
  int h17 = h16 + fieldHeight;
  int h18 = h17 + border;
  int h19 = h18 + fieldHeight;
  int h20 = h19 + border;

  int h01 = border;
  int h02 = h01 + border/2 + fontHeight;
  int h04 = h1  - border;
  int h03 = h04 - border;

  this->descriptionFrame->setEdgeGeometry(v1, v6, h01, h04);
  this->descriptionMemo ->setEdgeGeometry(v2, v5, h02, h03);

  this->unitsFrame->setEdgeGeometry(v1, v6, h1, h4);
  this->unitsLabel->setEdgeGeometry(v2, v3, h2, h3);
  this->unitsMenu ->setEdgeGeometry(v3, v5, h2, h3);

  this->modelingTolFrame->setEdgeGeometry(v1, v6, h5, h8);
  this->modelingTolLabel->setEdgeGeometry(v2, v3, h6, h7);
  this->modelingTolField->setEdgeGeometry(v3, v5, h6, h7);

  this->gravitationFrame ->setEdgeGeometry(v1, v7, h9, h10);
  this->gravitationVector->setEdgeGeometry(v1+2, v7-2, h11, h12);

  this->initialVelFrame ->setEdgeGeometry(v8, v6, h9, h10);
  this->initialVelVector->setEdgeGeometry(v8+2, v6-2, h11, h12);

  if (showLinkRepFrame) {
    int v4 = v5 - this->changeButton->getWidthHint();
    this->repositoryFrame->setEdgeGeometry(v1, v6, h13, h20);
    this->repositoryField->setEdgeGeometry(v2, v4-border, h14, h15);
    this->changeButton->setEdgeGeometry(v4, v5, h14, h15);
    this->switchButton->setEdgeGeometry(v2, v5, h16, h17);
    this->overwriteButton->setEdgeGeometry(v2, v5, h18, h19);
    this->repositoryFrame->popUp();
    this->repositoryField->popUp();
    this->changeButton->popUp();
    this->switchButton->popUp();
    this->overwriteButton->popUp();
  }
  else {
    h20 = h10;
    this->repositoryFrame->popDown();
    this->repositoryField->popDown();
    this->changeButton->popDown();
    this->switchButton->popDown();
    this->overwriteButton->popDown();
  }

  int h30 = h20 + border;
  int h31 = h30 + border/2 + fontHeight;
  int h32 = h31 + fieldHeight;
  int h33 = h32 + border;
  int h34 = h33 + fieldHeight;
  int h35 = h34 + border;
  this->extFuncFileFrame->setEdgeGeometry(v1, v6, h30, h35);
  this->extFuncFileButton->setEdgeGeometry(v2, v5, h31, h32);
  this->extFuncFileField->setEdgeGeometry(v2, v5, h33, h34);

  this->dialogButtons->setEdgeGeometry(0,width,buttonsTop,height);
}
//-----------------------------------------------------------------------------

void FuiModelPreferences::onPoppedUp()
{
  this->placeWidgets(this->getWidth(),this->getHeight());
  this->updateUIValues();
}
//----------------------------------------------------------------------------

bool FuiModelPreferences::onClose()
{
  this->invokeFinishedCB();
  this->updateDescriptionOnly();
  return false;
}
//----------------------------------------------------------------------------

void FuiModelPreferences::onDialogButtonClicked(int button)
{
  switch (button)
  {
    case SAVE:
      this->updateDBValues();
      break;

    case CLOSE:
      this->updateDescriptionOnly();
      this->invokeFinishedCB();
      return;

    case HELP:
      // Display the topic in the help file
      Fui::showCHM("dialogbox/model-preferences.htm");
      return;
  }

  // Also update the sea environment UI,
  // since the Gravitation vector are in both UI's
  FFuTopLevelShell* env = FFuTopLevelShell::getInstanceByType(FuiSeaEnvironment::getClassTypeID());
  if (env) dynamic_cast<FuiSeaEnvironment*>(env)->updateUIValues();
}
//----------------------------------------------------------------------------

void FuiModelPreferences::onChangeButtonPushed()
{
  this->changeRepositoryCB.invoke(false);
  this->updateUIValues();
}
//----------------------------------------------------------------------------

void FuiModelPreferences::onSwitchButtonPushed()
{
  this->changeRepositoryCB.invoke(!this->IAmInternalRepository);
  this->updateUIValues();
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiModelPreferences::createValuesObject()
{
  return new FuaModelPreferencesValues();
}
//----------------------------------------------------------------------------

void FuiModelPreferences::setUIValues(const FFuaUIValues* values)
{
  FuaModelPreferencesValues* prefValues = (FuaModelPreferencesValues*) values;

  this->descriptionMemo->setAllText(prefValues->description.c_str());
  this->modelingTolField->setValue(prefValues->modelingTol);
  this->unitsMenu->setOptions(prefValues->units);
  this->unitsMenu->selectOption(prefValues->selectedUnits,false);

  this->gravitationVector->setValue(prefValues->gravitation);
  this->initialVelVector->setValue(prefValues->velocity);
  this->overwriteButton->setValue(prefValues->overwriteFE);

  this->setSensitivity(prefValues->isSensitive);

  if (prefValues->useFuncFile >= 0) {
    this->extFuncFileButton->setValue(prefValues->useFuncFile);
    this->extFuncFileField->setAbsToRelPath(prefValues->modelFilePath);
    this->extFuncFileField->setFileName(prefValues->extFuncFileName);
    this->extFuncFileField->setSensitivity(true);
  }
  else {
    this->extFuncFileButton->setSensitivity(false);
    this->extFuncFileField->setSensitivity(false);
  }

  this->IAmInternalRepository = prefValues->repository.empty();
  if (this->IAmInternalRepository) {
    this->repositoryField->setValue("(internal)");
    this->changeButton->setSensitivity(false);
    this->switchButton->setLabel("Switch to external repository...");
    this->switchButton->setToolTip("Select or create an external FE model repository\n"
				   "that is independent of the current model");
  }
  else {
    this->repositoryField->setValue(prefValues->repository);
    this->switchButton->setLabel("Switch to internal repository...");
    this->switchButton->setToolTip("Use an internal FE model repository\n"
				   "that is specific for current model");
  }
}
//-----------------------------------------------------------------------------

void FuiModelPreferences::getUIValues(FFuaUIValues* values)
{
  FuaModelPreferencesValues* prefValues = (FuaModelPreferencesValues*) values;

  prefValues->description = this->descriptionMemo->getText();
  prefValues->repository = this->repositoryField->getValue();
  if (prefValues->repository == "(internal)") prefValues->repository = "";
  prefValues->modelingTol = this->modelingTolField->getDouble();
  prefValues->selectedUnits = this->unitsMenu->getSelectedOptionStr();
  prefValues->gravitation = this->gravitationVector->getValue();
  prefValues->velocity = this->initialVelVector->getValue();
  prefValues->overwriteFE = this->overwriteButton->getValue();
  if (this->extFuncFileButton->getSensitivity()) {
    prefValues->useFuncFile = this->extFuncFileButton->getValue();
    prefValues->extFuncFileName = this->extFuncFileField->getFileName();
  }
  else
    prefValues->useFuncFile = -1;
}
//-----------------------------------------------------------------------------

void FuiModelPreferences::updateDescriptionOnly()
{
  this->updateDescriptionCB.invoke(this->descriptionMemo->getText());
}
