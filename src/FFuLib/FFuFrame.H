// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_FRAME_H
#define FFU_FRAME_H

#include "FFuLib/FFuBase/FFuComponentBase.H"


class FFuFrame : virtual public FFuComponentBase
{
public:
  FFuFrame() {}
  virtual ~FFuFrame() {}

  virtual void setLook(int look) = 0;
  virtual void setBorderWidth(int) = 0;

  enum
  {
    FLAT,
    PANEL_RAISED,
    PANEL_SUNKEN,
    BORDER_RAISED,
    BORDER_SUNKEN,
    BORDER_FLAT
  };
};

#endif
