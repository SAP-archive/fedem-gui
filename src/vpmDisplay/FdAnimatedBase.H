// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_ANIMATED_BASE_H
#define FD_ANIMATED_BASE_H

class FFaLegendMapper;


class FdAnimatedBase
{
public:
  FdAnimatedBase() {}
  virtual ~FdAnimatedBase() {}

  virtual void showLinkMotion(bool) {}
  virtual void showTriadMotion(bool) {}
  virtual void showDeformations(bool) {}
  virtual void setDeformationScale(double) {}
  virtual void showFringes(bool) {}
  virtual void setFringeLegendMapping(const FFaLegendMapper&) {}

  /*!
    Turn on whatewer needed to make the animated object
    look like it should while animating (or stepping).
  */
  virtual void initAnimation() = 0;

  /*!
    Do whats needed to show the frame with selected number.
  */
  virtual void selectAnimationFrame(size_t frameNr) = 0;

  /*!
    Do whats needed to turn off everything that should be turned
    off when not animating or stepping any more.
  */
  virtual void resetAnimation() = 0;

  /*!
    The animation data is not needed any more. Delete it.
  */
  virtual void deleteAnimationData() = 0;
};

#endif
