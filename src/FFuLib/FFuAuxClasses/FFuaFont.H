// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_FONT_H
#define FFUA_FONT_H

#include <string>


struct FFuaFont
{
  FFuaFont(const std::string& family = "times", int size = 12,
	   bool bold = false, bool italic = false) : Family(family)
    {
      Size     = size;
      IsBold   = bold;
      IsItalic = italic;
    }

  std::string Family;
  int         Size;
  bool        IsBold;
  bool        IsItalic;
};

#endif
