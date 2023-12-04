// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUISUMMARYTABLE_H
#define FUISUMMARYTABLE_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include <vector>

class FFuTable;
class FFuLabel;


class FuiSummaryTable : public virtual FFuMultUIComponent
{
public:
  FuiSummaryTable() { mySummaryTable = 0; myAddBCLabel = 0; }
  virtual ~FuiSummaryTable() {}

  FFuTable* mySummaryTable;
  FFuLabel* myAddBCLabel;

protected:
  virtual void initWidgets();

  void updateColumnWidths();
  void columnSizeChanged(int col, int oldSize, int newSize);
  void tableDoubleClicked(int row, int col, int button);

  std::vector<double> myRelColWidths;
};

#endif
