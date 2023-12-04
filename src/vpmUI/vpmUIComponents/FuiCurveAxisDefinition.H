// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_CURVE_AXIS_DEFINITION_H
#define FUI_CURVE_AXIS_DEFINITION_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include <vector>
#include <string>

class FFuPushButton;
class FFuOptionMenu;
class FFuLabel;


class FuiCurveAxisDefinition : virtual public FFuMultUIComponent,
                               public FFuUAExistenceHandler
{
public:
  FuiCurveAxisDefinition();
  virtual ~FuiCurveAxisDefinition() {}

  void setUIValues(const std::string& result,
		   const std::vector<std::string>& opers,
		   const std::string& selOper);

  void setEditResultCB(const FFaDynCB0& dynCB)
  { this->editResultCB = dynCB; }
  void setOperSelectedCB(const FFaDynCB1<const std::string&>& dynCB)
  { this->operSelectedCB = dynCB; }

protected:
  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

  void onOperMenuSelected(std::string oper);
  void onEditButtonClicked();

protected:
  FFuLabel*      resultLabel;
  FFuPushButton* editButton;
  FFuOptionMenu* operMenu;

private:
  FFaDynCB0 editResultCB;
  FFaDynCB1<const std::string&> operSelectedCB;
};

#endif
