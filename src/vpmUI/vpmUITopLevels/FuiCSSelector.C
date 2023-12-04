// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiCSSelector.H"
#include "vpmUI/vpmUIComponents/FuiItemsListViews.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuPushButton.H"


Fmd_SOURCE_INIT(FcFUICSSELECTOR, FuiCSSelector, FFuTopLevelShell);


//----------------------------------------------------------------------------

FuiCSSelector::FuiCSSelector()
{
  Fmd_CONSTRUCTOR_INIT(FuiCSSelector);

  csLabel = matLabel = NULL;
  notesImage = notesLabel = notesText = NULL;
  importButton = closeButton = NULL;
}
//----------------------------------------------------------------------------

void FuiCSSelector::initWidgets()
{
  importButton->setActivateCB(FFaDynCB0M(FFaDynCB0,&importCB,invoke));
  closeButton->setActivateCB(FFaDynCB0M(FFuComponentBase,this,popDown));

  csLabel->setLabel("Beam cross sections");
  matLabel->setLabel("Materials");
  notesImage->setPixMap(info_xpm);
  notesLabel->setLabel("<b>Notes</b>");
  notesText->setLabel(
    "Select one or more cross sections and one material from the above,\n"
    "then press the \"Import\" button to create beam cross section objects.");

  importButton->setLabel("Import");
  closeButton->setLabel("Close");

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiCSSelector::placeWidgets(int width,int height)
{
  int border = this->getBorder();
  int labh   = csLabel->getHeightHint();
  int texth  = labh + border;

  int glbl = border;
  int glbr = width > border ? width-border : 0;

  int glh4 = height - 2*border - importButton->getHeightHint();
  int glh1 = border + texth/2;
  int glh2 = glh1 + (glh4-glh1-texth)*67/100;
  int glh3 = glh2 + texth;
  int glh5 = glh4 - 50;
  int glh6 = glh5 + 19;

  csLabel->setCenterYGeometrySizeHint( glbl,glh1-labh/2-border/4);
  matLabel->setCenterYGeometrySizeHint(glbl,glh3-labh/2-border/4);

  lvCS->setEdgeGeometry( glbl,glbr,glh1,glh2);
  lvMat->setEdgeGeometry(glbl,glbr,glh3,glh4-55);

  notesImage->setEdgeGeometry(glbl,    glbl+16, glh5, glh5+16);
  notesLabel->setEdgeGeometry(glbl+20, glbr,    glh5, glh5+16);
  notesText->setEdgeGeometry( glbl,    glbr,    glh6, glh6+39);

  importButton->setEdgeGeometry(glbl, glbl+importButton->getWidthHint(), glh4+border, height-border);
  closeButton->setEdgeGeometry (glbr-closeButton->getWidthHint(),  glbr, glh4+border, height-border);
}
