// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_MODEL_MANAGER_H
#define FUI_MODEL_MANAGER_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"

class FFuTabbedWidgetStack;
class FuiSimModelListView;
class FuiResultListView;


class FuiModelManager : virtual public FFuMultUIComponent
{
public:
  FuiModelManager();
  virtual ~FuiModelManager() {}

  FuiSimModelListView* getSimModelManager() { return this->simModelManager; }
  FuiResultListView* getResultManager() { return this->resultManager; }

protected:
  void initWidgets();
  virtual void placeWidgets(int width, int height);

private:
  void onTabSelected(int newTab);

protected:
  FFuTabbedWidgetStack* tabStack;
  FuiSimModelListView* simModelManager;
  FuiResultListView* resultManager;
};

#endif
