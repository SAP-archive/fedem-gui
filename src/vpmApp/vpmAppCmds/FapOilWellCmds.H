// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_OIL_WELL_CMDS_H
#define FAP_OIL_WELL_CMDS_H

#include <string>

#include "FapCmdsBase.H"

class FFlLinkHandler;
class FaVec3;


class FapOilWellCmds : public FapCmdsBase
{
public:
  static void createRiser(const std::string& fileName);
  static void createEvents(const std::string& fileName);
  static void createJacket(const FFlLinkHandler* jlink, const std::string& name,
			   const double* Morison, int IDoffset = 0);
  static void createPile(const std::string& fileName, const FaVec3& top,
			 double mudH, bool interconnectXY, bool doScale, int cyclic);
  static bool degradeSoilSprings(double wantedTime);

  static void createPipeSurface(const std::string& fileName);
  static void createPipeString(const std::string& fileName);
  static void createDrillString(const std::string& fileName);

  static void exportPipeWearData(const std::string& fileName,
				 double startPeriod, double endPeriod);
  static void getExportPipeWearSensitivity(bool& sensitivity);
};

#endif
