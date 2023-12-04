// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_TRIAD_DOF_H
#define FUI_QT_TRIAD_DOF_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiTriadDOF.H"


class FuiQtTriadDOF : public virtual FFuQtMultUIComponent,
		      public FuiTriadDOF
{
public:
  FuiQtTriadDOF(QWidget* parent, const char* name="TriadDOF");
  virtual ~FuiQtTriadDOF() {}
};

#endif
