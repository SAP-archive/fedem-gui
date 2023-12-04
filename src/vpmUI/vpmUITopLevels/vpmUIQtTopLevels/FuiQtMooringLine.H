// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_MOORING_LINE_H
#define FUI_QT_MOORING_LINE_H

#include "FFuLib/FFuQtBaseClasses/FFuQtModalDialog.H"
#include "vpmUI/vpmUITopLevels/FuiMooringLine.H"


class FuiQtMooringLine : public FFuQtModalDialog,
                         virtual public FuiMooringLine
{
public:
  FuiQtMooringLine(int xpos, int ypos, int width, int height,
                   const char* title, const char* name);
  virtual ~FuiQtMooringLine() {}

private:
  virtual void onDialogButtonClicked(int);
};

#endif
