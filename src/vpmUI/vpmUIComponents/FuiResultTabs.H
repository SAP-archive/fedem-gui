// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_RESULT_TABS_H
#define FUI_RESULT_TABS_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include <vector>
#include <array>

class FFuLabelFrame;
class FFuToggleButton;


class FuiTriadResults : public virtual FFuMultUIComponent
{
public:
  FuiTriadResults();
  virtual ~FuiTriadResults() {}

  void setToggleCB(const FFaDynCB1<bool>& cb);
  void setValues(const std::vector<bool>& vals);
  void getValues(std::vector<bool>& vals) const;

protected:
  void initWidgets();

  virtual void placeWidgets(int width, int height);

  FFuLabelFrame* myGlobalFrame;
  FFuLabelFrame* myLocalFrame;

  std::array<FFuToggleButton*,7> myToggles;
};


class FuiJointResults : public virtual FFuMultUIComponent
{
public:
  FuiJointResults();
  virtual ~FuiJointResults() {}

  void setToggleCB(const FFaDynCB1<bool>& cb);
  void setValues(const std::vector<bool>& vals);
  void getValues(std::vector<bool>& vals) const;

protected:
  void initWidgets();

  virtual void placeWidgets(int width, int height);

  FFuLabelFrame* myJointFrame;
  FFuLabelFrame* mySpringFrame;
  FFuLabelFrame* myDamperFrame;

  std::array<FFuToggleButton*,15> myToggles;
};

#endif
