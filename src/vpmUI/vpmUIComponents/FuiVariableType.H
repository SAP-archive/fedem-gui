// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIVARIABLETYPE_H
#define FUIVARIABLETYPE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabelFrame;
class FFuOptionMenu;


class FuiVariableType : public virtual FFuMultUIComponent
{
public:
  FuiVariableType() {}
  virtual ~FuiVariableType() {}

  virtual void setSensitivity(bool isSensitive);

  void setChangedCB(const FFaDynCB0& aDynCB);
  void onMenuSelected(int);

  void setValue(int selection);
  int getValue() const;

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  FFuLabelFrame* myFrame;
  FFuOptionMenu* myTypeMenu;

private:
  FFaDynCB0 myChangedCB;
};

#endif
