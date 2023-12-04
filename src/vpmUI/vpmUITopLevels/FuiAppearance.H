// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_APPERANCE_H
#define FUI_APPERANCE_H

#include <string>
#include <vector>

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include "FFuLib/FFuBase/FFuUAFinishHandler.H"
#include "FFuLib/FFuColor.H"

class FFuLabel;
class FFuFrame;
class FFuScale;
class FFuColorSelector;
class FFuDialogButtons;
class FFuOptionMenu;
class FFuLabelFrame;
class FuaAppearanceValues;


class FuiAppearance : virtual public FFuTopLevelShell,
		      public FFuUAExistenceHandler,
		      public FFuUADataHandler, public FFuUAFinishHandler
{
  Fmd_HEADER_INIT();

public:
  FuiAppearance();
  virtual ~FuiAppearance() {}

  // Static create method to use instead of constructor :
  // Implementation in GUILib Dependenet implementation file

  static FuiAppearance* create( int xpos=100, int ypos=100,
				int width=100, int height=100,
				const char *title= "Item Appearance",
				const char *name = "FuiAppearance");

  virtual void setUIValues(const FFuaUIValues* values);
  bool getValues(FuaAppearanceValues* values) const;
  virtual bool updateDBValues(bool updateui=true);

  virtual bool onClose();

  // callbacks
  void onDialogButtonClicked(int button);
  void onTranspSliderChanged(int)     { isTransparencyChanged = true; this->updateDBValues(); isTransparencyChanged = false;}
  void onShininessSliderChanged(int)  { isShininessChanged    = true; this->updateDBValues(); isShininessChanged    = false;}
  void onPolygonOptionChanged(int)    { isPolygonsChanged     = true; this->updateDBValues(); isPolygonsChanged     = false;}
  void onLinesOptionChanged(int)      { isLinesChanged        = true; this->updateDBValues(); isLinesChanged        = false;}
  void colorValueChanged(FFuColor)    { isColorChanged        = true; this->updateDBValues(); isColorChanged        = false;}

  // detail changes
  void disableAdvancedOptions(bool trueOrFalse);
  void setPolygonLODText(const std::vector<std::string>& options);
  void setLinesLODText(const std::vector<std::string>& options);

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets(void);

private:
  void placeDetails(FFuComponentBase *parent);
  void placeColor(FFuComponentBase *parent);
  void placeMaterial(FFuComponentBase *parent);

protected:

  // Main frames

  FFuLabelFrame *myDetailsFrame;
  FFuLabelFrame *myColorFrame;
  FFuLabelFrame *myMaterialFrame;

  FFuColorSelector *myColorSelector;

  // Dialog button:

  FFuDialogButtons* myDialogButtons;

  FFuLabel *myShininessLabel;
  FFuLabel *myTransparencyLabel;
  FFuScale *myShininessScale;
  FFuScale *myTransparencyScale;

  FFuLabel *myPolygonsLabel;
  FFuLabel *myLinesLabel;

  FFuOptionMenu *myPolygonOptions;
  FFuOptionMenu *myLinesOptions;

private:
  bool isShininessChanged;
  bool isTransparencyChanged;
  bool isColorChanged;
  bool isPolygonsChanged;
  bool isLinesChanged;
};


////////////////////////////////////////////////////////////////////////////////

class FuaAppearanceValues : public FFuaUIValues
{
public:
  FuaAppearanceValues()
  {
    isShininessChanged = isTransparencyChanged = isColorChanged = false;
    isPolygonsChanged = isLinesChanged = false;
    myShininess = myTransparency = 0;
    myPolygonsValue = myLinesValue = 0;
  }
  virtual ~FuaAppearanceValues() {}

  bool isShininessChanged;
  int  myShininess;

  bool isTransparencyChanged;
  int  myTransparency;

  bool isColorChanged;
  FFuColor myColor;

  bool isPolygonsChanged;
  int  myPolygonsValue;

  bool isLinesChanged;
  int  myLinesValue;
};

#endif
