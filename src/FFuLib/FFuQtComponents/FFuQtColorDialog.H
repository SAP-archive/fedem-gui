// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_COLOR_DIALOG_H
#define FFU_QT_COLOR_DIALOG_H

#include "FFuLib/FFuColorDialog.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"


class FFuQtColorDialog : public FFuQtTopLevelShell, public FFuColorDialog
{
public:
  FFuQtColorDialog(int xpos=100, int ypos=100,
                   int width=314,int height=145,
                   const char* title= "Color Dialog",
                   const char* name = "Color Dialog");
  virtual ~FFuQtColorDialog() {}

protected:
  virtual void closeEvent(QCloseEvent*);
};

#endif
