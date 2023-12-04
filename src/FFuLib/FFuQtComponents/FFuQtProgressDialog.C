// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuQtProgressDialog.H"


/*!
  Creates a heap-allocated progress dialog. Remember to delete!
*/

FFuProgressDialog* FFuProgressDialog::create(const std::string& labelTxt,
					     const std::string& btnTxt,
					     const std::string& caption,
					     int numSteps)
{
  return new FFuQtProgressDialog(labelTxt, btnTxt, caption, numSteps);
}


FFuQtProgressDialog::FFuQtProgressDialog(const std::string& labelTxt,
					 const std::string& btnTxt,
					 const std::string& title,
					 int numSteps)
  : QProgressDialog(labelTxt.c_str(), btnTxt.c_str(), 0, numSteps, NULL, Qt::Dialog)
{
  this->setWidget(this);
  this->setWindowTitle(title.c_str());

  QObject::connect(this, SIGNAL(canceled()), this, SLOT(fwdCanceled()));
}


bool FFuQtProgressDialog::userCancelled()
{
  return this->wasCanceled();
}


void FFuQtProgressDialog::doCancel()
{
  this->cancel();
}


void FFuQtProgressDialog::doReset()
{
  this->reset();
}


void FFuQtProgressDialog::setNumberSteps(int steps)
{
  this->setMaximum(steps);
}


void FFuQtProgressDialog::setCurrentProgress(int progress)
{
  this->setValue(progress);
}


void FFuQtProgressDialog::setLabelTxt(const std::string& label)
{
  this->setLabelText(label.c_str());
}


void FFuQtProgressDialog::setButtonText(const std::string& txt)
{
  this->setCancelButtonText(txt.c_str());
}


void FFuQtProgressDialog::setDelayTime(int ms)
{
  this->setMinimumDuration(ms);
}


void FFuQtProgressDialog::setAutomaticReset(bool tf)
{
  this->setAutoReset(tf);
}


void FFuQtProgressDialog::setAutomaticClose(bool tf)
{
  this->setAutoClose(tf);
}


int FFuQtProgressDialog::getTotalSteps()
{
  return this->maximum();
}


int FFuQtProgressDialog::getProgress()
{
  return this->value();
}


std::string FFuQtProgressDialog::getLabelText()
{
  return this->labelText().toStdString();
}


int FFuQtProgressDialog::getDelayTime()
{
  return this->minimumDuration();
}
