// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_DIALOG_BUTTONS_H
#define FFU_QT_DIALOG_BUTTONS_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "FFuLib/FFuDialogButtons.H"


class FFuQtDialogButtons : public FFuQtMultUIComponent,	public FFuDialogButtons
{
public:
  //You get the buttons in which you set their labels
  //Empty button label ("") gives no button
  FFuQtDialogButtons(QWidget* parent=0, bool separator = true,
		     const char* leftButtonLabel="",
		     const char* midButtonLabel="",
		     const char* rightButtonLabel="",
		     const char* name="FFuQtDialogButtons");
  virtual ~FFuQtDialogButtons() {}
};

#endif
