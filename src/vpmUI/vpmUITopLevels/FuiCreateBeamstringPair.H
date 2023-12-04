// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_CREATE_BEAMSTRING_PAIR_H
#define FUI_CREATE_BEAMSTRING_PAIR_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabel;
class FFuLabelFrame;
class FFuPushButton;
class FFuToggleButton;
class FFuaQueryBase;
class FuiQueryInputField;
class FuiQueryInputFieldValues;
class FmModelMemberBase;


struct FuiCreateBeamstringPairCBs
{
  FFaDynCB4<FmModelMemberBase*,FmModelMemberBase*,FmModelMemberBase*,bool> createCB;
  FFaDynCB2<FmModelMemberBase*,FmModelMemberBase*>                         deleteCB;
};


class FuiCreateBeamstringPair : virtual public FFuTopLevelShell,
				public FFuUAExistenceHandler,
				public FFuUADataHandler
{
  Fmd_HEADER_INIT();

public:
  FuiCreateBeamstringPair();
  virtual ~FuiCreateBeamstringPair() {}

  static FuiCreateBeamstringPair* create(int xpos = 100, int ypos = 100,
					 int width = 100, int height = 100,
					 const char* title= "Fedem Beamstring Pair Definition",
					 const char* name = "FuiCreateBeamstringPair");

  virtual void setSensitivity(bool isSensitive);

  void setCBs(const FuiCreateBeamstringPairCBs& cb) { this->myCBs = cb; }

protected:
  void initWidgets();
  virtual bool onClose();

private:
  virtual void placeWidgets(int width, int height);
  virtual void onPoppedUp();

  void onCreateButtonClicked();
  void onEraseButtonClicked();
  void onHelpButtonClicked();

  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);

  FuiCreateBeamstringPairCBs myCBs;

protected:
  FFuLabel*           headerImage;
  FFuLabel*           beamstringLabel1;
  FuiQueryInputField* beamstringMenu1;
  FFuLabel*           beamstringLabel2;
  FuiQueryInputField* beamstringMenu2;
  FFuLabel*           stiffnessFunctionLabel;
  FuiQueryInputField* stiffnessFunctionMenu;
  FFuToggleButton*    useRadialSpringsToggle;
  FFuLabel*           notesImage;
  FFuLabel*           notesLabel;
  FFuLabelFrame*      notesSeparator;
  FFuLabel*           notesText;
  FFuLabelFrame*      buttonSeparator;
  FFuPushButton*      createButton;
  FFuPushButton*      eraseButton;
  FFuPushButton*      closeButton;
  FFuPushButton*      helpButton;
};
////////////////////////////////////////////////////////////////////////////////

class FuaCreateBeamstringPairValues : public FFuaUIValues
{
public:
  FuaCreateBeamstringPairValues() {
    this->beamstringQuery1 = this->beamstringQuery2 = NULL;
    this->stiffnessFunctionQuery = NULL;
    this->isSensitive = true;
  }
  virtual ~FuaCreateBeamstringPairValues() {}

  FFuaQueryBase* beamstringQuery1;
  FFuaQueryBase* beamstringQuery2;
  FFuaQueryBase* stiffnessFunctionQuery;

  bool isSensitive;
};
////////////////////////////////////////////////////////////////////////////////

#endif
