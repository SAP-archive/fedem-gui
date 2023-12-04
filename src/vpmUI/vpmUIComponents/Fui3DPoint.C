// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/Fui3DPoint.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuFrame.H"


////////////////////////////////////////////////////////////////////////
//
// Initialisation to be called by UILib dep. subclass
//

void Fui3DPoint::init()
{
  this->myFrame->setLook(FFuFrame::PANEL_RAISED);
  this->myFrame->setBorderWidth(1);

  this->myXField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->myXField->setAcceptPolicy(FFuIOField::ENTERONLY);
  this->myXField->setDoubleDisplayMode(FFuIOField::AUTO);
  this->myXField->setAcceptedCB(FFaDynCB1M(Fui3DPoint,this,callPointChangedCB,double));

  this->myYField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->myYField->setAcceptPolicy(FFuIOField::ENTERONLY);
  this->myYField->setDoubleDisplayMode(FFuIOField::AUTO);
  this->myYField->setAcceptedCB(FFaDynCB1M(Fui3DPoint,this,callPointChangedCB,double));

  this->myZField->setInputCheckMode(FFuIOField::DOUBLECHECK);
  this->myZField->setAcceptPolicy(FFuIOField::ENTERONLY);
  this->myZField->setDoubleDisplayMode(FFuIOField::AUTO);
  this->myZField->setAcceptedCB(FFaDynCB1M(Fui3DPoint,this,callPointChangedCB,double));

  this->myZLabel->setLabel("Z");
  this->myYLabel->setLabel("Y");
  this->myXLabel->setLabel("X");

  if (!this->myRefMenu) return;

  this->myRefLabel->setLabel("Reference");
  this->myRefMenu->addOption("Global");
  this->myRefMenu->addOption("Local");
  this->myRefMenu->setOptionSelectedCB(FFaDynCB1M(Fui3DPoint,this,callRefChangedCB,int));
}


////////////////////////////////////////////////////////////////////////
//
//  Geometry management :
//

void Fui3DPoint::placeWidgets(int width, int height)
{
  // Horisontal GridLines :

  int glH1  = FFuMultUIComponent::getGridLinePos(height,  40);
  int glH2  = FFuMultUIComponent::getGridLinePos(height, 240);
  int glH3  = FFuMultUIComponent::getGridLinePos(height, 280);
  int glH4  = FFuMultUIComponent::getGridLinePos(height, 506);
  int glH5  = FFuMultUIComponent::getGridLinePos(height, 733);
  int glH6  = FFuMultUIComponent::getGridLinePos(height, 960);
  if (!this->myRefMenu) {
    glH3 = glH1;
    glH4 = FFuMultUIComponent::getGridLinePos(height, 347);
    glH5 = FFuMultUIComponent::getGridLinePos(height, 653);
  }

  // Vertical GridLines :

  int glV1  = FFuMultUIComponent::getGridLinePos(width,  40);
  int glV2  = FFuMultUIComponent::getGridLinePos(width,  200);
  int glV3  = FFuMultUIComponent::getGridLinePos(width,  500);
  int glV4  = FFuMultUIComponent::getGridLinePos(width,  960);

  // Setting geometry :

  this->myFrame->setEdgeGeometry   (0   ,width,   0 ,height);

  this->myXLabel->setEdgeGeometry  (glV1, glV2, glH3, glH4 );
  this->myYLabel->setEdgeGeometry  (glV1, glV2, glH4, glH5 );
  this->myZLabel->setEdgeGeometry  (glV1, glV2, glH5, glH6 );

  this->myXField->setEdgeGeometry  (glV2, glV4 ,glH3 ,glH4 );
  this->myYField->setEdgeGeometry  (glV2, glV4 ,glH4 ,glH5 );
  this->myZField->setEdgeGeometry  (glV2, glV4 ,glH5 ,glH6 );

  if (!this->myRefMenu) return;

  this->myRefLabel->setEdgeGeometry(glV1, glV3, glH1, glH2);
  this->myRefMenu->setEdgeGeometry (glV3, glV4, glH1, glH2);
}


void Fui3DPoint::setSensitivity(bool sensitive)
{
  this->myZField->setSensitivity(sensitive);
  this->myYField->setSensitivity(sensitive);
  this->myXField->setSensitivity(sensitive);
}

void Fui3DPoint::setLook(int look)
{
  myFrame->setLook(look);
}

void Fui3DPoint::setBorderWidth(int width)
{
  myFrame->setBorderWidth(width);
}


////////////////////////////////////////////////////////////////////////
//
// Setting and getting coordinate values
//

void Fui3DPoint::setXvalue(double value)
{
  this->myXField->setValue(value);
}

void Fui3DPoint::setYvalue(double value)
{
  this->myYField->setValue(value);
}

void Fui3DPoint::setZvalue(double value)
{
  this->myZField->setValue(value);
}

void Fui3DPoint::setValue(const FaVec3& point)
{
  this->myXField->setValue(point[0]);
  this->myYField->setValue(point[1]);
  this->myZField->setValue(point[2]);
}

void Fui3DPoint::setValue(double x, double y, double z)
{
  this->myXField->setValue(x);
  this->myYField->setValue(y);
  this->myZField->setValue(z);
}


double Fui3DPoint::getXvalue() const
{
  return this->myXField->getDouble();
}

double Fui3DPoint::getYvalue() const
{
  return this->myYField->getDouble();
}

double Fui3DPoint::getZvalue() const
{
  return this->myZField->getDouble();
}

FaVec3 Fui3DPoint::getValue() const
{
  return FaVec3(this->myXField->getDouble(),
		this->myYField->getDouble(),
		this->myZField->getDouble());
}


////////////////////////////////////////////////////////////////////////
//
// Setting and getting coordinate references
//

void Fui3DPoint::setGlobal()
{
  if (!this->myRefMenu) return;

  this->myRefMenu->selectOption(0);
}

void Fui3DPoint::setGlobalOnly()
{
  if (!this->myRefMenu) return;

  this->myRefMenu->selectOption(0);
  this->myRefMenu->setSensitivity(false);
}

void Fui3DPoint::setLocal()
{
  if (!this->myRefMenu) return;

  this->myRefMenu->selectOption(1);
  this->myRefMenu->setSensitivity(true);
}

void Fui3DPoint::enableLocal()
{
  if (!this->myRefMenu) return;

  this->myRefMenu->setSensitivity(true);
}

bool Fui3DPoint::isGlobal() const
{
  if (!this->myRefMenu) return true;

  return !this->myRefMenu->getSelectedOption();
}


/*!
  Callback to notify new coords and isGlobal()
*/

void Fui3DPoint::setPointChangedCB(const FFaDynCB2<const FaVec3&,bool>& aDynCB)
{
  this->myPointChangedCB = aDynCB;
}


/*!
  Callback to notify when ref changed. Called with isGlobal()
*/

void Fui3DPoint::setRefChangedCB(const FFaDynCB1<bool>& aDynCB)
{
  this->myRefChangedCB = aDynCB;
}


/*!
  Internal Callbacks
*/

void Fui3DPoint::callPointChangedCB(double)
{
  this->myPointChangedCB.invoke(this->getValue(),this->isGlobal());
}

void Fui3DPoint::callRefChangedCB(int)
{
  this->myRefChangedCB.invoke(this->isGlobal());
}
