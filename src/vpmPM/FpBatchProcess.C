// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmPM/FpBatchProcess.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmDB.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppCmds/FapSolveCmds.H"
#include "vpmApp/vpmAppCmds/FapFileCmds.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFaLib/FFaCmdLineArg/FFaCmdLineArg.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaString/FFaTokenizer.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"
#include <fstream>


bool FpBatchProcess::userWantsBatch()
{
  return (FFaCmdLineArg::instance()->isOptionSetOnCmdLine("solve") ||
          FFaCmdLineArg::instance()->isOptionSetOnCmdLine("prepareBatch"));
}


bool FpBatchProcess::setupBatch()
{
  std::string answer;

  // Check for preparation for batch execution of solvers, i.e.,
  // the required directory structure, populated with the necessary
  // solver input files is created, but no solver processes are started.
  FFaCmdLineArg::instance()->getValue("prepareBatch",answer);
  FFaLowerCaseString preBatch(answer.substr(0,7));

  if (preBatch == "all")
    return FapSolveCmds::solveAll(true); // i.e., stress, modes, gage and fpp

  else if (preBatch == "reducer")
  {
    FapSolveCmds::prepareForBatchReduction();
    return false; // no batch processes to start
  }
  else if (preBatch == "dynamic")
  {
    FapSolveCmds::eraseSimuleRes();
    return FapSolveCmds::prepareForBatchSolving();
  }
  else if (preBatch == "stress")
    return FapSolveCmds::solveStress(true);

  else if (preBatch == "modes")
    return FapSolveCmds::solveModes(true);

  else if (preBatch == "straing")
    return FapSolveCmds::solveRosette(true);

  else if (preBatch == "strainc")
    return FapSolveCmds::solveStrainCoat(true);

  // Check for event definition file?
  answer.clear();
  FFaCmdLineArg::instance()->getValue("events",answer);
  if (!answer.empty() && FapLicenseManager::checkSimEventLicense())
  {
    FapSolveCmds::eraseEventRes();
    if (!FapFileCmds::createEvents(answer))
      return false;
  }

  // Check for batch execution of solvers?
  answer.clear();
  FFaCmdLineArg::instance()->getValue("solve",answer);
  if (answer.empty()) return false; // no batch processes to start

  FFaLowerCaseString solver(answer);
  if (solver.find("all") != std::string::npos)
    return FapSolveCmds::solveAll(false);

  else if (solver.find("event") != std::string::npos)
  {
    FapSolveCmds::eraseEventRes();
    FapSolveCmds::solveEvents();
    return true; // no need to do more
  }

  if (solver.find("reduc") != std::string::npos)
    FapSolveCmds::reduceAllParts();

  if (solver.find("dynamic") != std::string::npos)
  {
    FapSolveCmds::eraseSimuleRes();
    FapSolveCmds::solveDynamics();
  }

  if (solver.find("stress") != std::string::npos)
  {
    answer.clear();
    FFaCmdLineArg::instance()->getValue("timerange",answer);
    FFaTokenizer times(answer,'[',']');
    if (times.size() > 1)
    {
      // A time range was provided on the command-line.
      // Update the analysis parameters accordingly.
      FmAnalysis* anal = FmDB::getActiveAnalysis();
      anal->stressStartTime.setValue(atof(times[0].c_str()));
      anal->stressStopTime.setValue(atof(times[1].c_str()));
      if (times.size() > 2)
      {
        anal->stressTimeIncr.setValue(atof(times[2].c_str()));
        anal->stressAllTimeSteps.setValue(false);
      }
    }
    FapSolveCmds::solveStress(false);
  }

  if (solver.find("modes") != std::string::npos)
    FapSolveCmds::solveModes(false);

  if (solver.find("strainga") != std::string::npos)
    FapSolveCmds::solveRosette(false);

  if (solver.find("straincoat") != std::string::npos)
    FapSolveCmds::solveStrainCoat(false);

  return FapSolutionProcessManager::instance()->batchExit();
}
