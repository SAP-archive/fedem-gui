// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_LABEL_FRAME_H
#define FFU_LABEL_FRAME_H

#include "FFuLib/FFuBase/FFuComponentBase.H"


class FFuLabelFrame : virtual public FFuComponentBase
{
public:
  FFuLabelFrame() {}
  virtual ~FFuLabelFrame() {}

  virtual void setLabel(const char* aLabel) = 0;
  virtual std::string getLabel() const = 0;
};

#endif
