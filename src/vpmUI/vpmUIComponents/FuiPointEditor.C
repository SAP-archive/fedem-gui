// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiPointEditor.H"
#include "vpmUI/vpmUIComponents/Fui3DPoint.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuPushButton.H"


void FuiPointEditor::initWidgets()
{
  myPointUI->setValue(0.0,0.0,0.0);
  myPointUI->setGlobal();

  myPickButton->setPixMap(mouseMedium_xpm);
  myViewPointButton->setPixMap(look_xpm);
  myApplyButton->setLabel("Apply");
  myApplyButton->setActivateCB(FFaDynCB0M(FuiPointEditor,this,onMyApplyButtonPressed));

  myViewWhatButton->setPixMap(look_xpm);
  myOnLabel->setLabel("On");
  myIdField->setSensitivity(false);

  myViewPointButton->setArmCB(FFaDynCB0M(FuiPointEditor,this,onMyViewPointTouched));
  myViewPointButton->setUnarmCB(FFaDynCB0M(FuiPointEditor,this,onMyViewPointTouched));

  myViewWhatButton->setArmCB(FFaDynCB0M(FuiPointEditor,this,onMyViewWhatTouched));
  myViewWhatButton->setUnarmCB(FFaDynCB0M(FuiPointEditor,this,onMyViewWhatTouched));
}

void FuiPointEditor::placeWidgets(int width, int height)
{
  int relBorder = 10;
  int relButtonHeight = 6 * relBorder;

  int onWhatCnt = IAmShowingOnWhat?1:0;

  int sum = (2+onWhatCnt)*relBorder + (3+onWhatCnt)*relButtonHeight;
  float error = (float)1000/sum;

  relBorder = (int)(error * relBorder);
  relButtonHeight = (int)(error * relButtonHeight);

  int glh1 = 0;
  int glh2 = getGridLinePos(height,    onWhatCnt *(relBorder+relButtonHeight) - relBorder );
  int glh3 = getGridLinePos(height,    onWhatCnt *(relBorder+relButtonHeight));
  int glh4 = getGridLinePos(height, (1+onWhatCnt)*(relBorder+relButtonHeight) - relBorder );
  int glh5 = getGridLinePos(height, (1+onWhatCnt)*(relBorder+relButtonHeight));
  int glh6 = getGridLinePos(height, (2+onWhatCnt)*(relBorder+relButtonHeight) - relBorder );
  int glh7 = getGridLinePos(height, (2+onWhatCnt)*(relBorder+relButtonHeight));
  int glh8 = height;

  int glv1 = 0;
  int glv2 = getGridLinePos(width,200);
  int glv3 = getGridLinePos(width,700);
  int glv4 = getGridLinePos(width,700+relBorder);
  int glv5 = width;

  myPointUI->        setEdgeGeometry(glv1,glv3,glh3,glh8);
  myPickButton->     setEdgeGeometry(glv4,glv5,glh3,glh4);
  myViewPointButton->setEdgeGeometry(glv4,glv5,glh5,glh6);
  myApplyButton->    setEdgeGeometry(glv4,glv5,glh7,glh8);

  if (IAmShowingOnWhat){
    myViewWhatButton-> setEdgeGeometry(glv4,glv5,glh1,glh2);
    myOnLabel->        setEdgeGeometry(glv1,glv2,glh1,glh2);
    myIdField->        setEdgeGeometry(glv2,glv3,glh1,glh2);
  }
}

void FuiPointEditor::hideOnWhatDisplay(bool doHide)
{
  if (IAmShowingOnWhat == doHide)
    {
      if(doHide)
        {
          myViewWhatButton-> popDown();
          myOnLabel->        popDown();
          myIdField->        popDown();
        }
      else
        {
          myViewWhatButton-> popUp();
          myOnLabel->        popUp();
          myIdField->        popUp();
        }

      IAmShowingOnWhat = !doHide;
      this->placeWidgets(this->getWidth(), this->getHeight());
    }
}

void FuiPointEditor::hideApplyButton(bool hide)
{
  if (hide)
    myApplyButton->popDown();
  else
    myApplyButton->popUp();
}

void FuiPointEditor::setSensitivity(bool isSensitive)
{
  myPointUI->setSensitivity(isSensitive);
  myPickButton->setSensitivity(isSensitive);
  myApplyButton->setSensitivity(isSensitive);
}


// Callbacks :

void FuiPointEditor::setViewWhatCB(const FFaDynCB1<bool> &aDynCB)
{
  myViewWhatCB = aDynCB;
}

void FuiPointEditor::setViewPointCB(const FFaDynCB1<bool> &aDynCB)
{
  myViewPointCB = aDynCB;
}

void FuiPointEditor::setPickCB(const FFaDynCB0 &aDynCB)
{
  myPickButton->setActivateCB(aDynCB);
}

void FuiPointEditor::setApplyCB(const FFaDynCB2<bool,FaVec3> &aDynCB)
{
  myApplyCB = aDynCB;
}

void FuiPointEditor::setPointChangedCB(const FFaDynCB2<const FaVec3&,bool>& aDynCB)
{
  myPointUI->setPointChangedCB(aDynCB);
}

void FuiPointEditor::setRefChangedCB(const FFaDynCB1<bool> &aDynCB)
{
  myPointUI->setRefChangedCB(aDynCB);
}

void FuiPointEditor::setOnWhatText(const std::string& text)
{
  myIdField->setValue(text);
}

void FuiPointEditor::setValue(const FaVec3& point)
{
  myPointUI->setValue(point);
}

FaVec3 FuiPointEditor::getValue() const
{
  return myPointUI->getValue();
}

bool FuiPointEditor::isGlobal() const
{
  return myPointUI->isGlobal();
}

void FuiPointEditor::setGlobal(bool isGlobal)
{
  if (isGlobal)
    myPointUI->setGlobal();
  else
    myPointUI->setLocal();
}

void FuiPointEditor::onMyViewWhatTouched()
{
  static bool buttonIn = false;
  buttonIn = !buttonIn;
  myViewWhatCB.invoke(buttonIn);
}

void FuiPointEditor::onMyViewPointTouched()
{
  static bool buttonIn = false;
  buttonIn = !buttonIn;
  myViewPointCB.invoke(buttonIn);
}

void FuiPointEditor::onMyApplyButtonPressed()
{
  myApplyCB.invoke(this->myPointUI->isGlobal(), this->myPointUI->getValue());
}
