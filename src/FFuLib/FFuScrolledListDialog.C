// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuScrolledList.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuScrolledListDialog.H"

extern const char* info_xpm[];


//! Widget initialization
void FFuScrolledListDialog::init()
{
  myDialogButtons->setButtonLabel(FFuDialogButtons::LEFTBUTTON, "OK");
  myDialogButtons->setButtonLabel(FFuDialogButtons::MIDBUTTON, "Apply");
  myDialogButtons->setButtonLabel(FFuDialogButtons::RIGHTBUTTON, "Cancel");

  showNotes = false;
  labNotesImage->setPixMap(info_xpm);
  labNotesLabel->setLabel("<b>Notes</b>");
  labNotesText->setLabel("");
  labNotesImage->popDown();
  labNotesLabel->popDown();
  labNotesText->popDown();

  myDialogButtons->setButtonClickedCB(FFaDynCB1M(FFuScrolledListDialog,this,onDlgButtonClicked,int));
}


//! Widget placement
void FFuScrolledListDialog::placeWidgets(int width, int height)
{
  int notesSpace = 0;
  if (showNotes) notesSpace = 50;

  myItemSelector->setEdgeGeometry(10, width-10, 10, height - myDialogButtons->getHeightHint() - notesSpace);
  myDialogButtons->setEdgeGeometry(0, width,  height - myDialogButtons->getHeightHint(), height);

  int notesTop = height - myDialogButtons->getHeightHint() - notesSpace + 10;
  labNotesImage->setEdgeGeometry(10,  26,       notesTop,    notesTop+16);
  labNotesLabel->setEdgeGeometry(30,  width-10, notesTop,    notesTop+16);
  labNotesText->setEdgeGeometry( 10,  width-10, notesTop+19, notesTop+19+16);
}


//! Returns the current item
int FFuScrolledListDialog::getItem() const
{
  return myItemSelector->getSelectedItemIndex();
}


void FFuScrolledListDialog::setOkButtonClickedCB(const FFaDynCB1<int>& aDynCB)
{
  myOkButtonClickedCB = aDynCB;
}

void FFuScrolledListDialog::setOkButtonClickedCB(const FFaDynCB2<int,FFuComponentBase*>& aDynCB)
{
  myOkButtonClickedWPtrCB = aDynCB;
}


void FFuScrolledListDialog::setCancelButtonClickedCB(const FFaDynCB1<int>& aDynCB)
{
  myCancelButtonClickedCB = aDynCB;
}

void FFuScrolledListDialog::setCancelButtonClickedCB(const FFaDynCB2<int,FFuComponentBase*>& aDynCB)
{
  myCancelButtonClickedWPtrCB = aDynCB;
}


void FFuScrolledListDialog::setApplyButtonClickedCB(const FFaDynCB1<int>& aDynCB)
{
  myApplyButtonClickedCB = aDynCB;
}

void FFuScrolledListDialog::setApplyButtonClickedCB(const FFaDynCB2<int,FFuComponentBase*>& aDynCB)
{
  myApplyButtonClickedWPtrCB = aDynCB;
}


void FFuScrolledListDialog::callOkButtonClickedCB()
{
  myOkButtonClickedCB.invoke(myItemSelector->getSelectedItemIndex());
  myOkButtonClickedWPtrCB.invoke(myItemSelector->getSelectedItemIndex(),this);
}

void FFuScrolledListDialog::callCancelButtonClickedCB()
{
  myCancelButtonClickedCB.invoke(myItemSelector->getSelectedItemIndex());
  myCancelButtonClickedWPtrCB.invoke(myItemSelector->getSelectedItemIndex(),this);
}

void FFuScrolledListDialog::callApplyButtonClickedCB()
{
  myApplyButtonClickedCB.invoke(myItemSelector->getSelectedItemIndex());
  myApplyButtonClickedWPtrCB.invoke(myItemSelector->getSelectedItemIndex(),this);
}

void FFuScrolledListDialog::onDlgButtonClicked(int val)
{
  switch (val)
    {
    case FFuDialogButtons::LEFTBUTTON:
      callOkButtonClickedCB();
      break;
    case FFuDialogButtons::MIDBUTTON:
      callApplyButtonClickedCB();
      break;
    case FFuDialogButtons::RIGHTBUTTON:
      callCancelButtonClickedCB();
      break;
    default:
      break;
    }
}
