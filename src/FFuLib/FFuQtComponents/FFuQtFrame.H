// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_FRAME_H
#define FFU_QT_FRAME_H

#include <QFrame>

#include "FFuLib/FFuFrame.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"


class FFuQtFrame : public QFrame, public FFuFrame, public FFuQtComponentBase
{
public:
  FFuQtFrame(QWidget* parent = NULL);
  virtual ~FFuQtFrame() {}

  virtual void setLook(int look);
  virtual void setBorderWidth(int width);
};

#endif
