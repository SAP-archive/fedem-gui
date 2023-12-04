// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_CAD_INFO_H
#define FD_CAD_INFO_H

#include "FFaLib/FFaString/FFaEnum.H"
#include "FFaLib/FFaAlgebra/FFaVec3.H"


class FdCadEntityInfo
{
public:
  FdCadEntityInfo() : type(UNKNOWN) { myAxisIsValid = myOriginIsValid = false; }

  void setAxis(const FaVec3& axs) { axis = axs; myAxisIsValid = true; }
  void setOrigin(const FaVec3& o) { origin = o; myOriginIsValid = true; }

  enum EntityType {
    UNKNOWN,
    PLANE,
    CYLINDER,
    CONE,
    SPHERE,
    TORUS,
    SREV,
    LINE,
    CIRCLE,
    ELLIPSE
  };

  FFaEnumMapping(EntityType) {
    FFaEnumEntry(UNKNOWN, "UNKNOWN");
    FFaEnumEntry(PLANE,   "PLANE");
    FFaEnumEntry(CYLINDER,"CYLINDER");
    FFaEnumEntry(CONE,    "CONE");
    FFaEnumEntry(SPHERE,  "SPHERE");
    FFaEnumEntry(TORUS,   "TORUS");
    FFaEnumEntry(SREV,    "SREV");
    FFaEnumEntry(LINE,    "LINE");
    FFaEnumEntry(CIRCLE,  "CIRCLE");
    FFaEnumEntry(ELLIPSE, "ELLIPSE");
    FFaEnumEntryEnd;
  };

  FFaEnum<EntityType,EntityTypeMapping> type; //!< The type of the entity
  FaVec3 origin; //!< The origin of the axis, e.g., point on cylinder axis
  FaVec3 axis; //!< The axis direction of some meaning, e.g., direction of cylinder axis, or plane normal
  bool myAxisIsValid; //!< Tells if the axis is defined for this cad entity
  bool myOriginIsValid; //!< Tells if the origin is defined for this cad entity
};

#endif
