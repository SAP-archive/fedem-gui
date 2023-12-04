// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppProcess/FapLinkSolver.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"

#include "vpmDB/FmPart.H"
#include "vpmDB/FmTriad.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmFileSys.H"
#include "vpmDB/FmDB.H"

#include "FFaLib/FFaCmdLineArg/FFaOptionFileCreator.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"
#include "FFaLib/FFaOS/FFaFilePath.H"


/*! fedem_partsol options:
  -autoMassScale      Scale factor for auto-added masses
  -autoStiffMethod    Method for automatic stiffness computations
                      = 1: Use k = Min(diag(K)) * 0.1/<tolFactorize>
                      = 2: Use k = Mean(diag(K)) * <autoStiffScale>
                      = 3: Use k = Max(diag(K)) * <autoStiffScale>
  -autoStiffScale     Scale factor for auto-added springs
  -bufsize_rigid      Buffer size (in DP-words) per rigid element
                      <= 0: Use conservative estimate computed internally
  -cachesize          Cache size (KB) to be used by the SPR solver
  -consolemsg         Output error messages to console
  -cwd                Change working directory
  -datacheck          Do data check only (exiting after data input)
  -debug              Debug print switch
  -denseSolver        Use LAPACK dense matrix equation solver
  -drillingStiff      Fictitious drilling DOF stiffness
  -eigenshift         Shift value for eigenvalue analysis
                      (target frequency for generalized DOFs)
  -extNodes           List of external nodes
                      (in addition to those specified in the part file)
  -factorMass         Factorize mass matrix in the eigenvalue solver
  -fao                Read additional options from this file
  -fco                Read calculation options from this file
  -fop                Read output options from this file
  -frsfile            Name of results database file
  -ftlout             Name of part output file in FTL-format
  -gsfSolver          Use the GSF equation solver
                      = 0: Use SPR for both stiffness and mass matrix
                      = 1: Use GSF for stiffness matrix, and SPR for mass
                      = 2: Use GSF for both stiffness and mass matrix
  -gvec               Gravity vector in global coordinates
  -help               Print out this help text
  -licenseinfo        Print out license information at startup
  -licensepath        License file directory
  -linkId             Part base-ID number
  -linkfile           Name of part input file (must be specified)
  -lumpedmass         Use lumped element mass matrices
  -neval              Number of eigenvalues/eigenvectors to compute
  -ngen               Number of generalized modes
  -rdbinc             Increment number for the results database files
  -resfile            Name of result output file
  -samfile            Name of SAM data file
  -singularityHandler Option on how to treat singular matrices
                      = 0: Abort on all occurring singularities
                      = 1: Suppress true zero pivots,
                           abort on reduced-to-zero pivots
                      > 1: Suppress all occurring singularities of any kind
  -skylineSolver      Use the skyline equation solver
  -terminal           File unit number for terminal output
  -tolEigval          Max acceptable relative error in eigenvalues
  -tolFactorize       Equation solver singularity criterion
                      (smaller values are less restrictive)
                      The lowest value allowed is 1e-20
  -tolWAVGM           Geometric tolerance for WAVGM elements
  -version            Print out program version
*/


FapLinkSolver::FapLinkSolver(FmPart* aPart) : FapRecoveryBase(aPart)
{
  mySolverName = "fedem_partsol";
  mySubTask = "timehist_rcy";
  myGroupID = FapSolverID::FAP_STRESS;
}


int FapLinkSolver::checkDependencies() const
{
#ifdef FAP_DEBUG
  std::cout <<"FapLinkSolver::checkDependencies()"<< std::endl;
#endif

  if (myWorkPart->useGenericProperties.getValue())
    return FAP_NOT_EXECUTABLE;
  else if (myWorkPart->suppressInSolver.getValue())
    return FAP_NOT_EXECUTABLE;
  else if (myWorkPart->lockLevel.getValue() == FmPart::FM_DENY_LINK_USAGE)
    return FAP_NOT_EXECUTABLE;

  // Verify that we have a baseName for this part
  if (myWorkPart->setValidBaseFTLFile().empty())
  {
    ListUI <<" --> No FE data file for "<< myWorkPart->getIdString(true) <<"\n";
    return FAP_NOT_EXECUTABLE;
  }

  // No other dependencies, since we are doing a direct solve here
  return FAP_READY_TO_RUN;
}


int FapLinkSolver::createInput(std::string& rdbPath)
{
#ifdef FAP_DEBUG
  std::cout <<"FapLinkSolver::createInput()"<< std::endl;
#endif

  // Check the dependencies for this part
  int depVal = this->checkDependencies();
  if (depVal != FAP_READY_TO_RUN)
    return depVal;

  FmResultStatusData* topRSD = this->getTopLevelRSD();
  if (topRSD->getTaskName() == "noname")
    topRSD->setTaskName("response");

  // Get path for the working directory of this solve process
  rdbPath = this->getRunDir(true,true);
  if (rdbPath.empty())
    return FAP_NOT_EXECUTABLE;

  rdbPath += FFaFilePath::getPathSeparator();

  std::string baseName = FFaFilePath::getBaseName(myWorkPart->baseFTLFile.getValue(),true);

  // Calculation options
  FFaOptionFileCreator fcoArgs(rdbPath + mySolverName + ".fco");

  // Use the FE part data file from the part repository
  myWorkPart->saveFEData();
  fcoArgs.add("-linkfile", FFaFilePath::getRelativeFilename(rdbPath,myWorkPart->getBaseFTLFile()));

  // Get all FIXED external FE nodes
  std::string extNodes;
  std::vector<FmTriad*> localTriads;
  myWorkPart->getTriads(localTriads);
  for (FmTriad* triad : localTriads)
    if (triad->fullyConstrained(true))
    {
      if (!extNodes.empty())
	extNodes += ",";
      extNodes += FFaNumStr(triad->FENodeNo.getValue());
    }
  if (!extNodes.empty())
    fcoArgs.add("-extNodes", "<" + extNodes + ">");

  if (myWorkPart->nGenModes.getValue() > 0)
  {
    fcoArgs.add("-ngen",         myWorkPart->nGenModes.getValue());
    fcoArgs.add("-neval",        myWorkPart->nEigvalsCalc.getValue());
    fcoArgs.add("-tolEigval",    myWorkPart->tolEigenval.getValue());
    fcoArgs.add("-tolFactorize", myWorkPart->tolFactorize.getValue());
    fcoArgs.add("-lumpedmass",  !myWorkPart->useConsistentMassMatrix.getValue());
    fcoArgs.add("-factorMass",   myWorkPart->factorizeMassMxEigSol.getValue());
    if (extNodes.empty()) // Apply shift in case of free-free eigenvalue analysis
      fcoArgs.add("-eigenshift", 0.01);
  }
  fcoArgs.add("-gvec", myWorkMech->gravity.getValue());
  fcoArgs.writeOptFile();

  // Output options
  FFaOptionFileCreator fopArgs(rdbPath + mySolverName + ".fop");
  fopArgs.add("-linkId",  myWorkPart->getBaseID());
  fopArgs.add("-resfile", mySolverName + ".res");
  fopArgs.add("-samfile", baseName + "_SAM.fsm");
  fopArgs.add("-frsfile", baseName + ".frs");
  fopArgs.add("-rdbinc",  FmFileSys::getNextIncrement(rdbPath,"frs"));
  fopArgs.writeOptFile();

  // Additional options, if any
  const std::string& addOptions = FmDB::getActiveAnalysis()->reducerAddOpts.getValue();
  if (!addOptions.empty())
  {
    FFaOptionFileCreator faoArgs(rdbPath + mySolverName + ".fao");
    faoArgs.addComment("Additional user defined options to " + mySolverName);
    faoArgs.add(addOptions,"",false);
    faoArgs.writeOptFile();
  }

  return FAP_READY_TO_RUN;
}


int FapLinkSolver::startProcess(const std::string& rdbPath)
{
#ifdef FAP_DEBUG
  std::cout <<"FapLinkSolver::startProcess()"<< std::endl;
#endif

  return this->startRecovery(NULL,rdbPath,
                             FmDB::getActiveAnalysis()->reducerAddOpts.getValue());
}
