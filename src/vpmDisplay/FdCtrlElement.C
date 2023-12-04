// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/SbVec2f.h>

#include "vpmDB/FmCtrlLine.H"
#include "vpmDB/FmcElements.H"
#include "vpmDB/FmcInput.H"
#include "vpmDB/FmcOutput.H"

#include "vpmDisplay/FdCtrlKit.H"
#include "vpmDisplay/FdCtrlElemKit.H"
#include "vpmDisplay/FdCtrlSymbolKit.H"
#include "vpmDisplay/FdCtrlDB.H"
#include "vpmDisplay/FdCtrlElement.H"
#include "vpmDisplay/FdCtrlLine.H"
#include "vpmDisplay/FdCtrlSymDef.H"
#include "vpmDisplay/FdBackPointer.H"


//////////////////////////////////////////////////////////////////////////

Fmd_SOURCE_INIT(FDCTRLELEMENT,FdCtrlElement,FdCtrlObject);

FdCtrlElement::FdCtrlElement(FmCtrlElementBase* ptr)
{
  Fmd_CONSTRUCTOR_INIT(FdCtrlElement);

  itsFmOwner = ptr;

  itsKit = new FdCtrlElemKit;
  itsKit->ref();

  myDescriptionId = myInfoStringId = NULL;

  SO_GET_PART(itsKit,"backPt",FdBackPointer)->setPointer(this);
}


FdCtrlElement::~FdCtrlElement()
{
  this->fdDisconnect();
  itsKit->unref();
}


SoNodeKitListPart* FdCtrlElement::getListSw() const
{
  return SO_GET_PART(FdCtrlDB::getCtrlKit(),"elemList",SoNodeKitListPart);
}


bool FdCtrlElement::updateFdTopology(bool)
{
  return this->updateFdCS();
}


bool FdCtrlElement::updateFdCS()
{
  SoTransform* elemTrans = SO_GET_PART(itsKit,"elemTrans",SoTransform);
  elemTrans->translation.setValue(this->getElemTranslation());

  float newAngle = this->isElementLeftRotated() ? 3.14159265f : 0.0f;
  elemTrans->rotation.setValue(SbVec3f(0,1,0),newAngle);
  SoTransform* textTrans = SO_GET_PART(itsKit,"textRotation",SoTransform);
  textTrans->rotation.setValue(SbVec3f(0,1,0),-newAngle);

  return true;
}


//Class methods
////////////////////////////////////////////////////////////////////

bool FdCtrlElement::updateFdDetails()
{
  if (myDescriptionId)
    ((FdCtrlElemKit*)itsKit)->removeText(myDescriptionId);

  myDescriptionId = ((FdCtrlElemKit*)itsKit)->addText(itsFmOwner->getUserDescription(),
                                                      0.0f, -0.75f, "CENTER", "Utopia-Regular", 0.3f);

  if (itsFmOwner->isOfType(FmcInput::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::inputSym());			//Input symbol
  else if (itsFmOwner->isOfType(FmcOutput::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::outputSym());			//Output symbol
  else if (itsFmOwner->isOfType(FmcComparator::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::comparatorSym());		//Comparator symbol
  else if (itsFmOwner->isOfType(FmcAdder::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::adderSym());			//Adder symbol
  else if (itsFmOwner->isOfType(FmcMultiplier::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::multiplierSym());		//Multiplier symbol
  else if (itsFmOwner->isOfType(FmcAmplifier::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::amplifierSym()); 		//Amplifier e.g. Gain symbol
  else if (itsFmOwner->isOfType(FmcLimDerivator::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::limDerivatorSym()); 		//Derivator symbol
  else if (itsFmOwner->isOfType(FmcSampleHold::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::sampleHoldSym()); 		//SampleHold symbol
  else if (itsFmOwner->isOfType(FmcDeadZone::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::deadZoneSym()); 		//Derivator symbol
  else if (itsFmOwner->isOfType(FmcLogicalSwitch::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::logicalSwitchSym()); 		//LogicalSwitch symbol
  else if (itsFmOwner->isOfType(FmcHysteresis::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::hysteresisSym()); 		//Hysteresis symbol
  else if(itsFmOwner->isOfType(FmcLimitation::getClassTypeID()))
    itsKit->setPart("body", FdCtrlSymDef::limitationSym()); 		//Limitation symbol
  else {
    itsKit->setPart("body", FdCtrlSymDef::std2pSym());			//Standard 2-port symbol

    // Elements with text
    if (itsFmOwner->isOfType(FmcPower::getClassTypeID()))
      this->setElemText("Pow", 0.35f);
    else if (itsFmOwner->isOfType(FmcIntegrator::getClassTypeID()))
      this->setElemText("1/s", 0.5f);
    else if (itsFmOwner->isOfType(FmcTimeDelay::getClassTypeID()))
      this->setElemText("Delay", 0.35f);
    else if (itsFmOwner->isOfType(FmcPi::getClassTypeID()))
      this->setElemText("PI", 0.5f);
    else if (itsFmOwner->isOfType(FmcPlimI::getClassTypeID()))
      this->setElemText("PlI", 0.5f);
    else if (itsFmOwner->isOfType(FmcPd::getClassTypeID()))
      this->setElemText("PD", 0.5f);
    else if (itsFmOwner->isOfType(FmcPlimD::getClassTypeID()))
      this->setElemText("PlD", 0.5f);
    else if (itsFmOwner->isOfType(FmcPid::getClassTypeID()))
      this->setElemText("PID", 0.5f);
    else if (itsFmOwner->isOfType(FmcPIlimD::getClassTypeID()))
      this->setElemText("PIlD", 0.4f);
    else if (itsFmOwner->isOfType(FmcPlimIlimD::getClassTypeID()))
      this->setElemText("PlIlD", 0.3f);
    else if (itsFmOwner->isOfType(FmcRealPole::getClassTypeID()))
      this->setElemText("K/(1+Ts)", 0.25f);
    else if (itsFmOwner->isOfType(FmcCompConjPole::getClassTypeID()))
      this->setElemText("C.Pole", 0.25f);
    else if (itsFmOwner->isOfType(Fmc1ordTF::getClassTypeID()))
      this->setElemText("1'order", 0.25f);
    else if (itsFmOwner->isOfType(Fmc2ordTF::getClassTypeID()))
      this->setElemText("2'order", 0.25f);
    else
      this->setElemText("Fault", 0.3f);
  }

  return true;
}


void FdCtrlElement::setElemText(const char* name, float textSize)
{
  // Element text transform.

  SoTransform* textTrans = SO_GET_PART(itsKit,"textTrans",SoTransform);
  textTrans->translation.setValue(SbVec3f(0,-textSize*0.34f,0));

  // Element text font.

  SoFont* font = SO_GET_PART(itsKit,"textFont",SoFont);
  font->name.setValue("Utopia-Regular");
  font->size.setValue(textSize);

  // Element text.

  SoText3* elemText = SO_GET_PART(itsKit,"text",SoText3);
  elemText->justification.setValue("CENTER");
  elemText->string.setValue(name);
}


void FdCtrlElement::moveObject(const SbVec3f& newTransVec, bool single)
{
  ((FmCtrlElementBase*)itsFmOwner)->setPosition(newTransVec[0],newTransVec[1]);

  this->updateFdCS();

  ((FmCtrlElementBase*)itsFmOwner)->updateLines(single);
}


void FdCtrlElement::rotateObject()
{
  // This will rotate the element 180 degrees
  ((FmCtrlElementBase*)itsFmOwner)->flipRotation();

  this->updateFdAll();

  ((FmCtrlElementBase*)itsFmOwner)->updateLines(true);
} 


bool FdCtrlElement::isElementLeftRotated() const
{
  return (((FmCtrlElementBase*)itsFmOwner)->isLeftRotated());
}


SbVec3f FdCtrlElement::getElemTranslation() const
{
  const Vec2& position = ((FmCtrlElementBase*)itsFmOwner)->getPosition();
  return SbVec3f(position.x,position.y,0.0f);
}


void FdCtrlElement::getElementDetail(const SbVec3f& globalPoint,
                                     int& detailHit, int& portNumberHit)
{
  float verticalportSpacing = 0.25f;
  float portLength          = 0.25f;
  float portDistance        = 0.575f;

  SbVec3f objPoint = globalPoint - this->getElemTranslation();
  bool leftRotated = this->isElementLeftRotated();
  float x = leftRotated ? -objPoint[0] : objPoint[0];
  float y = leftRotated ? -objPoint[1] : objPoint[1];

  int nIn  = ((FmCtrlElementBase*)itsFmOwner)->getNumInputPorts();
  int nOut = ((FmCtrlElementBase*)itsFmOwner)->getNumOutputPorts();
  bool isTwoInPorts  = nIn  == 2;
  bool isTwoOutPorts = nOut == 2;
  if (isTwoInPorts)  nIn  = 3;
  if (isTwoOutPorts) nOut = 3;

  // Find what port layout to use :

  int isUnEvenInPorts  = nIn%2;
  int isUnEvenOutPorts = nOut%2;

  // Calculate normalized picked height position, being aware
  // that odd and even numbered ports starts differently

  float inPortPickedHeight  = y/verticalportSpacing - 0.5f*isUnEvenInPorts;
  float outPortPickedHeight = y/verticalportSpacing - 0.5f*isUnEvenOutPorts;

  // Making a shift to make int cast round downwards also for values below zero:

  int inIdxPos  = (int)(inPortPickedHeight  > 0 ? inPortPickedHeight  : inPortPickedHeight-1.0f);
  int outIdxPos = (int)(outPortPickedHeight > 0 ? outPortPickedHeight : outPortPickedHeight-1.0f);

  // Transforming to port number idxes remembering special 2 port case:

  int inPortPickedIdx  = inIdxPos - (2*inIdxPos - (nIn-isUnEvenInPorts)/2);
  int outPortPickedIdx = outIdxPos - (2*outIdxPos - (nOut-isUnEvenOutPorts)/2);
  inPortPickedIdx  = (isTwoInPorts && inPortPickedIdx == 3) ? 2 : inPortPickedIdx;
  outPortPickedIdx = (isTwoOutPorts && outPortPickedIdx == 3) ? 2 : outPortPickedIdx;

  // Transforming the width coord to coords within the snapping aera

  float inWidthCoord  = x + portDistance;
  float outWidthCoord = x - portDistance;

  if (-portLength/2 < inWidthCoord && inWidthCoord < portLength/2)
  {
    portNumberHit = inPortPickedIdx;
    detailHit = 0 < portNumberHit && portNumberHit <= nIn ? INPUT : NONE;
  }
  else if (-portLength/2 < outWidthCoord && outWidthCoord < portLength/2)
  {
    portNumberHit = outPortPickedIdx;
    detailHit = 0 < portNumberHit && portNumberHit <= nOut ? OUTPUT : NONE;
  }
  else if (-portLength/2 < inWidthCoord && outWidthCoord < -portLength/2)
    detailHit = BODY;
  else
    detailHit = NONE;
}
