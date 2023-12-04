// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtFrame.H"


FFuQtFrame::FFuQtFrame(QWidget* parent) : QFrame(parent)
{
  this->setWidget(this);
}


void FFuQtFrame::setLook(int look)
{
  switch (look)
    {
    case FLAT:
      this->setFrameStyle(QFrame::NoFrame);
      break;
    case PANEL_RAISED:
       this->setFrameStyle(QFrame::Panel | QFrame::Raised);
      break;
    case PANEL_SUNKEN:
      this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
      break;
    case BORDER_RAISED:
      this->setFrameStyle(QFrame::Box | QFrame::Raised);
      break;
    case BORDER_SUNKEN:
      this->setFrameStyle(QFrame::Box | QFrame::Sunken);
      break;
    case BORDER_FLAT:
      this->setFrameStyle(QFrame::Box | QFrame::Plain);
      break;
    }
}


void FFuQtFrame::setBorderWidth(int width)
{
  this->setLineWidth(width);
}
