// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_LABEL_FRAME_H
#define FFU_QT_LABEL_FRAME_H

#include <QGroupBox>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuLabelFrame.H"


class FFuQtLabelFrame : public QGroupBox, public FFuLabelFrame, public FFuQtComponentBase
{
public:
  FFuQtLabelFrame(QWidget* parent = NULL);
  virtual ~FFuQtLabelFrame() {}

  virtual void setLabel(const char* aLabel);
  virtual std::string getLabel() const;
};

#endif
