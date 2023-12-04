// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiResultTabs.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuToggleButton.H"


FuiTriadResults::FuiTriadResults()
{
  myGlobalFrame = myLocalFrame = NULL;
  myToggles.fill(NULL);
}


void FuiTriadResults::initWidgets()
{
  myGlobalFrame->setLabel("Global");
  myToggles[0]->setLabel("Velocity");
  myToggles[1]->setLabel("Acceleration");
  myToggles[2]->setLabel("Force");
  myToggles[6]->setLabel("Deformation");

  myLocalFrame->setLabel("Local");
  myToggles[3]->setLabel("Velocity");
  myToggles[4]->setLabel("Acceleration");
  myToggles[5]->setLabel("Force");
}


void FuiTriadResults::placeWidgets(int, int)
{
  int border = 5;
  int height = myToggles[0]->getHeightHint();
  int offset = height + border;

  int v1 = 4*border;
  int v2 = v1 + myToggles[1]->getWidthHint();
  int v3 = v2 + 4*border;
  int v4 = v3 + myToggles[4]->getWidthHint();
  int i, h, h1 = 6*border;

  for (i = 0, h = h1; i < 3; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v1, v2, h, h+height);
  myToggles[6]->setEdgeGeometry(v1, v2, h, h+height);
  myGlobalFrame->setEdgeGeometry(v1-border, v2+border, h1-offset, h+height+border);

  for (i = 3, h = h1; i < 6; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v3, v4, h, h+height);
  myLocalFrame->setEdgeGeometry(v3-border, v4+border, h1-offset, h+height+border);
}


void FuiTriadResults::setToggleCB(const FFaDynCB1<bool>& cb)
{
  for (FFuToggleButton* toggle : myToggles)
    toggle->setToggleCB(cb);
}


void FuiTriadResults::setValues(const std::vector<bool>& vals)
{
  for (size_t i = 0; i < myToggles.size(); i++)
    myToggles[i]->setValue(i < vals.size() ? vals[i] : false);
}


void FuiTriadResults::getValues(std::vector<bool>& vals) const
{
  vals.clear();
  vals.reserve(myToggles.size());
  for (FFuToggleButton* toggle : myToggles)
    vals.push_back(toggle->getValue());
}


FuiJointResults::FuiJointResults()
{
  myJointFrame = mySpringFrame = myDamperFrame = NULL;
  myToggles.fill(NULL);
}


void FuiJointResults::initWidgets()
{
  myJointFrame->setLabel("Joint variables");
  myToggles[0]->setLabel("Deflection");
  myToggles[1]->setLabel("Velocity");
  myToggles[2]->setLabel("Acceleration");
  myToggles[3]->setLabel("Friction/Reaction force");
  myToggles[4]->setLabel("Friction energy");

  mySpringFrame->setLabel("Spring variables");
  myToggles[5]->setLabel("Stiffness");
  myToggles[6]->setLabel("Length");
  myToggles[7]->setLabel("Deflection");
  myToggles[8]->setLabel("Force");
  myToggles[9]->setLabel("Energies");

  myDamperFrame->setLabel("Damper variables");
  myToggles[10]->setLabel("Coefficient");
  myToggles[11]->setLabel("Length");
  myToggles[12]->setLabel("Velocity");
  myToggles[13]->setLabel("Force");
  myToggles[14]->setLabel("Energies");
}


void FuiJointResults::placeWidgets(int width, int)
{
  int border = 5;
  int height = myToggles[0]->getHeightHint();
  int offset = height + border;

  int v1 = 4*border;
  int v2 = v1 + myToggles[2]->getWidthHint();
  int v3 = v2 + 4*border;
  int v4 = v3 + myToggles[3]->getWidthHint();
  int v5 = v4 + 6*border;
  int v6 = v5 + (width-v1-v5)/2-3*border;
  int v7 = v6 + 6*border;
  int v8 = width - v1;
  int i, h, h1 = 6*border;

  for (i = 0, h = h1; i < 3; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v1, v2, h, h+height);
  myJointFrame->setEdgeGeometry(v1-border, v4+border, h1-offset, h+border);
  for (i = 3, h = h1; i < 5; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v3, v4, h, h+height);

  for (i = 5, h = h1; i < 10; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v5, v6, h, h+height);
  mySpringFrame->setEdgeGeometry(v5-border, v6+border, h1-offset, h+border);

  for (i = 10, h = h1; i < 15; i++, h += offset)
    myToggles[i]->setEdgeGeometry(v7, v8, h, h+height);
  myDamperFrame->setEdgeGeometry(v7-border, v8+border, h1-offset, h+border);
}


void FuiJointResults::setToggleCB(const FFaDynCB1<bool>& cb)
{
  for (FFuToggleButton* toggle : myToggles)
    toggle->setToggleCB(cb);
}


void FuiJointResults::setValues(const std::vector<bool>& vals)
{
  size_t nToggles = myToggles.size();
  if (vals.size() > 5)
  {
    mySpringFrame->popUp();
    myDamperFrame->popUp();
    for (size_t i = 5; i < nToggles; i++)
      myToggles[i]->popUp();
  }
  else
  {
    mySpringFrame->popDown();
    myDamperFrame->popDown();
    for (size_t i = 5; i < nToggles; i++)
      myToggles[i]->popDown();
    nToggles = 5;
  }

  for (size_t i = 0; i < nToggles; i++)
    myToggles[i]->setValue(i < vals.size() ? vals[i] : false);
}


void FuiJointResults::getValues(std::vector<bool>& vals) const
{
  vals.clear();
  vals.reserve(myToggles.size());
  for (FFuToggleButton* toggle : myToggles)
    vals.push_back(toggle->getValue());
}
