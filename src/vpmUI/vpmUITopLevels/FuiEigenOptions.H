// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_EIGEN_OPTIONS_H
#define FUI_EIGEN_OPTIONS_H

#include <vector>
#include <string>

#include "vpmUI/vpmUITopLevels/FuiTopLevelDialog.H"

class FFuLabel;
class FFuOptionMenu;
class FFuPushButton;
class FFuFrame;
class FFuListView;
class FFuListViewItem;
class FFuToggleButton;
class FFuFileBrowseField;
class FuaEigenOptionsValues;


class FuiEigenOptions : public FuiTopLevelDialog
{
  Fmd_HEADER_INIT();

public:
  FuiEigenOptions();
  virtual ~FuiEigenOptions();

  // Static create method to use instead of constructor
  // Implementation in GUILib-dependent implementation file
  static FuiEigenOptions* create(int xpos = 100, int ypos  = 100,
				 int width= 100, int height= 100,
				 const char* title= "Mode Shape Recovery Setup",
				 const char* name = "FuiEigenOptions");

protected:
  virtual void initWidgets();

private:
  void setUIValues();
  void setUISelectedModes();

  virtual void setUIValues(const FFuaUIValues* values);
  virtual bool updateDBValues(bool updateui = true);

  virtual void placeWidgets(int width, int height);

  void addModeAtTime(int mode, double time);
  void addModeAtAllTimes(int mode);
  void addAllModesAtTime(double time);
  void addAllModes();

  void onAddButtonClicked();
  void onDeleteButtonClicked();
  void onTmpSelectionChanged(FFuListViewItem*);
  void onPermSelectionChanged();

  void setVTFLabel(int);
  void onAutoVTFToggled(bool);
  void onAutoVTFFileChanged(const std::string&, int);

protected:
  FFuLabel* selectLabel;
  FFuLabel* modeLabel;
  FFuLabel* timeLabel;
  FFuLabel* selectedModesLabel;

  FFuOptionMenu* modeMenu;
  FFuOptionMenu* timeMenu;

  FFuPushButton* addButton;
  FFuPushButton* deleteButton;

  FFuFrame*    separator;
  FFuListView* selectedModesView;

  FFuToggleButton*    autoVTFToggle;
  FFuFileBrowseField* autoVTFField;

private:
  FuaEigenOptionsValues* values;
};
////////////////////////////////////////////////////////////////////////////////

struct FuiModeData
{
  FuiModeData(int m = 0, double t = 0.0, int id = -1) {
    this->mode = m;
    this->time = t;
    this->listId = id;
  }

  bool operator< (const FuiModeData& m) const;
  bool operator==(const FuiModeData& m) const;

  int    mode;
  double time;
  int    listId; // id for this objects list view item
};
////////////////////////////////////////////////////////////////////////////////

class FuaEigenOptionsValues : public FFuaUIValues
{
public:
  FuaEigenOptionsValues() {
    this->autoVTFSwitch = false;
    this->autoVTFFileType = 0;
    this->isSensitive = true;
  }
  virtual ~FuaEigenOptionsValues() {}

  bool eraseModeData(int idToErase);

  // db -> ui
  std::vector<int>    modes;
  std::vector<double> times;

  // db <-> ui
  std::vector<FuiModeData> selectedModes;

  char autoVTFSwitch;
  int  autoVTFFileType;
  std::string autoVTFFileName;
  std::string modelFilePath;

  bool isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
