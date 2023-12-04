// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQT3DPOINT_H
#define FUIQT3DPOINT_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/Fui3DPoint.H"


class FuiQt3DPoint : public virtual FFuQtMultUIComponent, public Fui3DPoint
{
public:
  FuiQt3DPoint(QWidget* parent = 0,
	       int xpos=100,
	       int ypos=100,
	       int width=40,
	       int height=60,
	       const char* name="D3Point",
	       bool refMenu=true);
  virtual ~FuiQt3DPoint() {}

  virtual void setSensitivity(bool sensitive)
  {Fui3DPoint::setSensitivity(sensitive);}
};

#endif
