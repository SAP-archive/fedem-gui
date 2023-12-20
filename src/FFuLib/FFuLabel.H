// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_LABEL_H
#define FFU_LABEL_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


class FFuLabel : virtual public FFuComponentBase
{
public:
  FFuLabel() {}
  virtual ~FFuLabel() {}

  // Methods to set what to show :

  virtual void setPixMap(const char** pixmap, bool stretch = false) = 0;
  virtual void setLabel(const char* label) = 0;

  void setLabel(const std::string& label) { this->setLabel(label.c_str()); }

  // Get the text of the label :

  virtual std::string getLabel() const = 0;

  // Sets callbacks :

  void setLinkActivatedCB(const FFaDynCB1<const std::string&>& cb) { myLinkActivatedCB = cb; }

protected:
  FFaDynCB1<const std::string&> myLinkActivatedCB;
};

#endif
