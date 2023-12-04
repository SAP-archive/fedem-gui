// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_JOINT_DOF_H
#define FUI_JOINT_DOF_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiSimpleLoad.H"
#include "vpmUI/vpmUIComponents/FuiSpringDefCalc.H"
#include "vpmUI/vpmUIComponents/FuiSprDaForce.H"

class FuiJointDOFValues;
class FuiMotionType;
class FuiVariableType;
class FFuLabelField;
class FFuToggleButton;


class FuiJointDOF : public virtual FFuMultUIComponent
{
public:
  FuiJointDOF();
  virtual ~FuiJointDOF() {}

  void setChangedCB(const FFaDynCB0& aDynCB);

  void getValues(FuiJointDOFValues& values) const;
  void setValues(const FuiJointDOFValues& values,
                 bool isSensitive = true);

  int dofNo;
  FuiMotionType*    motionType;
  FuiVariableType*  variableType;
  FuiSimpleLoad*    simpleLoad;
  FuiSpringDefCalc* springDC;
  FuiSprDaForce*    springFS;
  FuiSprDaForce*    damperFS;
  FFuLabelField*    initialVel;
  FFuToggleButton*  freqToggle;

  enum {
    FREE,
    FIXED,
    PRESCRIBED,
    FREE_DYNAMICS,
    SPRING_CONSTRAINED,
    SPRING_DYNAMICS,
    PRESCRIBED_DISP,
    PRESCRIBED_VEL,
    PRESCRIBED_ACC
  };

protected:
  virtual void placeWidgets(int width, int height);

  void initWidgets();
};


class FuiJointDOFValues
{
public:
  int myDofNo;
  int myMotionType;
  bool freqDomain;
  double myInitVel;
  FuiSimpleLoadValues    myLoadVals;
  FuiSpringDefCalcValues mySpringDCVals;
  FuiSprDaForceValues    mySpringFSVals;
  FuiSprDaForceValues    myDamperFCVals;

  FuiJointDOFValues(int dof = -1) {
    myDofNo = dof;
    myMotionType = -1;
    freqDomain = false;
    myInitVel = 0.0;
  }
};

#endif
