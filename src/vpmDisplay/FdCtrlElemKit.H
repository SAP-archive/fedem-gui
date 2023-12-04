// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * CLASS: FdCtrlElemKit
 * AUTHOR: Magnus Svanberg
 * LAST MODIFIED: 22 aug 1997
 *
 * DESCRIPTION
 * FdCtrlElemKit, a node kit, which is a simple grouping of properties.
 *
 * USAGE
 * To describe a general control element symbol.
 ******************************************************************************/

#ifndef FD_CTRL_ELEM_KIT_H
#define FD_CTRL_ELEM_KIT_H

#include <Inventor/nodekits/SoBaseKit.h>

#include <string>

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class FdCtrlElemKit : public SoBaseKit
{
  SO_KIT_HEADER(FdCtrlElemKit);

  // Defines fields for the new parts in the catalog

  SO_KIT_CATALOG_ENTRY_HEADER(elemSep);
  SO_KIT_CATALOG_ENTRY_HEADER(appearance);
  SO_KIT_CATALOG_ENTRY_HEADER(elemTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(body);
  SO_KIT_CATALOG_ENTRY_HEADER(textRotation);
  SO_KIT_CATALOG_ENTRY_HEADER(textSep);
  SO_KIT_CATALOG_ENTRY_HEADER(textTrans);
  SO_KIT_CATALOG_ENTRY_HEADER(textFont);
  SO_KIT_CATALOG_ENTRY_HEADER(text);
  SO_KIT_CATALOG_ENTRY_HEADER(moreText);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

public:
  FdCtrlElemKit();
  static void init();

  virtual SbBool affectsState() const { return FALSE; }

  void* addText(const std::string& text, float x, float y,
                const std::string& justification,
                const std::string& fontname,
                float size, bool is3DText = true);
  void removeText(void* id);

private:
  virtual ~FdCtrlElemKit() {}
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
