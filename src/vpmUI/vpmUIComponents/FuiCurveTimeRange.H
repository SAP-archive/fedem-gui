// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_CURVE_TIME_RANGE_H
#define FUI_CURVE_TIME_RANGE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include <vector>
#include <string>

class FFuOptionMenu;
class FFuLabelField;
class FFuIOField;


class FuiCurveTimeRange : virtual public FFuMultUIComponent
{
public:
  FuiCurveTimeRange();
  virtual ~FuiCurveTimeRange() {}

  void setUIValues(double tmin, double tmax, const std::string& selOper);
  void getUIValues(double& tmin, double& tmax, std::string& selOper);

  void setChangeCB(const FFaDynCB0& dynCB) { changeCB = dynCB; }

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  void onDoubleChanged(double);
  void onOperSelected(std::string);

protected:
  FFuOptionMenu* operMenu;
  FFuLabelField* timeField;
  FFuIOField*    maxField;

private:
  FFaDynCB0 changeCB;
};

#endif
