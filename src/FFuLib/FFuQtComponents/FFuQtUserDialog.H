// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_USER_DIALOG_H
#define FFU_QT_USER_DIALOG_H

#include <QMessageBox>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuUserDialog.H"


class FFuQtUserDialog : public QMessageBox, public FFuUserDialog,
                        public FFuQtComponentBase
{
public:
  FFuQtUserDialog(const char* msgText, int dialogType, const char** buttonTexts,
		  unsigned int nButtons, bool modal = true);
  virtual ~FFuQtUserDialog() {}

  virtual int execute();

private:
  virtual void closeEvent(QCloseEvent* e);
  virtual void done(int r);
};

#endif
