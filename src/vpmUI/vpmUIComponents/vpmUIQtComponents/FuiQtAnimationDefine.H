// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_ANIMATION_DEFINE_H
#define FUI_QT_ANIMATION_DEFINE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiAnimationDefine.H"


class FuiQtAnimationDefine : public FFuQtMultUIComponent, public FuiAnimationDefine
{
public:
  FuiQtAnimationDefine(QWidget* parent, const char* name = "FuiQtAnimationDefine");
  virtual ~FuiQtAnimationDefine() {}
};


class FuiQtFringeSheet : public FFuQtMultUIComponent, public FuiFringeSheet
{
public:
  FuiQtFringeSheet(QWidget* parent, const char* name = "FuiQtFringeSheet");
  virtual ~FuiQtFringeSheet() {}
};


class FuiQtTimeSheet : public FFuQtMultUIComponent,  public FuiTimeSheet
{
public:
  FuiQtTimeSheet(QWidget* parent, const char* name = "FuiQtTimeSheet");
  virtual ~FuiQtTimeSheet() {}
};


class FuiQtModesSheet : public FFuQtMultUIComponent, public FuiModesSheet
{
public:
  FuiQtModesSheet(QWidget* parent, const char* name = "FuiQtModesSheet");
  virtual ~FuiQtModesSheet() {}
};

#endif
