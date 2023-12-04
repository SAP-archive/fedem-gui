// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_PROGRESS_DIALOG_H
#define FFU_PROGRESS_DIALOG_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <string>


/*!
  \brief This class provides a progress dialog with a cancel button.

  Used as modal dialog.
  Check if user has cancelled by calling userCancelled().
  Qt will do a qApp->processEvents() for you.

  Implementation example:

  \verbatim

  FFuProgressDialog* progDlg = FFuProgressDialog::create("Please wait...",
                                                         "Cancel",
                                                         "Loading Animation",
                                                         100);
  // The dialog will show itself only if it figures out the
  // entire operation will take more than 2000 ms.
  progDlg->setDelayTime(2000);

  // Starting at 0
  progDlg->setCurrentProgress(0);

  for (;;) {

    // Incrementing progress
    progDlg->setCurrentProgress(nn);

    // ....

    // Check if user has cancelled
    if (progDlg->userCancelled()) {
      // ... cleanup?
      break;
    }

    // ...

  }

  // Finished, and setting progress equal to total steps
  // The dialog will be hidden and reset.
  progDlg->setCurrentProgress(100);

  // Freeing up memory
  delete progDlg;

  \endverbatim

  \sa FFuQtProgressDialog
  \sa QProgressDialog
*/

class FFuProgressDialog : virtual public FFuComponentBase
{
public:
  FFuProgressDialog() {}
  virtual ~FFuProgressDialog() {}

  //! Factory method to create a progress dialog.
  static FFuProgressDialog* create(const std::string& labelTxt="Please wait...",
				   const std::string& btnTxt="Cancel",
				   const std::string& caption="Fedem",
				   int numSteps=100);

  //! Returns true if user has cancelled.
  virtual bool userCancelled() = 0;
  //! Cancels the dialog.
  virtual void doCancel() = 0;
  //! Resets the dialog; progress is set to zero.
  virtual void doReset() = 0;

  //! Sets total number of steps.
  virtual void setNumberSteps(int steps) = 0;
  //! Sets progress.
  //! When you are finished, set progress equal to number of steps.
  //! This will cause the dialog to be reset and hidden,
  //! if these properties are true (which is default).
  //! Events are processed inside this call.
  virtual void setCurrentProgress(int progress) = 0;
  //! Sets the label text.
  virtual void setLabelTxt(const std::string& label) = 0;
  //! Sets the text on the cancel button.
  virtual void setButtonText(const std::string& txt) = 0;
  //! Sets the delay time to the given time (in milliseconds).
  //! The dialog will show itself (almost) immedeately if it figures out that
  //! the operation will take longer than the delay time. Default is 4 seconds.
  virtual void setDelayTime(int ms) = 0;
  //! Sets whether the dialog should reset itself when progress euals total number of steps.
  //! Default is true.
  virtual void setAutomaticReset(bool tf) = 0;
  //! Sets whether the dialog should close itself when progress equals total number of steps.
  //! Default is true.
  virtual void setAutomaticClose(bool tf) = 0;

  // Retrieve properties
  virtual int getTotalSteps() = 0;
  virtual int getProgress() = 0;
  virtual std::string getLabelText() = 0;
  virtual int getDelayTime() = 0;

  void setCancelledCB(const FFaDynCB0& cb) { myCancelledCB = cb; }

protected:
  FFaDynCB0 myCancelledCB;
};

#endif
