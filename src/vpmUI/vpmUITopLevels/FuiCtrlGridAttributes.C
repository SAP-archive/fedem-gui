// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiCtrlGridAttributes.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuFrame.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuToggleButton.H"


void FuiCtrlGridAttributes::initWidgets()
{
  myGridToggleButton->setLabel("Grid On/Off");
  myGridToggleButton->setToggleCB(FFaDynCB1M(FuiCtrlGridAttributes,
					     this,onToggeled,bool));
  myGridSizeLabel->setLabel("Grid size");
  myGXLabel->setLabel("X");
  myGYLabel->setLabel("Y");
  myGXField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myGXField->setDoubleDisplayMode(FFuIOField::DECIMAL,2,1);
  myGXField->setAcceptedCB(FFaDynCB1M(FuiCtrlGridAttributes,
				      this,onDoubleChanged,double));

  myGYField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  myGYField->setDoubleDisplayMode(FFuIOField::DECIMAL,2,1);
  myGYField->setAcceptedCB(FFaDynCB1M(FuiCtrlGridAttributes,
				      this,onDoubleChanged,double));

  mySnapToggleButton->setLabel("Snap On/Off");
  mySnapToggleButton->setToggleCB(FFaDynCB1M(FuiCtrlGridAttributes,
					     this,onToggeled,bool));
  mySnapDistLabel->setLabel("Snap distance");
  mySXLabel->setLabel("X");
  mySYLabel->setLabel("Y");
  mySXField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  mySXField->setDoubleDisplayMode(FFuIOField::DECIMAL, 2, 1);
  mySXField->setAcceptedCB(FFaDynCB1M(FuiCtrlGridAttributes,
				      this,onDoubleChanged,double));
  mySYField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  mySYField->setDoubleDisplayMode(FFuIOField::DECIMAL, 2, 1);
  mySYField->setAcceptedCB(FFaDynCB1M(FuiCtrlGridAttributes,
				      this,onDoubleChanged,double));

  myCloseButton->setLabel("Close");
  myCloseButton->setActivateCB(FFaDynCB0M(FFuComponentBase,
					  this,popDown));
  this->setMinWidth(myGridToggleButton->getWidthHint() + 2*mySXLabel->getWidthHint());

  FFuUAExistenceHandler::invokeCreateUACB(this);
}


void FuiCtrlGridAttributes::placeWidgets(int width, int)
{
  int widthOfX = mySXLabel->getWidthHint();
  int textHeight = mySnapDistLabel->getHeightHint();
  int fieldHeight = myGXField->getHeightHint();

  int glv1 = getGridLinePos(width, 3*widthOfX/10, FROM_START);
  int glv2 = getGridLinePos(width,   widthOfX,    FROM_START);
  int glv3 = getGridLinePos(width, 2*widthOfX,    FROM_START);
  int glv4 = getGridLinePos(width, 4*widthOfX,    FROM_START);
  int glv6 = getGridLinePos(width,   widthOfX,    FROM_END);
  int glv7 = getGridLinePos(width, 3*widthOfX/10, FROM_END);

  // Separator
  int glh2  = 0;
  int glh3  = getGridLinePos(width, glh2  + 2*textHeight,   FROM_START);
  int glh4  = getGridLinePos(width, glh3  + 3*textHeight/2, FROM_START);
  int glh5  = getGridLinePos(width, glh4  +   fieldHeight,  FROM_START);
  int glh6  = getGridLinePos(width, glh5  +   textHeight/5, FROM_START);
  int glh7  = getGridLinePos(width, glh6  +   fieldHeight,  FROM_START);
  int glh71 = getGridLinePos(width, glh7  +   textHeight,   FROM_START);
   // Separator
  int glh8  = getGridLinePos(width, glh71 +   textHeight,   FROM_START);
  int glh9  = getGridLinePos(width, glh8  + 2*textHeight,   FROM_START);
  int glh10 = getGridLinePos(width, glh9  + 3*textHeight/2, FROM_START);
  int glh11 = getGridLinePos(width, glh10 +   fieldHeight,  FROM_START);
  int glh12 = getGridLinePos(width, glh11 +   textHeight/5, FROM_START);
  int glh13 = getGridLinePos(width, glh12 +   fieldHeight,  FROM_START);
  int glh131= getGridLinePos(width, glh13 +   textHeight,   FROM_START);
   // Separator
  int glh14 = getGridLinePos(width, glh131+   textHeight,   FROM_START);
  int glh15 = getGridLinePos(width, glh14 + 2*textHeight,   FROM_START);
  int totalHeight = glh15 + (textHeight/2);

  this->setMinHeight(totalHeight);
  this->setMaxHeight(totalHeight);

  myGridToggleButton ->setEdgeGeometry(glv2, glv6, glh2,  glh3);
  myGridSizeLabel    ->setEdgeGeometry(glv2, glv6, glh3,  glh4);
  myGXLabel          ->setEdgeGeometry(glv3, glv4, glh4,  glh5);
  myGYLabel          ->setEdgeGeometry(glv3, glv4, glh6,  glh7 );
  myGXField          ->setEdgeGeometry(glv4, glv6, glh4,  glh5);
  myGYField          ->setEdgeGeometry(glv4, glv6, glh6,  glh7);

  myGridSnapSeparator->setEdgeGeometry(glv1, glv7, glh71,  glh71+2);

  mySnapToggleButton ->setEdgeGeometry(glv2, glv6, glh8,  glh9);
  mySnapDistLabel    ->setEdgeGeometry(glv2, glv6, glh9,  glh10);
  mySXLabel          ->setEdgeGeometry(glv3, glv4, glh10, glh11);
  mySYLabel          ->setEdgeGeometry(glv3, glv4, glh12, glh13);
  mySXField          ->setEdgeGeometry(glv4, glv6, glh10, glh11);
  mySYField          ->setEdgeGeometry(glv4, glv6, glh12, glh13);

  myCloseSeparator   ->setEdgeGeometry(glv1, glv7, glh131, glh131+2);

  myCloseButton      ->setEdgeGeometry(glv2, glv2 + myCloseButton->getWidthHint(), glh14, glh15);
}


void FuiCtrlGridAttributes::setUIValues(const FFuaUIValues* vals)
{
  const FuaCtrlGridValues* newVals = static_cast<const FuaCtrlGridValues*>(vals);
  myGridToggleButton->setValue(newVals->gridOn);
  myGXField->setValue(newVals->gridXSpacing);
  myGYField->setValue(newVals->gridYSpacing);
  mySnapToggleButton->setValue(newVals->snapOn);
  mySXField->setValue(newVals->snapXSpacing);
  mySYField->setValue(newVals->snapYSpacing);
}


void FuiCtrlGridAttributes::onValuesChanged()
{
  FuaCtrlGridValues newVals;

  newVals.gridOn = myGridToggleButton->getValue();
  newVals.gridXSpacing = myGXField->getDouble();
  newVals.gridYSpacing = myGYField->getDouble();
  newVals.snapOn = mySnapToggleButton->getValue();
  newVals.snapXSpacing = mySXField->getDouble();
  newVals.snapYSpacing = mySYField->getDouble();

  this->invokeSetAndGetDBValuesCB(&newVals);
  this->setUIValues(&newVals);
}
