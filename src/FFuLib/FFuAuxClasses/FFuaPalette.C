// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuAuxClasses/FFuaPalette.H"

/*!
  \class FFuaPalette FFuaPalette.H
  \brief A class to contain a user interface Palette.

  Operates on 24-bit RGB color represenation (values 0-255).

  \author Jacob Storen
*/

FFuaPalette::FFuaPalette()
{
  setStdBackground         ( 150, 150, 150 );
  setFieldBackground       ( 225, 225, 225 );
  setTextOnStdBackground   (   0,   0,   0 );
  setTextOnFieldBackground (   0,   0,   0 );
  setIconText              ( 225, 225, 225 );
  setDarkShadow            (  50,  50,  50 );
  setMidShadow             ( 100, 100, 100 );
  setLightShadow           ( 200, 200, 200 );
}


////////////////////////////////////////////////////////////////////////
//
//  Internal clipping and converting routines :
//


static UColor clip24bit(int r, int g, int b)
{
  if (r > 255)
    r = 255;
  else if (r < 0)
    r = 0;

  if (g > 255)
    g = 255;
  else if (g < 0)
    g = 0;

  if (b > 255)
    b = 255;
  else if (b < 0)
    b = 0;

  return UColor({r,g,b});
}

static void get24bit(const UColor& color, int& r, int& g, int& b)
{
  r = color[0];
  g = color[1];
  b = color[2];
}


////////////////////////////////////////////////////////////////////////
//
// Implementation of the get and set methods are done trough a macro:
//

#define FFuaPALETTE_ENTRY_IMPLEMENTATION(PaletteEntry)			\
									\
void FFuaPalette::get##PaletteEntry(int& r, int& g, int& b) const {	\
  get24bit(this->PaletteEntry,r,g,b);					\
}									\
									\
void FFuaPalette::set##PaletteEntry(const UColor& color) {		\
  this->PaletteEntry = color;						\
}									\
									\
void FFuaPalette::set##PaletteEntry(int r, int g, int b) {		\
  this->PaletteEntry = clip24bit(r,g,b);				\
}

FFuaPALETTE_ENTRY_IMPLEMENTATION(StdBackground)
FFuaPALETTE_ENTRY_IMPLEMENTATION(FieldBackground)
FFuaPALETTE_ENTRY_IMPLEMENTATION(TextOnStdBackground)
FFuaPALETTE_ENTRY_IMPLEMENTATION(TextOnFieldBackground)
FFuaPALETTE_ENTRY_IMPLEMENTATION(IconText)
FFuaPALETTE_ENTRY_IMPLEMENTATION(DarkShadow)
FFuaPALETTE_ENTRY_IMPLEMENTATION(MidShadow)
FFuaPALETTE_ENTRY_IMPLEMENTATION(LightShadow)
