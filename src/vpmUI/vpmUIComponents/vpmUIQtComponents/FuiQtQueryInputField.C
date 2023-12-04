// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"


FuiQtQueryInputField::FuiQtQueryInputField(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent,name)
{
  myOptions = new FFuQtOptionMenu(this);
  myButton  = new FFuQtPushButton(this);

  this->initWidgets();  
}


void FuiQtQueryInputField::setBehaviour(Policy behaviour)
{
  FFuQtIOField* iof;
  switch (behaviour)
    {
    case REF_NUMBER:
    case REF_TEXT:
      if (!myIOField)
      {
	myIOField = iof = new FFuQtIOField(this);
	iof->setFrame(false);
	iof->toFront();
      }
      break;

    default:
      if (myIOField)
      {
	delete myIOField;
	myIOField = 0;
      }
    }

  this->FuiQueryInputField::setBehaviour(behaviour);
}
