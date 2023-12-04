// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_MOORING_LINE_H
#define FUI_MOORING_LINE_H

#include "FFuLib/FFuBase/FFuModalDialog.H"

class FFuLabel;
class FFuLabelField;
class FFuOptionMenu;
class FFuDialogButtons;


class FuiMooringLine : virtual public FFuModalDialog
{
  Fmd_HEADER_INIT();

protected:
  FuiMooringLine();
  virtual ~FuiMooringLine() {}

  void initWidgets();

private:
  virtual void placeWidgets(int width, int height);

public:
  static FuiMooringLine* create(int xpos = 100, int ypos = 100,
                                int width = 300, int height = 200,
                                const char* title = "Mooring Line",
                                const char* name = "FuiMooringLine");

  void addElmType(const std::string& etype, bool clear = false);

  int getElmType();
  int getNumSeg();
  double getLength();

protected:
  FFuLabelField* myNumField;
  FFuLabel*      myTypeLabel;
  FFuOptionMenu* myTypeMenu;
  FFuLabelField* myLengthField;

  FFuDialogButtons* myDialogButtons;
};

#endif
