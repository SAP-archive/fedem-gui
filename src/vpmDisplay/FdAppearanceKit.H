// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_APPEARANCE_KIT_H
#define FD_APPEARANCE_KIT_H

#include <Inventor/nodekits/SoBaseKit.h>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdAppearanceKit : public SoBaseKit
{
  SO_KIT_HEADER(FdAppearanceKit);
  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(style);
#ifdef USE_SMALLCHANGE
  SO_KIT_CATALOG_ENTRY_HEADER(depth);
#endif

public:
  FdAppearanceKit();

  SoINTERNAL public:
  static void init();

protected:
  virtual ~FdAppearanceKit() {}
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
