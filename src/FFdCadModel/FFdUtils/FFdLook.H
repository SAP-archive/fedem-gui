// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFD_LOOK_H
#define FFD_LOOK_H

#include <array>

typedef std::array<float,3> FdColor;


struct FFdLook
{
  FFdLook() :
    diffuseColor({0.5f,0.5f,0.5f}),
    ambientColor({0.0f,0.0f,0.0f}),
    specularColor({1.0f,1.0f,1.0f}),
    emissiveColor({0.0f,0.0f,0.0f}),
    transparency(0.0f), shininess(1.0f),
    isDefined(false) {}

  FFdLook(const FdColor& c, float amb = 0.0f) :
    diffuseColor(c),
    ambientColor({c[0]*amb,c[1]*amb,c[2]*amb}),
    specularColor({1.0f,1.0f,1.0f}),
    emissiveColor({0.0f,0.0f,0.0f}),
    transparency(0.0f), shininess(1.0f),
    isDefined(false) {}

  FdColor diffuseColor;
  FdColor ambientColor;
  FdColor specularColor;
  FdColor emissiveColor;
  float   transparency;
  float   shininess;
  bool    isDefined;

  bool operator==(const FFdLook& look) const
  {
    return (transparency  == look.transparency  &&
            shininess     == look.shininess     &&
            diffuseColor  == look.diffuseColor  &&
            ambientColor  == look.ambientColor  &&
            specularColor == look.specularColor &&
            emissiveColor == look.emissiveColor);
  }

  bool operator!=(const FFdLook& look) const { return !(*this == look); }

  FFdLook& operator+=(const FFdLook& look)
  {
    for (int i = 0; i < 3; i++)
    {
      diffuseColor[i]  += look.diffuseColor[i];
      ambientColor[i]  += look.ambientColor[i];
      specularColor[i] += look.specularColor[i];
      emissiveColor[i] += look.emissiveColor[i];
    }
    transparency += look.transparency;
    shininess    += look.shininess;
    return *this;
  }

  FFdLook& operator*=(float scale)
  {
    for (int i = 0; i < 3; i++)
    {
      diffuseColor[i]  *= scale;
      ambientColor[i]  *= scale;
      specularColor[i] *= scale;
      emissiveColor[i] *= scale;
    }
    transparency *= scale;
    shininess    *= scale;
    return *this;
  }
};

#endif
