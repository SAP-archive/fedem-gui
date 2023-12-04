// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_CREATE_TURBINE_ASSEMBLY_H
#define FUI_CREATE_TURBINE_ASSEMBLY_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include <vector>

class FFuOptionMenu;
class FFuLabel;
class FFuLabelFrame;
class FFuLabelField;
class FFuFileBrowseField;
class FFuSpinBox;
class FFuDialogButtons;
class FFuPushButton;
class FFuToggleButton;
class FmModelMemberBase;
class FmBladeDesign;


namespace FWP {
  enum FieldNames {
    NAME = 0,
    TOWER_X = 1,
    TOWER_Y = 2,
    TOWER_Z = 3,
    TOWER_T = 4,
    H1 = 5,
    HR = 6,
    ALPHA = 7,
    BETA = 8,
    D1 = 9,
    D2 = 10,
    D3 = 11,
    D4 = 12,
    D5 = 13,
    D6 = 14,
    B1 = 15,
    B2 = 16,
    S = 17,
    THETA = 18,
    COG_X = 19,
    COG_Y = 20,
    COG_Z = 21,
    NUM_FIELDS = 22
  };
}


class FuiCreateTurbineAssembly : virtual public FFuTopLevelShell,
				 public FFuUAExistenceHandler,
				 public FFuUADataHandler,
				 public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiCreateTurbineAssembly();
  virtual ~FuiCreateTurbineAssembly() {}

  static FuiCreateTurbineAssembly* create(int xpos = 100, int ypos = 100,
					  int width = 100, int height = 100,
					  const char* title= "Fedem Turbine Definition",
					  const char* name = "FuiCreateTurbineAssembly");

  virtual void setSensitivity(bool isSensitive);

protected:
  void initWidgets();
  void setMainImage(int drivelineType, int bearings);
  virtual bool onClose();

private:
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();

protected:
  void onDrivelineTypeChanged(int);
  void onBearingsChanged(int);

private:
  void onBladeDesignFileSelected(const std::string&,int);
  void onDialogButtonClicked(int button);
  virtual void onCopyButtonClicked() = 0;
  virtual void onPasteButtonClicked() = 0;

  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

  void createOrUpdateTurbine();

protected:
  FFuLabel*           headerImage;
  FFuLabel*           modelImage;
  FFuLabel*           drivelineTypeLabel;
  FFuOptionMenu*      drivelineTypeMenu;
  FFuLabel*           bearingsLabel;
  FFuOptionMenu*      bearingsMenu;
  FFuLabel*           nameLabel;
  FFuLabelFrame*      towerBaseFrame;
  FFuLabelFrame*      hubFrame;
  FFuLabelFrame*      drivelineFrame;
  FFuLabelFrame*      nacelleFrame;
  std::vector<FFuLabelField*> myFields;
  FFuPushButton*      copyButton;
  FFuPushButton*      pasteButton;
  FFuLabel*           bladesNumLabel;
  FFuSpinBox*         bladesNumField;
  FFuLabel*           bladesDesignLabel;
  FFuFileBrowseField* bladesDesignField;
  FFuToggleButton*    incCtrlSysToggle;
  FFuLabel*           notesImage;
  FFuLabel*           notesLabel;
  FFuLabelFrame*      notesSeparator;
  FFuLabel*           notesText;
  FFuDialogButtons*   dialogButtons;

private:
  bool haveTurbine;
  FmBladeDesign* currentBladeDesign;
};
////////////////////////////////////////////////////////////////////////////////

class FuaCreateTurbineAssemblyValues : public FFuaUIValues
{
public:
  FuaCreateTurbineAssemblyValues(size_t nval = 0) : geom(nval,0.0) {
    haveTurbine = incCtrlSys = false;
    drivelineType = bearings = bladesNum = 0;
    bladesDesign = NULL;
    isSensitive = true;
  }
  virtual ~FuaCreateTurbineAssemblyValues() {}

  char                haveTurbine;   //!< 0: no turbine, 1=unattached, 2=attached
  int                 drivelineType; //!< Drive line type (=gearbox 1=direct)
  int                 bearings;      //!< Number of bearings (0, 1 or 2)
  int                 bladesNum;     //!< Number of blades (3 or 4)
  FmModelMemberBase*  bladesDesign;  //!< Pointer to turbine blade design object
  std::string         name;          //!< Name field
  std::vector<double> geom;          //!< Geometry parameters
  bool                incCtrlSys;    //!< Include control system?

  bool isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
