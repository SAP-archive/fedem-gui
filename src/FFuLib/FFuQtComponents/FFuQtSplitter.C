// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtSplitter.H"


FFuQtSplitter::FFuQtSplitter(Qt::Orientation o, QWidget* parent) : QSplitter(o, parent)
{
  this->setWidget(this);
}

void FFuQtSplitter::setWidgetSizes(const std::vector<int>& sizes)
{
  QList<int> l; l.reserve(sizes.size());
  for (int i : sizes) l.push_back(i);
  this->setSizes(l);
}
