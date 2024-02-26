// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_SIM_MODEL_LISTVIEW_H
#define FAP_UA_SIM_MODEL_LISTVIEW_H

#include "FapUAModMemListView.H"


class FapUASimModelListView : public FapUAModMemListView
{
public:
  FapUASimModelListView(FuiItemsListView* ui);
  virtual ~FapUASimModelListView() {}

protected:
  // Reimplementations from FapUAItemsListView
  virtual bool isHeaderOkAsLeaf(FFaListViewItem* item) const;
  virtual bool verifyItem(FFaListViewItem* item);
  virtual FFaListViewItem* getParent(FFaListViewItem* item,
				     const std::vector<int>& assID) const;
  virtual void getChildren(FFaListViewItem* parent,
			   std::vector<FFaListViewItem*>& children) const;
  virtual std::vector<std::string> getItemText(FFaListViewItem* item);

private:
  // Reimplementations from FapUACommandHandler
  virtual FFuaUICommands* getCommands();

  FFuaCmdHeaderItem createHeader;
  FFuaCmdHeaderItem createSpringFunctionHeader;
  FFuaCmdHeaderItem createDamperFunctionHeader;
  FFuaCmdHeaderItem createFrictionHeader;
  FFuaCmdHeaderItem solveHeader;
  FFuaCmdHeaderItem resultHeader;

  FFuaCmdHeaderItem convertHeader;
  FFuaCmdHeaderItem convertToSpringHeader;
  FFuaCmdHeaderItem convertToDamperHeader;

  bool debugMode;
};

#endif
