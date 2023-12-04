// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_SPIN_BOX_H
#define FFU_QT_SPIN_BOX_H

#include <QSpinBox>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuSpinBox.H"


class FFuQtSpinBox : public QSpinBox, public FFuSpinBox,
		     virtual public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtSpinBox(QWidget* parent = NULL);
  virtual ~FFuQtSpinBox() {}

  virtual int getIntValue();
  virtual void setIntValue(int value);

  virtual std::string getPrefixString();
  virtual void setPrefixString(const std::string& prefix);

  virtual std::string getSuffixString();
  virtual void setSuffixString(const std::string& suffix);
  
  virtual void setWrapping(bool on);
  virtual bool hasWrapping();
  
  virtual void setButtonSymbol(int symbol);
  virtual int getButtonSymbol();
  
  virtual int getMinValue();
  virtual int getMaxValue();
  virtual void setMinMax(int min, int max);
  
  virtual void setStepSize(int step);
  virtual int getStepSize();

  virtual void stepOneUp();
  virtual void stepOneDown();

protected slots:
  void fwdValueChanged(int value);
};

#endif
