// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_ITEMS_LIST_VIEWS_H
#define FUI_ITEMS_LIST_VIEWS_H

#include "vpmUI/vpmUIComponents/FuiItemsListView.H"


class FuiSimModelListView : virtual public FuiItemsListView
{
public:
  FuiSimModelListView() {}
  virtual ~FuiSimModelListView() {}

protected:
  void initWidgets();
};


class FuiResultListView : virtual public FuiItemsListView
{
public:
  FuiResultListView() {}
  virtual ~FuiResultListView() {}

protected:
  void initWidgets();
};


class FuiRDBListView : virtual public FuiItemsListView
{
public:
  FuiRDBListView() {}
  virtual ~FuiRDBListView() {}

protected:
  void initWidgets();
};


class FuiSimModelRDBListView : virtual public FuiItemsListView
{
public:
  FuiSimModelRDBListView() {}
  virtual ~FuiSimModelRDBListView() {}

protected:
  void initWidgets();
};


class FuiCrossSectionListView : virtual public FuiItemsListView
{
public:
  FuiCrossSectionListView() {}
  virtual ~FuiCrossSectionListView() {}

protected:
  void initWidgets();
};


class FuiMaterialListView : virtual public FuiItemsListView
{
public:
  FuiMaterialListView() {}
  virtual ~FuiMaterialListView() {}

protected:
  void initWidgets();
};

#endif
