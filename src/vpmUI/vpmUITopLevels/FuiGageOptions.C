// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiGageOptions.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


Fmd_SOURCE_INIT(FUI_GAGEOPTIONS,FuiGageOptions,FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiGageOptions::FuiGageOptions()
{
  Fmd_CONSTRUCTOR_INIT(FuiGageOptions);
}
//----------------------------------------------------------------------------

void FuiGageOptions::setSensitivity(bool sens)
{
  this->importRosFileButton->setSensitivity(sens);
  this->FuiTopLevelDialog::setSensitivity(sens);
}
//----------------------------------------------------------------------------

void FuiGageOptions::initWidgets()
{
  this->time->setResetCB(FFaDynCB0M(FuiGageOptions,this,onResetTimeClicked));

  this->autoDacExportToggle->setLabel("Direct export of gage strains to DAC files");
  this->autoDacExportToggle->setToggleCB(FFaDynCB1M(FuiGageOptions,this,
						    onAutoDacExportToggled,bool));
  this->dacSampleRateField->setLabel("DAC file sample rate");

  this->rainflowToggle->setLabel("Report cyclecount");
  this->rainflowToggle->setToggleCB(FFaDynCB1M(FuiGageOptions,this,
					       onRainflowToggled,bool));
  this->binSizeField->setLabel("Stress cycle bin size");

  this->importRosFileButton->setLabel("Import strain rosette file...");

  this->FuiTopLevelDialog::initWidgets();
}
//----------------------------------------------------------------------------

void FuiGageOptions::placeWidgets(int width, int height)
{
  int border = this->getBorder();
  int timet = border;
  int timeb = 13*(height - this->getDialogButtonsHeightHint() - border)/24;
  this->time->setEdgeGeometry(border,width-border,timet,timeb);

  int sep = this->time->getSepH();
  int widgeth = this->time->getWidgetH();

  int ypos = timeb + sep;
  this->autoDacExportToggle->setEdgeGeometry(border, width-border, ypos, ypos+widgeth);
  ypos += widgeth + sep;
  this->dacSampleRateField->setEdgeGeometry(border, width-border, ypos, ypos+widgeth);
  ypos += widgeth + sep + border;
  this->rainflowToggle->setEdgeGeometry(border, width-border, ypos, ypos+widgeth);
  ypos += widgeth + sep;
  this->binSizeField->setEdgeGeometry(border, width-border, ypos, ypos+widgeth);
  ypos += widgeth + sep + border;
  this->importRosFileButton->setEdgeGeometry(border, width-border, ypos, ypos+widgeth);

  this->FuiTopLevelDialog::placeWidgets(width,height);
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiGageOptions::createValuesObject()
{
  return new FuaGageOptionsValues();
}
//----------------------------------------------------------------------------

void FuiGageOptions::setUIValues(const FFuaUIValues* values)
{
  FuaGageOptionsValues* gageValues = (FuaGageOptionsValues*) values;

  this->time->setUIValues(&gageValues->timeValues);
  this->autoDacExportToggle->setValue(gageValues->autoDacSwitch);
  this->dacSampleRateField->setValue(gageValues->dacSampleRate);
  this->dacSampleRateField->setSensitivity(gageValues->autoDacSwitch);
  this->dacSampleRateField->myLabel->setSensitivity(gageValues->autoDacSwitch);
  this->rainflowToggle->setValue(gageValues->rainflowSwitch);
  this->binSizeField->setValue(gageValues->binSize);
  this->binSizeField->setSensitivity(gageValues->rainflowSwitch);
  this->binSizeField->myLabel->setSensitivity(gageValues->rainflowSwitch);
  this->setSensitivity(gageValues->isSensitive);
}
//-----------------------------------------------------------------------------

void FuiGageOptions::getUIValues(FFuaUIValues* values)
{
  FuaGageOptionsValues* gageValues = (FuaGageOptionsValues*) values;

  this->time->getUIValues(&gageValues->timeValues);
  gageValues->autoDacSwitch = this->autoDacExportToggle->getValue();
  gageValues->dacSampleRate = this->dacSampleRateField->getValue();
  gageValues->rainflowSwitch = this->rainflowToggle->getValue();
  gageValues->binSize = this->binSizeField->getValue();
}
//-----------------------------------------------------------------------------

void FuiGageOptions::setTimeUIValues(const FuaTimeIntervalValues* timeValues)
{
  this->time->setUIValues(timeValues);
}
//-----------------------------------------------------------------------------

void FuiGageOptions::setResetTimeCB(const FFaDynCB0& dynCB)
{
  this->resetTimeCB = dynCB;
}
//-----------------------------------------------------------------------------

void FuiGageOptions::onResetTimeClicked()
{
  this->resetTimeCB.invoke();
}
//-----------------------------------------------------------------------------

void FuiGageOptions::onAutoDacExportToggled(bool value)
{
  this->dacSampleRateField->setSensitivity(value);
  this->dacSampleRateField->myLabel->setSensitivity(value);
}
//-----------------------------------------------------------------------------

void FuiGageOptions::onRainflowToggled(bool value)
{
  this->binSizeField->setSensitivity(value);
  this->binSizeField->myLabel->setSensitivity(value);
}
//-----------------------------------------------------------------------------

void FuiGageOptions::setImportRosetteFileCB(const FFaDynCB0& dynCB)
{
  this->importRosFileButton->setActivateCB(dynCB);
}
//-----------------------------------------------------------------------------
