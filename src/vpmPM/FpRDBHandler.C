// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmPM/FpRDBHandler.H"
#include "vpmPM/FpRDBExtractorManager.H"
#include "vpmPM/FpModelRDBHandler.H"
#include "vpmApp/vpmAppCmds/FapAnimationCmds.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmDB/FmDB.H"
#include "FFuLib/FFuAuxClasses/FFuaTimer.H"
#include "FFrLib/FFrExtractor.H"
#include "FFaLib/FFaCmdLineArg/FFaCmdLineArg.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


FFuaTimer* FpRDBHandler::ourHeaderChangedTimer = NULL;
FFuaTimer* FpRDBHandler::ourDataChangedTimer = NULL;


void FpRDBHandler::onProcessGroupStarted(int groupId)
{
  if (groupId) startRDBChecking();
}


void FpRDBHandler::startRDBChecking()
{
#if FP_DEBUG > 2
  std::cout <<"FpRDBHandler::startRDBChecking()"<< std::endl;
#endif

  int deltaT = 500;
  FFaCmdLineArg::instance()->getValue("checkRDBinterval",deltaT);

  if (!ourDataChangedTimer)
    ourDataChangedTimer = FFuaTimer::create(FFaDynCB0S(checkForNewData));

  ourDataChangedTimer->start(deltaT);

  if (!ourHeaderChangedTimer)
    ourHeaderChangedTimer = FFuaTimer::create(FFaDynCB0S(checkForNewHeaders));

  ourHeaderChangedTimer->start(deltaT);

  FFaSwitchBoard::connect(FpRDBExtractorManager::instance(),
			  FpRDBExtractorManager::MODELEXTRACTOR_DATA_CHANGED,
			  FFaSlot1S(FapAnimationCmds,onModelExtrDataChanged,FFrExtractor*));

  FFaSwitchBoard::connect(FpRDBExtractorManager::instance(),
			  FpRDBExtractorManager::MODELEXTRACTOR_HEADER_CHANGED,
			  FFaSlot1S(FapAnimationCmds,onModelExtrHeaderChanged,FFrExtractor*));
}


void FpRDBHandler::stopRDBChecking()
{
#if FP_DEBUG > 2
  std::cout <<"FpRDBHandler::stopRDBChecking()"<< std::endl;
#endif

  FFaMsg::list("===> No more processes.\n");

  if (ourHeaderChangedTimer) {
    ourHeaderChangedTimer->stop();
    checkForNewHeaders();
  }

  if (ourDataChangedTimer) {
    ourDataChangedTimer->stop();
    checkForNewData();
  }

  FpModelRDBHandler::removeResFiles();

  FFaSwitchBoard::disConnect(FpRDBExtractorManager::instance(),
			     FpRDBExtractorManager::MODELEXTRACTOR_DATA_CHANGED,
			     FFaSlot1S(FapAnimationCmds,onModelExtrDataChanged,FFrExtractor*));

  FFaSwitchBoard::disConnect(FpRDBExtractorManager::instance(),
			     FpRDBExtractorManager::MODELEXTRACTOR_HEADER_CHANGED,
			     FFaSlot1S(FapAnimationCmds,onModelExtrHeaderChanged,FFrExtractor*));
}


void FpRDBHandler::checkForNewHeaders()
{
  // Check for new res-files also (for progress polling)
  FpModelRDBHandler::RDBSync(FapSimEventHandler::getActiveRSD(),
			     FmDB::getMechanismObject(),true,true);
  FapSolutionProcessManager::instance()->syncRunningProcesses();
}


void FpRDBHandler::checkForNewData()
{
  FFrExtractor* extr = FpRDBExtractorManager::instance()->getModelExtractor();
  if (extr) extr->doResultFilesUpdate();
}
