// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_TRIAD_SUMMARY_H
#define FUI_TRIAD_SUMMARY_H

#include "vpmUI/vpmUIComponents/FuiSummaryTable.H"

class FFuLabelFrame;
class FFuLabelField;
class FFuPushButton;
class FFuOptionMenu;
class FuiTriadDOFValues;


class FuiTriadSummary : public FuiSummaryTable
{
public:
  FuiTriadSummary() {}
  virtual ~FuiTriadSummary() {}

  void setSummary(int dof, const FuiTriadDOFValues& tval);

  FFuLabelField* myFENodeField;
  FFuPushButton* mySetAllFreeButton;
  FFuPushButton* mySetAllFixedButton;

  FFuLabelFrame* myMassFrame;
  FFuLabelField* myMassField;
  FFuLabelField* myIxField;
  FFuLabelField* myIyField;
  FFuLabelField* myIzField;

  FFuLabel*      myTriadLabel;
  FFuLabelFrame* mySysDirFrame;
  FFuOptionMenu* mySysDirMenu;
  FFuLabelFrame* myConnectorFrame;
  FFuOptionMenu* myConnectorMenu;

protected:
  virtual void placeWidgets(int width, int height);
  virtual void initWidgets();
};

#endif
