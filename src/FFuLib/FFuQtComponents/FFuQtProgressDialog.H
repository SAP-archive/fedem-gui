// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_PROGRESS_DIALOG_H
#define FFU_QT_PROGRESS_DIALOG_H

#include <QProgressDialog>

#include "FFuLib/FFuProgressDialog.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"


class FFuQtProgressDialog : public QProgressDialog,
			    public FFuProgressDialog,
			    virtual public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtProgressDialog(const std::string& labelTxt,
		      const std::string& btnTxt,
		      const std::string& title,
		      int numSteps);
  virtual ~FFuQtProgressDialog() {}

  // Returns true if user has cancelled
  virtual bool userCancelled();
  virtual void doCancel();
  virtual void doReset();

  // Set properties
  virtual void setNumberSteps(int steps);
  virtual void setCurrentProgress(int progress);
  virtual void setLabelTxt(const std::string& label);
  virtual void setButtonText(const std::string& txt);
  virtual void setDelayTime(int ms);
  virtual void setAutomaticReset(bool tf);
  virtual void setAutomaticClose(bool tf);

  // Retrieve properties
  virtual int getTotalSteps();
  virtual int getProgress();
  virtual std::string getLabelText();
  virtual int getDelayTime();

private slots:
  void fwdCanceled() { myCancelledCB.invoke(); }
};

#endif
