// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_LINK_VISUAL_CMDS_H
#define FAP_LINK_VISUAL_CMDS_H

#include "vpmApp/vpmAppCmds/FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapLinkVisualCmds : public FapCmdsBase
{
public:
  static void hideLinkSelection();
  static void showLinkSelection();
  static void showSubassemblySelection();
  static void hideSubassemblySelection();

private:
  static void getElmFaceHideShowSensitivity(bool& isSensitive);
  static void setSelectionDetail(int detailType);

  static void init();

  friend class FFaInitialisation<FapLinkVisualCmds>;
};

static FFaInitialisation<FapLinkVisualCmds> FapLinkVisualCmds_Init;

#endif
