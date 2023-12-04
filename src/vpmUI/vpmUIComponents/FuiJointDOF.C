// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiJointDOF.H"
#include "vpmUI/vpmUIComponents/FuiMotionType.H"
#include "vpmUI/vpmUIComponents/FuiVariableType.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuIOField.H"


FuiJointDOF::FuiJointDOF() : dofNo(-1)
{
  motionType = NULL;
  variableType = NULL;
  simpleLoad = NULL;
  springDC = NULL;
  springFS = damperFS = NULL;
  initialVel = NULL;
  freqToggle = NULL;
}


void FuiJointDOF::initWidgets()
{
  initialVel->setLabel("Initial velocity");
  initialVel->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
#ifdef FT_HAS_FREQDOMAIN
  freqToggle->setLabel("Apply in frequency domain");
#endif
  springFS->setAsSpring(true);
  damperFS->setAsSpring(false);
}


void FuiJointDOF::placeWidgets(int width, int height)
{
  int border = 4;
  int columnWidth1 = (width - 4*border)/4;
  int columnWidth2 = (width - columnWidth1 - 4*border)/2;

  int v1 = border;
  int v2 = v1 + columnWidth1;
  int v3 = v2 + border;
  int v4 = v3 + columnWidth2;
  int v5 = v4 + border;
  int v6 = v5 + columnWidth2;

  int h1 = border;
  int h2 = 6*(height - 2*border)/10;
  int h3 = h2 + border;
  int h4 = height - border;
  int h5 = h4 - initialVel->myField->getHeightHint();
  if (h4-h5 > 2*(h5-border-h3)/3)
    h5 = 3*h4/5 + 2*(h3+border)/5;
  int h6 = h5 - border;
  int springBtm = h1 + 42*(h4 - h1)/100 - border/2;
  int damperTop = springBtm + border;

  motionType->  setEdgeGeometry(v1, v2, h1, h2);
  simpleLoad->  setEdgeGeometry(v1, v2, h3, h6);
  variableType->setEdgeGeometry(v1, v2, h3, h6);
#ifdef FT_HAS_FREQDOMAIN
  freqToggle->  setEdgeGeometry(v5, v6, h3, h3 + freqToggle->getHeightHint());
#endif
  initialVel->  setEdgeGeometry(v1, v2, h5, h4);
  springDC->    setEdgeGeometry(v3, v4, h1, h4);
  springFS->    setEdgeGeometry(v5, v6, h1, springBtm);
  damperFS->    setEdgeGeometry(v5, v6, damperTop, h4);
}


void FuiJointDOF::setChangedCB(const FFaDynCB0& aDynCB)
{
  simpleLoad->setChangedCB(aDynCB);
  variableType->setChangedCB(aDynCB);
  springDC->setChangedCB(aDynCB);
  springFS->setChangedCB(aDynCB);
  damperFS->setChangedCB(aDynCB);
}


void FuiJointDOF::getValues(FuiJointDOFValues& values) const
{
  values.myMotionType = motionType->getValue();
  if (values.myMotionType == PRESCRIBED)
    values.myMotionType = PRESCRIBED_DISP + variableType->getValue();

  simpleLoad->getValues(values.myLoadVals);
#ifdef FT_HAS_FREQDOMAIN
  values.freqDomain = freqToggle->getValue();
#endif
  values.myInitVel = initialVel->getValue();
  springDC->getValues(values.mySpringDCVals);
  springFS->getValues(values.mySpringFSVals);
  damperFS->getValues(values.myDamperFCVals);
}


void FuiJointDOF::setValues(const FuiJointDOFValues& values, bool isSensitive)
{
  int mType = values.myMotionType;
  if (mType >= PRESCRIBED_DISP) {
    variableType->setValue(mType-PRESCRIBED_DISP);
    mType = PRESCRIBED;
  }
  else if (mType == PRESCRIBED)
    variableType->setValue(0); // Default is prescribed displacement/angle

  motionType->setValue(mType);
  simpleLoad->setValues(values.myLoadVals);
#ifdef FT_HAS_FREQDOMAIN
  freqToggle->setValue(values.freqDomain);
#endif
  initialVel->setValue(values.myInitVel);
  springDC->setValues(values.mySpringDCVals);
  springFS->setValues(values.mySpringFSVals);
  damperFS->setValues(values.myDamperFCVals);

  bool isFree   = mType == FREE || mType == FREE_DYNAMICS;
  bool isSprDmp = mType == SPRING_CONSTRAINED || mType == SPRING_DYNAMICS;

  if (mType == PRESCRIBED)
    variableType->popUp();
  else
    variableType->popDown();

  if (isFree || isSprDmp)
    simpleLoad->popUp();
  else
    simpleLoad->popDown();

#ifdef FT_HAS_FREQDOMAIN
  if (isFree) {
    freqToggle->popUp();
    freqToggle->setSensitivity(isSensitive && !values.myLoadVals.isConstant);
  }
  else if (mType == PRESCRIBED) {
    freqToggle->popUp();
    freqToggle->setSensitivity(isSensitive && values.mySpringDCVals.selectedLengthEngine);
  }
  else
    freqToggle->popDown();
#else
  // Dummy statement to suppress compiler warning
  if (freqToggle) freqToggle->setSensitivity(isSensitive);
#endif

  if (mType == FIXED)
    initialVel->popDown();
  else
    initialVel->popUp();

  if (isSprDmp) {
    springFS->popUp();
    damperFS->popUp();
  }
  else {
    springFS->popDown();
    damperFS->popDown();
  }
}
