// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiEigenOptions.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuListView.H"
#include "FFuLib/FFuListViewItem.H"
#include "FFuLib/FFuPopUpMenu.H"
#include "FFuLib/FFuFrame.H"
#include "FFuLib/FFuFileBrowseField.H"
#include "FFuLib/FFuFileDialog.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include <algorithm>


enum { MODE, TIME };

Fmd_SOURCE_INIT(FUI_EIGENMODEOPTIONS, FuiEigenOptions, FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiEigenOptions::FuiEigenOptions()
{
  Fmd_CONSTRUCTOR_INIT(FuiEigenOptions);

  this->values = new FuaEigenOptionsValues();
}
//----------------------------------------------------------------------------

FuiEigenOptions::~FuiEigenOptions()
{
  delete this->values;
}
//----------------------------------------------------------------------------

void FuiEigenOptions::initWidgets()
{
  this->addButton->setActivateCB(FFaDynCB0M(FuiEigenOptions,this,
					    onAddButtonClicked));
  this->deleteButton->setActivateCB(FFaDynCB0M(FuiEigenOptions,this,
					       onDeleteButtonClicked));
  this->selectedModesView->setPermSelectionChangedCB(FFaDynCB0M(FuiEigenOptions,this,
								onPermSelectionChanged));
  this->selectedModesView->setTmpSelectionChangedCB(FFaDynCB1M(FuiEigenOptions,this,
							       onTmpSelectionChanged,
							       FFuListViewItem*));

  this->selectLabel->setLabel("Select mode shape to recover:");
  this->modeLabel->setLabel("Mode:");
  this->timeLabel->setLabel("Time:");
  this->selectedModesLabel->setLabel("Mode shapes to recover:");

  this->addButton->setLabel("Add");
  this->deleteButton->setLabel("Delete");
  this->deleteButton->setSensitivity(false);

  FFuaCmdItem* item = new FFuaCmdItem();//TODO garbage (should be member,but..)
  item->setText("Delete");
  item->setActivatedCB(FFaDynCB0M(FuiEigenOptions,this,onDeleteButtonClicked));
  this->selectedModesView->getPopUpMenu()->insertCmdItem(item);

  this->selectedModesView->setHeaderClickEnabled(-1,false);//disable header click
  this->selectedModesView->setSglSelectionMode(false);
  this->selectedModesView->setListColumns({"  Mode","Time"});

  this->autoVTFToggle->setLabel("Automatic export to GLview VTF file");
  this->autoVTFToggle->setToggleCB(FFaDynCB1M(FuiEigenOptions,this,
					      onAutoVTFToggled,bool));
  this->autoVTFField->setLabel("Express File");
  this->autoVTFField->setAbsToRelPath("yes");
  this->autoVTFField->setDialogType(FFuFileDialog::FFU_SAVE_FILE);
  this->autoVTFField->setDialogRememberKeyword("AutoVTFField");

  this->autoVTFField->addDialogFilter("Express VTF file","vtf",true,0);
  this->autoVTFField->addDialogFilter("Binary VTF file","vtf",false,1);
  this->autoVTFField->addDialogFilter("ASCII VTF file","vtf",false,2);
  this->autoVTFField->setFileOpenedCB(FFaDynCB2M(FuiEigenOptions,this,
						 onAutoVTFFileChanged,
						 const std::string&,int));

  this->FuiTopLevelDialog::initWidgets();
}
//----------------------------------------------------------------------------

void FuiEigenOptions::placeWidgets(int width, int height)
{
  //l-left, r-right, t-top, b-bottom,
  int border = this->getBorder();
  int sep = 10;
  int labh = this->selectLabel->getHeightHint(); // same font for all labels
  int menuh = this->modeMenu->getHeightHint();   // same font for both menus
  int maxbuttw = 0;
  int maxbutth = 0;

  if (this->addButton->getWidthHint() > this->deleteButton->getWidthHint())
    maxbuttw = this->addButton->getWidthHint();
  else
    maxbuttw = this->deleteButton->getWidthHint();

  if (this->addButton->getHeightHint() > this->deleteButton->getHeightHint())
    maxbutth = this->addButton->getHeightHint();
  else
    maxbutth = this->deleteButton->getHeightHint();

  //vertical borders
  int glbl = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_START);
  int glbr = this->getGridLinePos(width,border,FFuMultUIComponent::FROM_END);
  //horisontal borders
  int glbt = this->getGridLinePos(height,border,FFuMultUIComponent::FROM_START);

  //vertical gridlines
  int glv0 = 4*(glbr-glbl)/10;

  //horisontal gridlines
  int glh[10];
  glh[0] = glbt+labh+sep/2;
  glh[1] = glh[0]+labh;
  glh[2] = glh[1]+menuh+sep;
  glh[3] = glh[2]+maxbutth+sep;
  glh[4] = glh[3]+2*sep;
  glh[5] = glh[4]+labh+sep/2;
  glh[7] = this->getGridLinePos(height,this->getDialogButtonsHeightHint(),
				FFuMultUIComponent::FROM_END);
  glh[6] = glh[7]-2*(menuh+sep);
  glh[8] = glh[6]+menuh/2+sep;
  glh[9] = glh[7]-menuh-sep;

  //place widgets
  this->selectLabel->setSizeGeometry(glbl,glbt,this->selectLabel->getWidthHint(),labh);

  this->modeLabel->setSizeGeometry(glbl,glh[0],this->modeLabel->getWidthHint(),labh);
  this->timeLabel->setSizeGeometry(glv0,glh[0],this->timeLabel->getWidthHint(),labh);

  this->modeMenu->setEdgeGeometry(glbl,glv0-sep,glh[1],glh[1]+menuh);
  this->timeMenu->setEdgeGeometry(glv0,glbr,glh[1],glh[1]+menuh);

  this->addButton->setSizeGeometry(glbr-maxbuttw,glh[2],maxbuttw,maxbutth);

  this->separator->setSizeGeometry(glbl,glh[3],glbr-glbl,0);

  this->selectedModesLabel->setSizeGeometry(glbl,glh[4],this->selectedModesLabel->getWidthHint(),labh);
  this->deleteButton->setSizeGeometry(glbr-maxbuttw,glh[4]+labh-maxbutth,maxbuttw,maxbutth);

  this->selectedModesView->setEdgeGeometry(glbl,glbr,glh[5],glh[6]);

  this->autoVTFToggle->setCenterYGeometryWidthHint(glbl,glh[8],menuh);
  this->autoVTFField->setEdgeGeometry(glbl,glbr,glh[9],glh[7]-sep);

  if (this->values->autoVTFSwitch >= 0) {
    this->autoVTFToggle->popUp();
    this->autoVTFField->popUp();
  }
  else {
    this->autoVTFToggle->popDown();
    this->autoVTFField->popDown();
  }

  this->dialogButtons->setEdgeGeometry(0,width,glh[7],height);

  //place selectedModesView's columns
  //this width setting may be subsequently overridden.
  this->selectedModesView->setListColumnWidth(MODE,3*(glbr-glbl-1)/10);
  this->selectedModesView->setListColumnWidth(TIME,7*(glbr-glbl-1)/10);
}
//-----------------------------------------------------------------------------

bool FuiEigenOptions::updateDBValues(bool)
{
  this->invokeSetAndGetDBValuesCB(this->values);
  this->setUIValues();
  return true;
}
//-----------------------------------------------------------------------------

void FuiEigenOptions::addModeAtTime(int mode, double time)
{
  std::vector<FuiModeData>::const_iterator i1 = this->values->selectedModes.begin();
  std::vector<FuiModeData>::const_iterator i2 = this->values->selectedModes.end();
  FuiModeData newMode(mode,time);
  if (std::find(i1,i2,newMode) == i2)
  {
    this->values->selectedModes.push_back(newMode);
    this->setUISelectedModes();
  }
}
//----------------------------------------------------------------------------

void FuiEigenOptions::addModeAtAllTimes(int mode)
{
  for (double time : this->values->times)
    this->addModeAtTime(mode,time);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::addAllModesAtTime(double time)
{
  for (int mode : this->values->modes)
    this->addModeAtTime(mode,time);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::addAllModes()
{
  this->values->selectedModes.clear();

  for (int mode : this->values->modes)
    for (double time : this->values->times)
      this->values->selectedModes.push_back(FuiModeData(mode,time));

  this->setUISelectedModes();
}
//----------------------------------------------------------------------------

void FuiEigenOptions::onAddButtonClicked()
{
  //get mode
  size_t iMode = this->modeMenu->getSelectedOption();
  if (iMode > this->values->modes.size())
    return;

  //get time
  size_t iTime = this->timeMenu->getSelectedOption();
  if (iTime > this->values->times.size())
    return;

  if (iMode < this->values->modes.size() && iTime < this->values->times.size())
    this->addModeAtTime(this->values->modes[iMode],this->values->times[iTime]);
  else if (iMode < this->values->modes.size())
    this->addModeAtAllTimes(this->values->modes[iMode]);
  else if (iTime < this->values->times.size())
    this->addAllModesAtTime(this->values->times[iTime]);
  else
    this->addAllModes();
}
//----------------------------------------------------------------------------

void FuiEigenOptions::onDeleteButtonClicked()
{
  std::vector<FFuListViewItem*> items = this->selectedModesView->getSelectedListItems();
  if (items.empty()) return;

  for (FFuListViewItem* item : this->selectedModesView->getSelectedListItems())
    this->values->eraseModeData(item->getItemId());

  this->setUISelectedModes();
}
//----------------------------------------------------------------------------

void FuiEigenOptions::onTmpSelectionChanged(FFuListViewItem* item)
{
  bool sensitive = item ? true : false;
  this->deleteButton->setSensitivity(sensitive);
  this->selectedModesView->getPopUpMenu()->setSensitivity(sensitive);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::onPermSelectionChanged()
{
  bool sensitive = !this->selectedModesView->getSelectedListItems().empty();
  this->deleteButton->setSensitivity(sensitive);
  this->selectedModesView->getPopUpMenu()->setSensitivity(sensitive);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::setVTFLabel(int id)
{
  const char* vtf_label[3] = { "Express File",
			       " Binary File",
			       "  ASCII File" };

  if (id >= 0 && id < 3)
    this->autoVTFField->setLabel(vtf_label[id]);
  else
    this->autoVTFField->setLabel("File");
}
//-----------------------------------------------------------------------------

void FuiEigenOptions::onAutoVTFFileChanged(const std::string& vtfFile, int id)
{
  this->setVTFLabel(id);
  this->values->autoVTFFileName = vtfFile;
  this->values->autoVTFFileType = id;
}
//----------------------------------------------------------------------------

void FuiEigenOptions::onAutoVTFToggled(bool value)
{
  this->values->autoVTFSwitch = value;
  this->autoVTFField->setSensitivity(value);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::setUIValues(const FFuaUIValues* vals)
{
  *this->values = *((FuaEigenOptionsValues*)vals);
  this->setUIValues();
}
//----------------------------------------------------------------------------

void FuiEigenOptions::setUIValues()
{
  size_t i, nItems;

  //modes
  this->modeMenu->clearOptions();
  nItems = this->values->modes.size();
  for (i = 0; i < nItems; i++)
    this->modeMenu->addOption(FFaNumStr(this->values->modes[i]).c_str());
  if (nItems == 2)
    this->modeMenu->addOption("(Both)");
  else if (nItems > 2)
    this->modeMenu->addOption("(All)");
  this->modeMenu->selectOption(0);

  //times
  this->timeMenu->clearOptions();
  nItems = this->values->times.size();
  for (i = 0; i < nItems; i++)
    this->timeMenu->addOption(FFaNumStr(this->values->times[i],1).c_str());
  if (nItems == 2)
    this->timeMenu->addOption("(Both)");
  else if (nItems > 2)
    this->timeMenu->addOption("(All)");
  this->timeMenu->selectOption(0);

  //selectedModes
  this->setUISelectedModes();

  //auto-VTF export
  if (this->values->autoVTFSwitch >= 0) {
    this->autoVTFToggle->setValue(this->values->autoVTFSwitch);
    this->autoVTFField->setAbsToRelPath(this->values->modelFilePath);
    this->autoVTFField->setFileName(this->values->autoVTFFileName);
    this->autoVTFField->setSensitivity(this->values->autoVTFSwitch);
    this->setVTFLabel(this->values->autoVTFFileType);
  }
  this->setSensitivity(this->values->isSensitive);
}
//----------------------------------------------------------------------------

void FuiEigenOptions::setUISelectedModes()
{
  std::sort(this->values->selectedModes.begin(),this->values->selectedModes.end());

  this->deleteButton->setSensitivity(false);
  this->selectedModesView->clearList();
  this->selectedModesView->getPopUpMenu()->setSensitivity(false);

  for (int i = this->values->selectedModes.size()-1; i >= 0; i--) {
    FFuListViewItem* listItem = this->selectedModesView->createListItem();
    //set listViewItem pointer
    this->values->selectedModes[i].listId = listItem->getItemId();
    //mode
    listItem->setItemText(MODE,FFaNumStr("  %d",this->values->selectedModes[i].mode).c_str());
    //time
    listItem->setItemText(TIME,("  "+FFaNumStr(this->values->selectedModes[i].time,1)).c_str());
  }
}
//----------------------------------------------------------------------------

bool FuiModeData::operator<(const FuiModeData& m) const
{
  if (this->mode > m.mode)
    return false;
  else if (this->mode < m.mode)
    return true;

  return this->time < m.time;
}
//----------------------------------------------------------------------------

bool FuiModeData::operator==(const FuiModeData& m) const
{
  return this->mode == m.mode && this->time == m.time;
}

//----------------------------------------------------------------------------

bool FuaEigenOptionsValues::eraseModeData(int idToErase)
{
  std::vector<FuiModeData>::iterator it;
  for (it = this->selectedModes.begin(); it != this->selectedModes.end(); it++)
    if (it->listId == idToErase) {
      this->selectedModes.erase(it);
      return true;
    }

  return false;
}
