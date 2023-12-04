// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_CURVE_DEFINE_H
#define FUI_QT_CURVE_DEFINE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiCurveDefine.H"


class FuiQtCurveDefine : public FFuQtMultUIComponent, public FuiCurveDefine
{
 public:
  FuiQtCurveDefine(QWidget* parent = 0, const char* name = "FuiQtCurveDefine");
  virtual ~FuiQtCurveDefine() {}

 private:
  virtual void setSensitivity(bool) {}
};

/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveDefSheet : public FFuQtMultUIComponent, public FuiCurveDefSheet
{
 public:
  FuiQtCurveDefSheet(QWidget* parent = 0, const char* name = "FuiQtCurveDefSheet");
  virtual ~FuiQtCurveDefSheet() {}

 protected:
  virtual void setNoComps(unsigned int nc);

 private:
  virtual void setSensitivity(bool) {}
};

/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveAnalysisSheet : public FFuQtMultUIComponent, public FuiCurveAnalysisSheet
{
 public:
  FuiQtCurveAnalysisSheet(QWidget* parent = 0, const char* name = "FuiQtCurveAnaylsisSheet");
  virtual ~FuiQtCurveAnalysisSheet() {}

 private:
  virtual void setSensitivity(bool) {}
};


/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveAppearanceSheet : public FFuQtMultUIComponent, public FuiCurveAppearanceSheet
{
 public:
  FuiQtCurveAppearanceSheet(QWidget* parent = 0, const char* name = "FuiQtCurveAppearance");
  virtual ~FuiQtCurveAppearanceSheet();

 private:
  virtual void setSensitivity(bool) {}
};
/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveInfoSheet : public FFuQtMultUIComponent, public FuiCurveInfoSheet
{
 public:
  FuiQtCurveInfoSheet(QWidget* parent = 0, const char* name = "FuiQtCurveInfo");
  virtual ~FuiQtCurveInfoSheet() {}

 private:
  virtual void setSensitivity(bool) {}
};

/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveScaleSheet : public FFuQtMultUIComponent, public FuiCurveScaleSheet
{
public:
  FuiQtCurveScaleSheet(QWidget* parent = 0, const char* name = "FuiQtcurveScaleSheet");
  virtual ~FuiQtCurveScaleSheet() {}

 private:
  virtual void setSensitivity(bool) {}
};
/////////////////////////////////////////////////////////////////////////////

class FuiQtCurveFatigueSheet : public FFuQtMultUIComponent, public FuiCurveFatigueSheet
{
 public:
  FuiQtCurveFatigueSheet(QWidget* parent = 0, const char* name = "FuiQtFatigueInfo");
  virtual ~FuiQtCurveFatigueSheet() {}

 private:
  virtual void setSensitivity(bool) {}
};

#endif
