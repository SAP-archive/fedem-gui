// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiStressOptions.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuFileBrowseField.H"
#include "FFuLib/FFuFileDialog.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


Fmd_SOURCE_INIT(FUI_STRESSOPTIONS, FuiStressOptions, FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiStressOptions::FuiStressOptions()
{
  Fmd_CONSTRUCTOR_INIT(FuiStressOptions);

  showVTFfield = false;
}
//----------------------------------------------------------------------------

void FuiStressOptions::initWidgets()
{
  this->time->setResetCB(FFaDynCB0M(FuiStressOptions,this,onResetTimeClicked));

  this->outputFrame->setLabel("Output Options");
  this->deformationToggle->setLabel("deformation");
  this->stressResToggle->setLabel("stress resultant tensor");
  this->stressToggle[0]->setLabel("stress tensor");
  this->stressToggle[1]->setLabel("von Mises stress");
  this->stressToggle[2]->setLabel("max principal stress");
  this->stressToggle[3]->setLabel("min principal stress");
  this->stressToggle[4]->setLabel("max shear stress");
  this->strainToggle[0]->setLabel("strain tensor");
  this->strainToggle[1]->setLabel("von Mises strain");
  this->strainToggle[2]->setLabel("max principal strain");
  this->strainToggle[3]->setLabel("min principal strain");
  this->strainToggle[4]->setLabel("max shear strain");

  this->autoVTFToggle->setLabel("Automatic export to GLview VTF file");
  this->autoVTFToggle->setToggleCB(FFaDynCB1M(FuiStressOptions,this,
					      onAutoVTFToggled,bool));
  this->autoVTFField->setLabel("Express File");
  this->autoVTFField->setAbsToRelPath("yes");
  this->autoVTFField->setDialogType(FFuFileDialog::FFU_SAVE_FILE);
  this->autoVTFField->setDialogRememberKeyword("AutoVTFField");

  this->autoVTFField->addDialogFilter("Express VTF file","vtf",true,0);
  this->autoVTFField->addDialogFilter("Binary VTF file","vtf",false,1);
  this->autoVTFField->addDialogFilter("ASCII VTF file","vtf",false,2);
  this->autoVTFField->setFileOpenedCB(FFaDynCB2M(FuiStressOptions,this,
						 onAutoVTFFileChanged,
						 const std::string&,int));

  this->fringeLabel->setLabel("Contour range for Express VTF file (von Mises stress only)");
  this->minFringeField->setLabel("Min");
  this->maxFringeField->setLabel("Max");

  this->FuiTopLevelDialog::initWidgets();
}
//----------------------------------------------------------------------------

void FuiStressOptions::placeWidgets(int width, int height)
{
  int border = this->getBorder();
  int timet = border;
  int timeb = 34*height/100;
  this->time->setEdgeGeometry(border,width-border,timet,timeb);

  int sep = this->time->getSepH();
  int widgeth = this->time->getWidgetH();

  int frameFonth = this->outputFrame->getFontHeigth();

  int incr = sep+widgeth;
  int outputframet = timeb+sep;
  int ypos = outputframet + frameFonth+incr/2;
  int outputframeb = ypos + 5*incr+widgeth/2+sep;

  this->outputFrame->setEdgeGeometry(border,width-border,outputframet,outputframeb);
  this->deformationToggle->setCenterYGeometryWidthHint(2*border,ypos,widgeth);
  this->stressResToggle->setCenterYGeometryWidthHint(width/2,ypos,widgeth);
  ypos += incr;
  for (int i = 0; i < 5; i++, ypos += incr) {
    this->strainToggle[i]->setCenterYGeometryWidthHint(2*border,ypos,widgeth);
    this->stressToggle[i]->setCenterYGeometryWidthHint(width/2,ypos,widgeth);
  }

  ypos += sep;
  this->autoVTFToggle->setCenterYGeometryWidthHint(border,ypos,widgeth);
  ypos += incr/2;
  this->autoVTFField->setEdgeGeometry(border,width-border,ypos,ypos+widgeth);
  ypos += incr+sep;

  this->fringeLabel->setEdgeGeometry(border,width-border,ypos,ypos+frameFonth);
  ypos += frameFonth+sep;
  this->minFringeField->setEdgeGeometry(border,width/2-sep,ypos,ypos+widgeth);
  this->maxFringeField->setEdgeGeometry(width/2+sep,width-border,ypos,ypos+widgeth);

  if (showVTFfield) {
    this->autoVTFToggle->popUp();
    this->autoVTFField->popUp();
    this->fringeLabel->popUp();
    this->minFringeField->popUp();
    this->maxFringeField->popUp();
  }
  else {
    this->autoVTFToggle->popDown();
    this->autoVTFField->popDown();
    this->fringeLabel->popDown();
    this->minFringeField->popDown();
    this->maxFringeField->popDown();
  }

  this->FuiTopLevelDialog::placeWidgets(width,height);
}
//-----------------------------------------------------------------------------

void FuiStressOptions::setTimeUIValues(const FuaTimeIntervalValues* timeValues)
{
  this->time->setUIValues(timeValues);
}
//-----------------------------------------------------------------------------

void FuiStressOptions::setResetTimeCB(const FFaDynCB0& dynCB)
{
  this->resetTimeCB = dynCB;
}
//-----------------------------------------------------------------------------

void FuiStressOptions::onResetTimeClicked()
{
  this->resetTimeCB.invoke();
}
//-----------------------------------------------------------------------------

void FuiStressOptions::setVTFLabel(int id)
{
  const char* vtf_label[3] = { "Express File",
			       " Binary File",
			       "  ASCII File" };

  if (id >= 0 && id < 3)
    this->autoVTFField->setLabel(vtf_label[id]);
  else
    this->autoVTFField->setLabel("File");

  bool fringeSens = id == 0 && this->autoVTFToggle->getValue();
  this->minFringeField->setSensitivity(fringeSens);
  this->maxFringeField->setSensitivity(fringeSens);
}
//-----------------------------------------------------------------------------

void FuiStressOptions::onAutoVTFFileChanged(const std::string&, int id)
{
  this->setVTFLabel(id);
}
//----------------------------------------------------------------------------

void FuiStressOptions::onAutoVTFToggled(bool value)
{
  this->autoVTFField->setSensitivity(value);
  bool isExpressFile = this->autoVTFField->getFilterID() == 0;
  this->minFringeField->setSensitivity(value && isExpressFile);
  this->maxFringeField->setSensitivity(value && isExpressFile);
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiStressOptions::createValuesObject()
{
  return new FuaStressOptionsValues();
}
//----------------------------------------------------------------------------

void FuiStressOptions::setUIValues(const FFuaUIValues* values)
{
  FuaStressOptionsValues* stressValues = (FuaStressOptionsValues*) values;

  this->time->setUIValues(&stressValues->timeValues);
  this->deformationToggle->setValue(stressValues->deformationOutput);
  this->stressResToggle->setValue(stressValues->stressResOutput);
  for (int i = 0; i < 5; i++) {
    this->strainToggle[i]->setValue(stressValues->strainOutput[i]);
    this->stressToggle[i]->setValue(stressValues->stressOutput[i]);
  }
  if ((showVTFfield = stressValues->autoVTFSwitch >= 0)) {
    this->autoVTFToggle->setValue(stressValues->autoVTFSwitch);
    this->autoVTFField->setAbsToRelPath(stressValues->modelFilePath);
    this->autoVTFField->setFileName(stressValues->autoVTFFileName);
    this->autoVTFField->setFilterID(stressValues->autoVTFFileType);
    this->autoVTFField->setSensitivity(stressValues->autoVTFSwitch);
    this->setVTFLabel(stressValues->autoVTFFileType);
    this->minFringeField->setValue(stressValues->vtfFringeMin);
    this->maxFringeField->setValue(stressValues->vtfFringeMax);
  }
  this->setSensitivity(stressValues->isSensitive);
}
//-----------------------------------------------------------------------------

void FuiStressOptions::getUIValues(FFuaUIValues* values)
{
  FuaStressOptionsValues* stressValues = (FuaStressOptionsValues*) values;

  this->time->getUIValues(&stressValues->timeValues);
  stressValues->deformationOutput = this->deformationToggle->getValue();
  stressValues->stressResOutput   = this->stressResToggle->getValue();
  for (int i = 0; i < 5; i++) {
    stressValues->stressOutput[i] = this->stressToggle[i]->getValue();
    stressValues->strainOutput[i] = this->strainToggle[i]->getValue();
  }
  if (showVTFfield) {
    stressValues->autoVTFSwitch   = this->autoVTFToggle->getValue();
    stressValues->autoVTFFileName = this->autoVTFField->getFileName();
    stressValues->autoVTFFileType = this->autoVTFField->getFilterID();
    stressValues->vtfFringeMin    = this->minFringeField->getValue();
    stressValues->vtfFringeMax    = this->maxFringeField->getValue();
  }
  else
    stressValues->autoVTFSwitch = -1;
}
