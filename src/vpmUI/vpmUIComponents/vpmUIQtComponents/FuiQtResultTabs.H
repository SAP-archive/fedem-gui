// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_RESULT_TABS_H
#define FUI_QT_RESULT_TABS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiResultTabs.H"


class FuiQtTriadResults : public virtual FFuQtMultUIComponent,
                          public FuiTriadResults
{
public:
  FuiQtTriadResults(QWidget* parent, const char* name="TriadResults");
  virtual ~FuiQtTriadResults() {}
};


class FuiQtJointResults : public virtual FFuQtMultUIComponent,
                          public FuiJointResults
{
public:
  FuiQtJointResults(QWidget* parent, const char* name="JointResults");
  virtual ~FuiQtJointResults() {}
};

#endif
