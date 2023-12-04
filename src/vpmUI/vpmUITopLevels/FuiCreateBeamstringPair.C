// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiCreateBeamstringPair.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "vpmUI/Fui.H"
#include "vpmUI/Pixmaps/beamstringPair.xpm"

extern const char* info_xpm[];

#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuToggleButton.H"


Fmd_SOURCE_INIT(FUI_CREATEBEAMSTRINGPAIR,FuiCreateBeamstringPair,FFuTopLevelShell);

//----------------------------------------------------------------------------

FuiCreateBeamstringPair::FuiCreateBeamstringPair()
{
  Fmd_CONSTRUCTOR_INIT(FuiCreateBeamstringPair);
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::setSensitivity(bool isSensitive)
{
  this->createButton->setSensitivity(isSensitive);
  this->eraseButton->setSensitivity(isSensitive);
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::initWidgets()
{
  this->headerImage->setPixMap(beamstringPair_xpm);

  this->beamstringLabel1->setLabel("First beamstring");
  this->beamstringMenu1->setBehaviour(FuiQueryInputField::REF_NONE);
  this->beamstringMenu1->setButtonMeaning(FuiQueryInputField::EDIT);
  this->beamstringMenu1->turnButtonOff(true);

  this->beamstringLabel2->setLabel("Second beamstring");
  this->beamstringMenu2->setBehaviour(FuiQueryInputField::REF_NONE);
  this->beamstringMenu2->setButtonMeaning(FuiQueryInputField::EDIT);
  this->beamstringMenu2->turnButtonOff(true);

  this->stiffnessFunctionLabel->setLabel("Contact stiffness function");
  this->stiffnessFunctionMenu->setBehaviour(FuiQueryInputField::REF_NONE);
  this->stiffnessFunctionMenu->setButtonMeaning(FuiQueryInputField::EDIT);
  this->stiffnessFunctionMenu->turnButtonOff(true);

  this->useRadialSpringsToggle->setLabel("Use radial springs");

  this->notesImage->setPixMap(info_xpm);
  this->notesLabel->setLabel("<b>Notes</b>");
  this->notesText->setLabel(
    "The Beamstring Pair Definition tool is used to generate Free Joints between the triads of a beamstring pair.\n"
    "The primary purpose of this approach is to simulate that the inner pipe hits the outer pipe, and then the\n"
    "inner pipe will bounce back. The Contact stiffness function provides the magnitude of the contact spring\n"
    "that is applied on all joints. The Use radial springs check box indicates whether radial springs are to be used.");
  this->placeWidgets(this->getWidth(),this->getHeight());

  this->createButton->setLabel("Generate Free Joints");
  this->eraseButton->setLabel("Erase Free Joints");
  this->closeButton->setLabel("Close");
  this->helpButton->setLabel("Help");
  this->createButton->setActivateCB(FFaDynCB0M(FuiCreateBeamstringPair,this,onCreateButtonClicked));
  this->eraseButton->setActivateCB(FFaDynCB0M(FuiCreateBeamstringPair,this,onEraseButtonClicked));
  this->closeButton->setActivateCB(FFaDynCB0M(FFuComponentBase,this,popDown));
  this->helpButton->setActivateCB(FFaDynCB0M(FuiCreateBeamstringPair,this,onHelpButtonClicked));

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::placeWidgets(int, int)
{
  int border = this->getBorder();

  int fontHeight = this->getFontHeigth();
  int fieldHeight = 20; // hard coded field height?!

  int v1 = border;
  int y  = border + 140;
  int x  = v1;

  // top image

  this->headerImage->setEdgeGeometry(0, 827, 0, 129);

  // geometry

  beamstringLabel1->setEdgeGeometry(x, x+250, y, y+fontHeight);
  x += 270;
  beamstringLabel2->setEdgeGeometry(x, x+250, y, y+fontHeight);
  x += 270;
  stiffnessFunctionLabel->setEdgeGeometry(x, x+250, y, y+fontHeight);
  y += fontHeight+2;

  x = v1;
  beamstringMenu1->setEdgeGeometry(x, x+250, y, y+fieldHeight);
  x += 270;
  beamstringMenu2->setEdgeGeometry(x, x+250, y, y+fieldHeight);
  x += 270;
  stiffnessFunctionMenu->setEdgeGeometry(x, x+250, y, y+fieldHeight);
  y += fieldHeight+2;

  useRadialSpringsToggle->setEdgeGeometry(x, x+250, y, y+fieldHeight);

  // notes

  y += 30;
  this->notesImage->setEdgeGeometry(v1, v1+16, y-5, y+11);
  this->notesSeparator->setEdgeGeometry(v1+20, v1+520, y+10, y+13);
  this->notesLabel->setEdgeGeometry(v1+20, v1+520, y-5, y+11);
  this->notesText->setEdgeGeometry(v1, v1+520, y+12, y+70);

  // dialog buttons

  y += 90;
  this->buttonSeparator->setEdgeGeometry(v1, v1+520, y, y+3);

  y += 10;
  x = v1;
  this->createButton->setEdgeGeometry(x, x+140, y, y+fieldHeight);
  x += 160;
  this->eraseButton->setEdgeGeometry(x, x+140, y, y+fieldHeight);
  x += 160;
  this->closeButton->setEdgeGeometry(x, x+90, y, y+fieldHeight);
  x += 110;
  this->helpButton->setEdgeGeometry(x, x+90, y, y+fieldHeight);
}
//-----------------------------------------------------------------------------

void FuiCreateBeamstringPair::onPoppedUp()
{
  this->placeWidgets(this->getWidth(),this->getHeight());
  this->updateUIValues();
}
//----------------------------------------------------------------------------

bool FuiCreateBeamstringPair::onClose()
{
  this->popDown();
  return false;
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::onCreateButtonClicked()
{
  this->myCBs.createCB.invoke(beamstringMenu1->getSelectedRef(),
                              beamstringMenu2->getSelectedRef(),
                              stiffnessFunctionMenu->getSelectedRef(),
                              useRadialSpringsToggle->getValue());
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::onEraseButtonClicked()
{
  this->myCBs.deleteCB.invoke(beamstringMenu1->getSelectedRef(),
                              beamstringMenu2->getSelectedRef());
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::onHelpButtonClicked()
{
  Fui::showCHM("dialogbox/marine/beamstring-pair-definition.htm");
}
//----------------------------------------------------------------------------

FFuaUIValues* FuiCreateBeamstringPair::createValuesObject()
{
  return new FuaCreateBeamstringPairValues();
}
//----------------------------------------------------------------------------

void FuiCreateBeamstringPair::setUIValues(const FFuaUIValues* values)
{
  FuaCreateBeamstringPairValues* cbpValues = (FuaCreateBeamstringPairValues*) values;

  this->beamstringMenu1->setQuery(cbpValues->beamstringQuery1);
  this->beamstringMenu1->setSelectedRef(NULL);
  this->beamstringMenu2->setQuery(cbpValues->beamstringQuery2);
  this->beamstringMenu2->setSelectedRef(NULL);
  this->stiffnessFunctionMenu->setQuery(cbpValues->stiffnessFunctionQuery);
  this->stiffnessFunctionMenu->setSelectedRef(NULL);
  this->setSensitivity(cbpValues->isSensitive);
}
