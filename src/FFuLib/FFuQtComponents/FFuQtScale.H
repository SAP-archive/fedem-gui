// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_SCALE_H
#define FFU_QT_SCALE_H

#include <QSlider>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuScale.H"


class FFuQtScale : public QSlider, public FFuScale,
		   virtual public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtScale(QWidget* parent = NULL);
  virtual ~FFuQtScale() {}

  virtual void setValue(int value);
  virtual int  getValue() const;

  virtual void setMinMax(int  min, int  max);
  virtual void getMinMax(int& min, int& max) const;

protected slots:
  void dragged(int value);
  void released();

private:
  int myValue;
};

#endif
