// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_LABEL_KIT_H
#define FD_LABEL_KIT_H

#include <Inventor/nodekits/SoBaseKit.h>
#include "FFaLib/FFaAlgebra/FFaVec3.H"
#include <string>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdLabelKit : public SoBaseKit
{
public:
  FdLabelKit();
  FdLabelKit(const std::string& text, const FaVec3& position);
  FdLabelKit(const std::string& text, const FaVec3& position,
             const FaVec3& offset);

  static void init();

  void setText(const std::string& text);
  void setOffset(const FaVec3& offset);
  void setPosition(const FaVec3& point);
  void setTo3DText(bool yesOrNo);

protected:
  virtual ~FdLabelKit() {}

private:
  void buildKit();
  void updateTranslation();

  bool IAm3DText;
  FaVec3 myOffset;
  FaVec3 myPosition;

  // Node kit definitions :

  SO_KIT_HEADER(FdLabelKit);

public:
  SO_KIT_CATALOG_ENTRY_HEADER(separator);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
#ifdef USE_SMALLCHANGE
  SO_KIT_CATALOG_ENTRY_HEADER(depthBuffer);
#endif
  SO_KIT_CATALOG_ENTRY_HEADER(text2d);
  SO_KIT_CATALOG_ENTRY_HEADER(text3d);
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
