// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CURVE_AXIS_DEFINITION_H
#define FUI_QT_CURVE_AXIS_DEFINITION_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiCurveAxisDefinition.H"
#include "vpmUI/vpmUIComponents/FuiCurveTimeRange.H"


class FuiQtCurveAxisDefinition : public FFuQtMultUIComponent,
                                 public FuiCurveAxisDefinition
{
public:
  FuiQtCurveAxisDefinition(QWidget* parent = 0,
			   const char* name = "FuiQtCurveAxisDefinition");
  virtual ~FuiQtCurveAxisDefinition() {}

private:
  virtual void setSensitivity(bool) {}
};


class FuiQtCurveTimeRange : public FFuQtMultUIComponent,
                            public FuiCurveTimeRange
{
public:
  FuiQtCurveTimeRange(QWidget* parent = 0,
		      const char* name = "FuiQtCurveTimeRange");
  virtual ~FuiQtCurveTimeRange() {}

private:
  virtual void setSensitivity(bool) {}
};

#endif
