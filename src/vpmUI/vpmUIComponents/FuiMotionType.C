// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiMotionType.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuRadioButton.H"
#include "FFuLib/FFuToggleButton.H"


FuiMotionType::FuiMotionType(int nButton)
{
  IAmSensitive = true;
  myMotionTypeLabels.reserve(4);
  myMotionTypeLabels.push_back("Free");
  myMotionTypeLabels.push_back("Fixed");
  myMotionTypeLabels.push_back("Prescribed");
  if (nButton > 3)
    myMotionTypeLabels.push_back("Spring-Damper");
}


void FuiMotionType::initWidgets()
{
  myFrame->setLabel("Constraint Type");

  for (size_t i = 0; i < myMotionTypeButtons.size(); i++)
  {
    myMotionTypeButtons[i]->setLabel(myMotionTypeLabels[i].c_str());
    myMotionTypeToggleGroup.insert(myMotionTypeButtons[i]);
  }

  myMotionTypeToggleGroup.setGroupToggleCB(FFaDynCB2M(FuiMotionType,this,
						      onMotionTypeChanged,int,bool));

  myAddButton->setLabel("Additional BC");
  myAddButton->setToggleCB(FFaDynCB1M(FuiMotionType,this,onButtonToggled,bool));
  myAddButton->setToolTip("Fix in initial equilibirum analysis only\n"
			  "and optionally in eigenmode analysis");
}


void FuiMotionType::placeWidgets(int width, int height)
{
  int border      = 6;
  int frameLeft   = 0;
  int frameRight  = width;
  int frameTop    = 0;
  int frameBtm    = height;

  int fieldHeight = 20;
  int fieldSpace  = 10;

  int nButtons = myMotionTypeButtons.size();

  while ((2*nButtons+1)*(fieldHeight+fieldSpace) > 2*height-4*border)
    if ((2*nButtons+1)*fieldHeight > 2*height-4*border) {
      fieldHeight = (2*height-4*border)/(2*nButtons+1);
      fieldSpace = 0;
      break;
    }
    else
      fieldSpace--;

  myFrame->setEdgeGeometry(frameLeft,frameRight,frameTop,frameBtm);

  int v1 = frameLeft  + border;
  int v2 = frameRight - border;
  int v3 = v2 - myAddButton->getWidthHint();
  int line = frameTop + fieldSpace + fieldHeight + border;
  myAddButton->setCenterYGeometry(v3, line, v2-v3, fieldHeight);
  for (int i = 0; i < nButtons; i++)
  {
    myMotionTypeButtons[i]->setCenterYGeometry(v1, line, v2-v1, fieldHeight);
    line += fieldSpace + fieldHeight;
  }
}


void FuiMotionType::setChangedCB(const FFaDynCB0& aDynCB)
{
  myChangedCB = aDynCB;
}

void FuiMotionType::setValuesChangedCB(const FFaDynCB1<int>& aDynCB)
{
  myValuesChangedCB = aDynCB;
}


void FuiMotionType::setValue(unsigned int motionType)
{
  bool addBC = false;
  if (motionType == 3)
  {
    addBC = true;
    motionType = 0;
  }
  else if (motionType == 4 || motionType == 5)
  {
    addBC = motionType == 5;
    motionType = 3;
  }

  if (motionType == 1 || motionType == 2)
  {
    myAddButton->setValue(false);
    myAddButton->setSensitivity(false);
  }
  else
  {
    myAddButton->setValue(addBC);
    myAddButton->setSensitivity(IAmSensitive);
  }

  if (motionType < myMotionTypeButtons.size())
    myMotionTypeToggleGroup.setValue(myMotionTypeButtons[motionType],true);
}

unsigned int FuiMotionType::getValue() const
{
  for (size_t i = 0; i < myMotionTypeButtons.size(); i++)
    if (myMotionTypeButtons[i]->getValue())
    {
      if (myAddButton->getValue())
      {
	if (i == 0)
	  return 3;
	else if (i == 3)
	  return 5;
      }
      return i == 3 ? 4 : i;
    }

  return 0;
}


void FuiMotionType::setSensitivity(bool isSensitive)
{
  IAmSensitive = isSensitive;
  for (size_t i = 0; i < myMotionTypeButtons.size(); i++)
    myMotionTypeButtons[i]->setSensitivity(isSensitive);

  if (myMotionTypeButtons[1]->getValue() || myMotionTypeButtons[2]->getValue())
    myAddButton->setSensitivity(false);
  else
    myAddButton->setSensitivity(isSensitive);
}

void FuiMotionType::setSensitivity(unsigned int button, bool isSensitive)
{
  if (button < myMotionTypeButtons.size())
    myMotionTypeButtons[button]->setSensitivity(isSensitive);
}


void FuiMotionType::onValuesChanged()
{
  myValuesChangedCB.invoke(this->getValue());
  myChangedCB.invoke();
}
