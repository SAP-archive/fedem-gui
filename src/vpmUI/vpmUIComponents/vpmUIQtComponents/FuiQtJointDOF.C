// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtJointDOF.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtMotionType.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtVariableType.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSimpleLoad.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSpringDefCalc.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtSprDaForce.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelField.H"
#ifdef FT_HAS_FREQDOMAIN
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#endif


FuiQtJointDOF::FuiQtJointDOF(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  motionType   = new FuiQtMotionType(this);
  variableType = new FuiQtVariableType(this);
  simpleLoad   = new FuiQtSimpleLoad(this);
  springDC     = new FuiQtSpringDefCalc(this);
  springFS     = new FuiQtSprDaForce(this);
  damperFS     = new FuiQtSprDaForce(this);
  initialVel   = new FFuQtLabelField(this);
#ifdef FT_HAS_FREQDOMAIN
  freqToggle   = new FFuQtToggleButton(this);
#endif

  this->initWidgets();
}
