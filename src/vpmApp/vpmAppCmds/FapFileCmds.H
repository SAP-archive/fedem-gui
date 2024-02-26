// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_FILE_CMDS_H
#define FAP_FILE_CMDS_H

#include "FapCmdsBase.H"
#include "FFaLib/FFaPatterns/FFaInitialisation.H"


class FapFileCmds : public FapCmdsBase
{
private:
  static void init();
  static void getChangeLinkSensitivity(bool& isSensitive);
  static void getSetModelLinkRepSensitivity(bool& isSensitive);
  static void getChangeModelSensitivity(bool& isSensitive);

  static void importPipeSurface();
  static void importPipeString();
  static void importDrillString();
  static void importRiser();
  static void importJacket();
  static void importTurbine();
  static void importSoilPile();
  static void importAssembly();
  static void importEvents();

  static bool open(const std::string& fileName, bool loadParts);
  static void open(size_t recentFileIdx);

public:
  static void open();
  static void save() { FapFileCmds::save(true); }
  static void save(bool pruneEmptyDirs);
  static void saveAs();
  static void exit() { FapFileCmds::exit(true,true); }
  static void exit(bool saveOnBatchExit, bool pruneEmptyDirs, int status = 0);
  static void loadLink();
  static void changeLink();
  static void setExternalLinkRep() { FapFileCmds::setModelLinkRep(false); }
  static void setModelLinkRep(bool switchToInternal = false);
  static bool createEvents(const std::string& fileName);

private:
  friend class FFaInitialisation<FapFileCmds>;
};

static FFaInitialisation<FapFileCmds> FapFileCmds_Init;

#endif
