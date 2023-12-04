// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_POSITION_DATA_H
#define FUI_QT_POSITION_DATA_H

#include <string>

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiPositionData.H"

class QGroupBox;


class FuiQtPositionData : public virtual FFuQtMultUIComponent, 
			  public FuiPositionData
{
public:
  FuiQtPositionData(QWidget* parent = NULL,
		    int xpos=100, int ypos=100,
		    int width=800,int height=35,
		    const char* name="PositionData");
  virtual ~FuiQtPositionData() {}

  virtual int getHeightHint();
  virtual int getWidthHint();

  virtual void setPosLabel(const std::string& text); 
  virtual void setRotLabel(const std::string& text);

  virtual void popUpRotUI(bool onOff);
  virtual void popUpPosUI(bool onOff);

  QGroupBox* myRotationFrame;
  QGroupBox* myTranslationFrame;

  virtual void setSensitivity(bool onOff) { this->FuiPositionData::setSensitivity(onOff); }
};

#endif
