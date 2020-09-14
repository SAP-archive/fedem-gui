// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_STRAIN_COAT_CMDS_H
#define FAP_STRAIN_COAT_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"
#include <vector>

class FmElementGroupProxy;
class FmPart;


class FapStrainCoatCmds : public FapCmdsBase
{
public:
  static void makeFullStrainCoat();
  static void makeStrainCoatOnSelection();

  static int makeStrainCoat(bool autoCreate, FmPart* fmPart,
                            const std::vector<FmElementGroupProxy*>& groups);

private:
  static void init();

  static void getSensitivity(bool& isSensitive);
  static void getOnSelectionSensitivity(bool& isSensitive);

  static void makeStrainCoat(const std::vector<FmElementGroupProxy*>& groups,
                             bool showProgress = false);

  static void makeStrainCoat(const std::vector<FmPart*>& parts);
  static bool makeStrainCoat(FmPart* part, FmElementGroupProxy* group = NULL);

  static void addFatigueProps(FmPart* part);
  static void addFatigueProps(FmPart* part, FmElementGroupProxy* group);

  friend class FFaInitialisation<FapStrainCoatCmds>;
};

static FFaInitialisation<FapStrainCoatCmds> FapStrainCoatCmds_Init;

#endif
