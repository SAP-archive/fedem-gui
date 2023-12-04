// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtTriadDOF.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtMotionType.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtVariableType.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSimpleLoad.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#ifdef FT_HAS_FREQDOMAIN
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#endif


FuiQtTriadDOF::FuiQtTriadDOF(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  motionType   = new FuiQtMotionType(this,3);
  variableType = new FuiQtVariableType(this);
  loadField    = new FuiQtSimpleLoad(this);
  initialVel   = new FFuQtLabelField(this);
#ifdef FT_HAS_FREQDOMAIN
  freqToggle   = new FFuQtToggleButton(this);
#endif

  this->initWidgets();
}
