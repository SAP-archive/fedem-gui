// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_JOINT_DOF_H
#define FUI_QT_JOINT_DOF_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiJointDOF.H"


class FuiQtJointDOF : public virtual FFuQtMultUIComponent,
		      public FuiJointDOF
{
public:
  FuiQtJointDOF(QWidget* parent, const char* name="JointDOF");
  virtual ~FuiQtJointDOF() {}
};

#endif
