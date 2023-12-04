// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_PALETTE_H
#define FFUA_PALETTE_H

#include <array>

typedef std::array<int,3> UColor;


class FFuaPalette
{
public:
  FFuaPalette();

  // Get 24 bit color :

  UColor getStdBackground        () const { return StdBackground; }
  UColor getFieldBackground      () const { return FieldBackground; }
  UColor getTextOnStdBackground  () const { return TextOnStdBackground; }
  UColor getTextOnFieldBackground() const { return TextOnFieldBackground; }
  UColor getIconText             () const { return IconText; }
  UColor getDarkShadow           () const { return DarkShadow; }
  UColor getMidShadow            () const { return MidShadow; }
  UColor getLightShadow          () const { return LightShadow; }

  // Get 24 bit color, 0-255 on each component :

  void getStdBackground         (int& r, int& g, int& b) const;
  void getFieldBackground       (int& r, int& g, int& b) const;
  void getTextOnStdBackground   (int& r, int& g, int& b) const;
  void getTextOnFieldBackground (int& r, int& g, int& b) const;
  void getIconText              (int& r, int& g, int& b) const;
  void getDarkShadow            (int& r, int& g, int& b) const;
  void getMidShadow             (int& r, int& g, int& b) const;
  void getLightShadow           (int& r, int& g, int& b) const;

  // Set 24 bit color :

  void setStdBackground         (const UColor& color);
  void setFieldBackground       (const UColor& color);
  void setTextOnStdBackground   (const UColor& color);
  void setTextOnFieldBackground (const UColor& color);
  void setIconText              (const UColor& color);
  void setDarkShadow            (const UColor& color);
  void setMidShadow             (const UColor& color);
  void setLightShadow           (const UColor& color);

  // Set 24 bit color, 0-255 on each component :

  void setStdBackground         (int r, int g, int b);
  void setFieldBackground       (int r, int g, int b);
  void setTextOnStdBackground   (int r, int g, int b);
  void setTextOnFieldBackground (int r, int g, int b);
  void setIconText              (int r, int g, int b);
  void setDarkShadow            (int r, int g, int b);
  void setMidShadow             (int r, int g, int b);
  void setLightShadow           (int r, int g, int b);

private:
  UColor StdBackground;
  UColor FieldBackground;
  UColor TextOnStdBackground;
  UColor TextOnFieldBackground;
  UColor IconText;
  UColor DarkShadow;
  UColor MidShadow;
  UColor LightShadow;
};

#endif
