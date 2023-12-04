// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_USER_DEFINED_ELEMENT_H
#define FD_USER_DEFINED_ELEMENT_H

#include "vpmDisplay/FdLink.H"

class FmUserDefinedElement;


class FdUserDefinedElement : public FdLink
{
  Fmd_HEADER_INIT();

public:
  FdUserDefinedElement(FmUserDefinedElement* elm);

  virtual bool updateFdDetails();
  virtual void updateSimplifiedViz();

protected:
  virtual void showHighlight();
  virtual void hideHighlight();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
