// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_VIEWER_H
#define FD_VIEWER_H

class FFuComponentBase;
class QWidget;


namespace FdViewer
{
  FFuComponentBase* create(QWidget* parent, bool noRotation = false);
}

#endif
