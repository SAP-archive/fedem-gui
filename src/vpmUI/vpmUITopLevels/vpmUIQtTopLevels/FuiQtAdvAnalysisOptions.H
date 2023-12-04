// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_ADV_ANALYSIS_OPTIONS_H
#define FUI_QT_ADV_ANALYSIS_OPTIONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiAdvAnalysisOptions.H"


class FuiQtAdvAnalysisOptionsSheet : public FFuQtMultUIComponent, public FuiAdvAnalysisOptionsSheet
{
public:
  FuiQtAdvAnalysisOptionsSheet(FuiAdvAnalysisOptions* owner)
  : FFuQtMultUIComponent(NULL,"FuiQtAdvAnalysisOptionsSheet"),
    FuiAdvAnalysisOptionsSheet(owner) {}
  virtual ~FuiQtAdvAnalysisOptionsSheet() {}
};


class FuiQtAdvAnalysisOptions : public FFuQtTopLevelShell, public FuiAdvAnalysisOptions
{
public:
  FuiQtAdvAnalysisOptions(QWidget* parent,
			  int xpos = 100, int ypos  = 100,
			  int width= 100, int height= 100, bool basicMode=false,
			  const char* title= "Fedem",
			  const char* name = "FuiQtAdvAnalysisOptions");
  virtual ~FuiQtAdvAnalysisOptions() {}

private:
  virtual void setSensitivity(bool sens)
  { this->FuiAdvAnalysisOptions::setSensitivity(sens); }

protected:
  virtual void onAdvBtnClicked();
};

#endif
