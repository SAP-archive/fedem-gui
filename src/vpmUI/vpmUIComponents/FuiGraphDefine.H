// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_GRAPH_DEFINE_H
#define FUI_GRAPH_DEFINE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"
#include <string>
#include <array>

class FFuLabel;
class FFuIOField;
class FFuSpinBox;
class FFuOptionMenu;
class FFuToggleButton;
class FFuLabelField;


class FuiGraphDefine : virtual public FFuMultUIComponent,
		       public FFuUAExistenceHandler,
		       public FFuUADataHandler
{
public:
  FuiGraphDefine();
  virtual ~FuiGraphDefine() {}

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  // Inside callback functions
  void onFieldValueChanged(char*);
  void onFieldValueChanged(double);
  void onFieldValueChanged(int);
  void onButtonToggled(bool);

  // from datahandler
  virtual FFuaUIValues* createValuesObject();
  virtual void setUIValues(const FFuaUIValues* values);
  virtual void getUIValues(FFuaUIValues* values);

protected:
  FFuLabel*   titleLabel;
  FFuIOField* titleField;
  FFuLabel*   subtitleLabel;
  FFuIOField* subtitleField;
  FFuLabel*   xAxisLabel;
  FFuIOField* xAxisField;
  FFuLabel*   yAxisLabel;
  FFuIOField* yAxisField;

  std::array<FFuLabel*,3>   fontSizeLabel;
  std::array<FFuSpinBox*,3> fontSizeBox;

  FFuLabel*      gridLabel;
  FFuOptionMenu* gridMenu;

  FFuToggleButton* legendButton;
  FFuToggleButton* autoscaleButton;

  FFuLabelField*   tminField;
  FFuLabelField*   tmaxField;
  FFuToggleButton* timeButton;
};

/////////////////////////////////////////////////////////////////////////////

class FuaGraphDefineValues : public FFuaUIValues
{
public:
  FuaGraphDefineValues() {
    this->fontSize = {10,8,8};
    this->gridType = -1;
    this->showLegend = false;
    this->autoScaleOnLoadCurve = false;
    this->useTimeInterval = false;
    this->tmin = this->tmax = 0.0;
  }
  virtual ~FuaGraphDefineValues() {}

  std::string title;
  std::string subtitle;
  std::string xAxisLabel;
  std::string yAxisLabel;
  std::array<int,3> fontSize;

  int  gridType;
  bool showLegend;
  bool autoScaleOnLoadCurve;
  char useTimeInterval;
  double tmin, tmax;
};

/////////////////////////////////////////////////////////////////////////////

#endif
