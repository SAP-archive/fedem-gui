// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUAFONTSET_H
#define FFUAFONTSET_H

/*
    StandardFont   = FFuaFont( , , , );
    TextFieldFont  = FFuaFont( , , , );
    IconButtonFont = FFuaFont( , , , );
*/

#include "FFuLib/FFuAuxClasses/FFuaFont.H"

class FFuaFontSet
{
public:
  FFuaFont StandardFont;
  FFuaFont TextFieldFont;
  FFuaFont IconButtonFont;
};

#endif
