// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"


FFuQtLabelFrame::FFuQtLabelFrame(QWidget* parent) : QGroupBox(parent)
{
  this->setWidget(this);
}


void FFuQtLabelFrame::setLabel(const char* aLabel)
{
  this->setTitle(aLabel);
}


std::string FFuQtLabelFrame::getLabel() const
{
  return this->title().toStdString();
}
