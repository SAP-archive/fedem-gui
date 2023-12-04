// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_MODAL_DIALOG_H
#define FFU_MODAL_DIALOG_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"


class FFuModalDialog : virtual public FFuTopLevelShell
{
  Fmd_HEADER_INIT();

public:
  FFuModalDialog();
  virtual ~FFuModalDialog() {}

  virtual bool execute() = 0;
  virtual void closeDialog(bool resultCode) = 0;

private:
  virtual void onDialogButtonClicked(int) = 0;

protected:
  // Reimplemented from FFuTopLevelShell
  virtual void setNonBlockableWidget(FFuComponentBase*) {}
  virtual void onPoppedUp();
  virtual bool onClose();
};

#endif
