// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiJointTabAdvanced.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuLabel.H"


void FuiJointTabAdvanced::initWidgets()
{
  this->showRotFormulation(false);
  this->showSpringCpl(false);
}


void FuiJointTabAdvanced::showRotFormulation(bool yesOrNo)
{
  IAmShowingRotFormulation = yesOrNo;
  if (yesOrNo){
    myRotFormulationFrame->popUp();
    myRotFormulationMenu->popUp();
    myRotFormulationLabel->popUp();
    myRotSequenceMenu->popUp();
    myRotSequenceLabel->popUp();
    myRotExplainLabel->popUp();}
  else{
    myRotFormulationFrame->popDown();
    myRotFormulationMenu->popDown();
    myRotFormulationLabel->popDown();
    myRotSequenceMenu->popDown();
    myRotSequenceLabel->popDown();
    myRotExplainLabel->popDown();}
}


void FuiJointTabAdvanced::showSpringCpl(bool yesOrNo)
{
  IAmShowingSpringCpl = yesOrNo ? 2 : 0;
  if (yesOrNo){
    mySpringCplFrame->popUp();
    myTranSpringCplMenu->popUp();
    myTranSpringCplLabel->popUp();
    myRotSpringCplMenu->popUp();
    myRotSpringCplLabel->popUp();}
  else{
    mySpringCplFrame->popDown();
    myTranSpringCplMenu->popDown();
    myTranSpringCplLabel->popDown();
    myRotSpringCplMenu->popDown();
    myRotSpringCplLabel->popDown();}
}


void FuiJointTabAdvanced::showRotSpringCpl()
{
  IAmShowingSpringCpl = 1;
  mySpringCplFrame->popUp();
  myTranSpringCplMenu->popDown();
  myTranSpringCplLabel->popDown();
  myRotSpringCplMenu->popUp();
  myRotSpringCplLabel->popUp();
}


void FuiJointTabAdvanced::placeWidgets(int width, int height)
{
  int fontHeight = this->getFontHeigth();
  int fontWidth = this->getFontWidth("  Ry ");

  int numLines = 8;
  if (numLines*fontHeight > height)
    fontHeight = height/numLines;

  int curHL = 4;
  int curHR = curHL;
  int frameTop = curHL;
  int frameBot = curHL + fontHeight*15/2;

  if (IAmShowingRotFormulation) {
    int frameLeft  = fontWidth*3/10;
    int frameRight = width*2/3 - fontWidth*3/20;
    int labelLeft  = frameLeft + fontWidth*3/10;
    int labelW     = this->getFontWidth("Formulation ");
    int menuLeft   = labelLeft + labelW;
    int menuW      = frameRight - menuLeft - fontWidth/5;
    myRotFormulationFrame->setEdgeGeometry(frameLeft, frameRight, frameTop, frameBot);
    curHL += fontHeight * 2;
    myRotFormulationLabel->setCenterYGeometry(labelLeft, curHL, labelW, fontHeight*3/2);
    myRotFormulationMenu->setCenterYGeometry(menuLeft, curHL, menuW, fontHeight*3/2);
    curHL += fontHeight * 2;
    myRotSequenceLabel->setCenterYGeometry(labelLeft, curHL, labelW, fontHeight*3/2);
    myRotSequenceMenu->setCenterYGeometry(menuLeft, curHL, menuW, fontHeight*3/2);
    curHL += fontHeight * 2;
    myRotExplainLabel->setCenterYGeometry(labelLeft, curHL, frameRight-labelLeft-fontWidth/5, fontHeight*3/2);
  }

  if (IAmShowingSpringCpl) {
    int frameLeft  = width*2/3 + fontWidth*3/20;
    int frameRight = width     - fontWidth*3/10;
    int labelLeft  = frameLeft + fontWidth*3/10;
    int labelW     = this->getFontWidth("Translation ");
    int menuLeft   = labelLeft + labelW;
    int menuW      = frameRight - menuLeft - fontWidth/5;
    mySpringCplFrame->setEdgeGeometry(frameLeft, frameRight, frameTop, frameBot);

    if (IAmShowingSpringCpl == 2) {
      curHR += fontHeight * 2;
      myTranSpringCplLabel->setCenterYGeometry(labelLeft, curHR, labelW, fontHeight*3/2);
      myTranSpringCplMenu->setCenterYGeometry(menuLeft, curHR, menuW, fontHeight*3/2);
    }
    curHR += fontHeight * 2;
    myRotSpringCplLabel->setCenterYGeometry(labelLeft, curHR, labelW, fontHeight*3/2);
    myRotSpringCplMenu->setCenterYGeometry(menuLeft, curHR, menuW, fontHeight*3/2);
  }
}
