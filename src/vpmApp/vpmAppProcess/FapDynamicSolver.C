// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <ctime>

#include "vpmApp/vpmAppProcess/FapDynamicSolver.H"
#include "vpmApp/vpmAppProcess/FapLinkReducer.H"
#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"
#include "vpmApp/vpmAppProcess/FapSolutionProcessMgr.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"
#include "vpmApp/FapLicenseManager.H"

#include "vpmPM/FpProcessOptions.H"
#include "vpmPM/FpModelRDBHandler.H"
#include "vpmPM/FpPM.H"

#include "vpmDB/FmDB.H"
#include "vpmDB/FmFileSys.H"
#include "vpmDB/FmSolverInput.H"
#include "vpmDB/FmSolverParser.H"
#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmPart.H"

#include "FFaLib/FFaCmdLineArg/FFaOptionFileCreator.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaAppInfo.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


/*!
  Directory structure created by this solver:

  response_####
      |
      +-- timehist_prim_####
      |      th_p_#.frs
      +-- timehist_sec_####
      |      th_s_#.frs
      |      ctrl_#.frs
      +-- eigval_####
             ev_p_#.frs
        response.fmm.bak
        fedem_solver.fsi
        fedem_solver.fco
        fedem_solver.fop
        fedem_solver.fao
        fedem_solver.res

  Available command-line options (run fedem_solver -help to get updated list):
  -JacobiPerturb          Relative perturbation for computation of
                          numerical Jacobian in control iterations
  -VTFfile                Name of VTF output file
  -addBC_eigensolver      Use additional BCs on eigensolver
  -allAccVars             Output all acceleration variables
  -allAlgorVars           Output all algorithm variables
  -allBeamForces          Output all beam sectional forces
  -allCGVars              Output all centre of gravity variables
  -allControlVars         Output all control variables
  -allDampCoeff           Output all damper coefficients
  -allDamperVars          Output all damper variables
  -allDefVars             Output all deflection variables
  -allEnergyVars          Output all energy quantities
  -allEngineVars          Output all engine values
  -allForceVars           Output all force variables
  -allFrictionVars        Output all friction variables
  -allGenDOFVars          Output all generalized DOF variables
  -allHDVars              Output all hydrodynamics variables
  -allJointVars           Output all joint variables
  -allLengthVars          Output all length variables
  -allLoadVars            Output all external load variables
  -allPrimaryVars         Output all primary variables
  -allRestartVars         Output all variables needed for restart
  -allSecondaryVars       Output all secondary variables
  -allSpringVars          Output all spring variables
  -allStiffVars           Output all spring stiffnesses
  -allSupelVars           Output all superelement variables
  -allSystemVars          Output all system variables
  -allTireVars            Output all tire variables
  -allTriadVars           Output all triad variables
  -allVelVars             Output all velocity variables
  -alpha1                 Global mass-proportional damping factor
  -alpha2                 Global stiffness-proportional damping factor
  -alphaNewmark           Numerical damping coefficient
  -autoTimeStep           Time stepping procedure
                          = 0: Fixed time step size
                          = 1: Automatically computed time step size
  -centripForceCorr       Use centripital force correction
  -consolemsg             Output error messages to console
  -ctrlAccuracy           Accuracy parameter for control iterations
  -ctrlTolAbs             Absolute tolerance in control iterations
  -ctrlTolRel             Relative tolerance in control iterations
  -ctrlfile               Name of control system database file
  -curveFile              Name of curve definition file
  -curvePlotFile          Name of curve export output file
  -curvePlotPrec          Output precision for exported curve data files
                          = 0 : half precision (int*2)
                          = 1 : single precision (real*4)
                          = 2 : double precision (real*8)
  -curvePlotType          Format of curve export output file
                          = 0 : ASCII (separate file for each curve)
                          = 1 : DAC, Windows (separate file for each curve)
                          = 2 : DAC, UNIX (separate file for each curve)
                          = 3 : RPC, Windows (all curves in one file)
                          = 4 : RPC, UNIX (all curves in one file)
                          = 5 : ASCII (all curves in one file)
  -cutbackFactor          Time step reduction factor in cut-back
  -cutbackNegPiv          Try cut-back when detecting negative pivots
  -cutbackSing            Try cut-back when detecting singularities
  -cutbackSteps           Number of cut-back steps
  -cwd                    Change working directory
  -damped                 Solve the damped eigenproblem using LAPACK
  -debug                  Debug print switch
  -delayBuffer            Initial buffer size for delay elements
  -densesolver            Use LAPACK dense matrix equation solver
  -double1                Save primary variables in double precision
  -double2                Save secondary variables in double precision
  -effModalMass           Compute the effective mass for each mode
  -eigenshift             Shift value for vibration eigenvalue analysis
  -eiginc                 Time between each vibration analysis
  -factorMass_eigensolver Factor mass matrix in eigensolver
  -fao                    Read additional options from this file
  -fco                    Read calculation options from this file
  -flushinc               Time between each database file flush
                          < 0.0: Do not flush results database
                          = 0.0: Flush at each time step
                          > 0.0: Flush at specified time interval
  -fop                    Read output options from this file
  -frs1file               Name of primary response database file
  -frs2file               Name of secondary response database file
  -fsi2file               Name of additional solver input file
  -fsifile                Name of solver input file
  -help                   Print out this help text
  -ignoreIC               Ignore initial conditions from the fsi-file
  -initEquilibrium        Initial static equilibrium iterations
  -lancz1                 Use the LANCZ1 eigensolver
  -licenseinfo            Print out license information at startup
  -licensepath            License file directory
  -limInitEquilStep       Initial equilibrium step size limit
  -lineSearch             Apply line search during nonlinear iterations
  -maxInc                 Maximum time increment
  -maxSeqNoUpdate         Max number of sequential iterations without
                          system matrix update
  -maxit                  Maximum number of iterations
  -minInc                 Minimum time increment
  -minit                  Minimum number of iterations
  -modesfile              Name of modes database file
  -monitorIter            Number of iterations to monitor before maxit
  -monitorWorst           Number of DOFs to monitor on poor convergence
  -noBeamForces           Suppress all beam sectional force output
  -noStiffDampFiltering   Turn off rigid body filtering
                          of stiffness-proportional damping
  -nosolveropt            Switch off equation system reordering
  -numEigModes            Number of eigenmodes to calculate
  -num_damp_energy_skip   Number of steps without calculation of
                          energy from stiffness proportional damping
  -numit                  Fixed number of iterations
  -nupdat                 Number of iterations with system matrix update
  -pardiso                Use the Pardiso sparse equation solver
  -pardisoIndef           Use Pardiso, indefinite system matrices
  -printinc               Time between each print-out
  -quasiStatic            Do a quasi-static simulation to this time
  -rdbinc                 Increment number for the results database file
  -rdblength              Maximum time length of results database files
  -resfile                Name of result output file
  -restartfile            Response database file(s) to restart from
  -restarttime            Physical time for restart
                          < 0.0: No restart, but regular simulation
  -rpcFile                Get number of repeats, averages, and
                          points per frame and group, from this RPC-file
  -saveinc2               Time between each save of secondary variables
  -saveinc3               Time between each save for external recovery
  -saveinc4               Time between each save of control system data
  -savestart              Time for first save to response database
  -scaleToKG              Scaling factor to SI mass unit [kg]
  -scaleToM               Scaling factor to SI length unit [m]
  -scaleToS               Scaling factor to SI time unit [s]
  -skylinesolver          Use skyline solver
  -stopGlbDmp             Stop time for structural damping factors
  -stopOnDivergence       Number of warnings on possible divergence
                          before the dynamics simulation is aborted
  -stressStiffDivergSkip  Number of iterations without stress
                          stiffening on cut-back with same step size
  -stressStiffDyn         Use geometric stiffness for dynamics
  -stressStiffEig         Use geometric stiffness for eigenvalue analysis
  -stressStiffEqu         Use geometric stiffness for statics
  -stressStiffUpdateSkip  Number of iterations without calculation of new
                          stress stiffening, (predictor step always calculated)
  -targetFrequencyRigid   Target frequency for auto-stiffness calculation
  -terminal               File unit number for terminal output
  -timeEnd                Stop time
  -timeInc                Initial time increment
  -timeStart              Start time
  -tolAccGen              Max generalized acceleration tolerance
  -tolAccNorm             Acceleration vector convergence tolerance
  -tolAccRot              Max angular acceleration tolerance
  -tolAccTra              Max acceleration tolerance
  -tolDispGen             Max generalized DOF tolerance
  -tolDispNorm            Displacement vector convergence tolerance
  -tolDispRot             Max rotation tolerance
  -tolDispTra             Max displacement tolerance
  -tolEigval              Max acceptable relative error in eigenvalues
  -tolEigvector           Orthogonality limit for accepted eigenvectors
  -tolEnerMax             Max energy in a single DOF tolerance
  -tolEnerSum             Energy norm convergence tolerance
  -tolFactCtrl            Singularity criterion for the internal
                          control system solver (smaller value less restrictive)
  -tolFactDyn             Linear solver singularity criterion for
                          dynamics solver
  -tolFactorize           Linear solver singularity criterion for
                          initial equilibrium and eigenvalue analysis
  -tolInitEquil           Convergence tolerance for initial equil. iterations
  -tolResGen              Max residual generalized DOF force tolerance
  -tolResNorm             Residual force vector convergence tolerance
  -tolResRot              Max residual torque tolerance
  -tolResTra              Max residual force tolerance
  -tolUpdateFactor        Convergence criterion scaling factor
                          for continuing matrix updates
  -tolVelGen              Max generalized velocity tolerance
  -tolVelNorm             Velocity vector convergence tolerance
  -tolVelRot              Max angular velocity tolerance
  -tolVelTra              Max velocity tolerance
  -version                Print out program version
  -yamlFile               YAML file prefix for system mode shape export
*/


FapDynamicSolver::FapDynamicSolver(FmSimulationEvent* event, bool preBatch)
{
  mySolverName = "fedem_solver";
  myGroupID = FapSolverID::FAP_DYN_SOLVER;
  myWorkEvent = event;
  amIPreparingForBatch = preBatch;
}


FmResultStatusData* FapDynamicSolver::getTopLevelRSD() const
{
  if (myWorkEvent)
    return myWorkEvent->getResultStatusData();
  else
    return myWorkMech->getResultStatusData();
}


int FapDynamicSolver::checkDependencies() const
{
#if FAP_DEBUG
  std::cout <<"FapDynamicSolver::checkDependencies()"<< std::endl;
#endif

  // Solver is dependent on the existence of reduced data for all parts.
  if (FapSolutionProcessManager::instance()->isGroupRunning(FapSolverID::FAP_REDUCER))
  {
#if FAP_DEBUG > 1
    std::cout <<" --> A reducer process is already running, please wait"<< std::endl;
#endif
    return FAP_PENDING_DEPENDENCIES_BUT_WAIT;
  }

  // Check model consistency
  if (!FmSolverParser::preSimuleCheck())
  {
    FFaMsg::dialog("The current model is not solvable.\n"
                   "Check Output List for details.",FFaMsg::ERROR);
    return FAP_NOT_EXECUTABLE;
  }

  std::vector<FmPart*> allParts;
  FmDB::getAllParts(allParts);
  std::reverse(allParts.begin(),allParts.end());

  int retVar = FAP_READY_TO_RUN;
  for (FmPart* part : allParts)
  {
#if FAP_DEBUG > 1
    std::cout <<"\n --> Creating reduction process"<< std::endl;
#endif

    FapLinkReducer* red = new FapLinkReducer(part,false,amIPreparingForBatch);
    switch (red->checkDependencies())
    {
      case FAP_RESULTS_OK:
        delete red; // everything is OK - just skip this part
        break;

      case FAP_NOT_EXECUTABLE:
        delete red; // reduction could not be run - skip this part and try next
	if (retVar == FAP_READY_TO_RUN) retVar = FAP_NOT_EXECUTABLE;
	break;

      case FAP_READY_TO_RUN:
        FapSolutionProcessManager::instance()->pushSolverProcess(red);
        retVar = FAP_PENDING_DEPENDENCIES;
    }
  }
  return retVar;
}


int FapDynamicSolver::createInput(std::vector<std::string>& rdbPath)
{
#ifdef FAP_DEBUG
  std::cout <<"FapDynamicSolver::createInput()"<< std::endl;
#endif

  // Check the dependencies for the dynamics solver
  int depVal = this->checkDependencies();
  if (depVal != FAP_READY_TO_RUN)
    return depVal;

  // Check for existing results, query for overwrite
  if (FmDB::getActiveAnalysis()->overwriteResults.getValue())
    if (!FpModelRDBHandler::removeAllFiles(this->getTopLevelRSD()))
      return FAP_NOT_EXECUTABLE;

  // Plugin libraries (user-defined functions, etc.)
  std::vector<std::string> plugins;
  FpPM::getActivePlugins(plugins);

  // Create directory structure with solver input files
  myCurrentSolve = Fedem::createSolverInput(FmDB::getActiveAnalysis(),
                                            myWorkMech,myWorkEvent,mySolverName,
                                            plugins,rdbPath,amIPreparingForBatch);
  if (myCurrentSolve.find(mySolverName) > 0)
  {
    ListUI << myCurrentSolve <<"\n";
    FFaMsg::dialog("Failed to generate solver input.\n"
                   "Check Output List for details.",FFaMsg::ERROR);
    return FAP_NOT_EXECUTABLE;
  }

  if (FmDB::getActiveAnalysis()->autoSolverVTFExport.getValue())
  {
    // Find all links that are included in the solver (also the generic parts)
    std::vector<FmLink*> allLinks;
    FmDB::getAllLinks(allLinks);
    for (size_t i = 0; i < allLinks.size();)
      if (allLinks[i]->isSuppressed())
	allLinks.erase(allLinks.begin()+i);
      else
	i++;

    // Create VTF-file for dynamics results
    std::string vtfFile = FmDB::getActiveAnalysis()->solverVTFname.getValue();
    if (!FapSolverBase::writeVTFHeader(allLinks,this->eventName(vtfFile),
                                       FmDB::getActiveAnalysis()->solverVTFtype.getValue()))
      return FAP_NOT_EXECUTABLE;
  }

  return FAP_READY_TO_RUN;
}


int FapDynamicSolver::createInput(std::string& mainPath)
{
  // Activate model data for current simulation event while creating input files
  FmSimulationEvent* activeEvent = FapSimEventHandler::getActiveEvent();
  FapSimEventHandler::activate(myWorkEvent,false,false);

  std::vector<std::string> rdbPath;
  int retVal = this->createInput(rdbPath);
  if (!rdbPath.empty()) mainPath = rdbPath.front();

  // Restore the active event
  FapSimEventHandler::activate(activeEvent,false,false);

  return retVal;
}


int FapDynamicSolver::execute()
{
#ifdef FAP_DEBUG
  std::cout <<"\nFapDynamicSolver::execute()"<< std::endl;
#endif

  // Activate model data for current simulation event while creating input files
  FmSimulationEvent* activeEvent = FapSimEventHandler::getActiveEvent();
  FapSimEventHandler::activate(myWorkEvent,false,false);

  FFaMsg::pushStatus("Creating Dynamics Solver input");
  std::vector<std::string> rdbPath;
  int depVal = this->createInput(rdbPath);
  FFaMsg::popStatus();

  // Restore the active event
  FapSimEventHandler::activate(activeEvent,false,false);

  if (depVal != FAP_READY_TO_RUN)
  {
    if (depVal == FAP_NOT_EXECUTABLE)
      ListUI <<"===> Dynamics Solver did NOT start\n";
    return depVal;
  }
  else if (amIPreparingForBatch)
  {
    ListUI <<"===> Input files for batch execution of "
	   << mySolverName <<" created in:\n     "<< rdbPath.front() <<"\n";
    FapSolutionProcessManager::instance()->afterBatchPreparation(myGroupID);
    return depVal;
  }

  // Create argument string
  FFaOptionFileCreator processOpts;
  if (FapSolverBase::doRemoteSolve())
    processOpts.add("-cwd", this->findRemotePath(rdbPath.front()));

  processOpts.add("-fco", myCurrentSolve + ".fco");
  processOpts.add("-fop", myCurrentSolve + ".fop");
  const std::string& addOptions = FmDB::getActiveAnalysis()->solverAddOpts.getValue();
  if (!addOptions.empty())
    processOpts.add("-fao", myCurrentSolve + ".fao");

  // Switch off explicit result file buffering unless solving the active event.
  // There is no need for this buffering for the other events since they are
  // performed without result-monitoring during the simulation.
  if (myWorkEvent != activeEvent)
    processOpts.add("-flushinc", -1.0);

  // Enable console output of error messages
  processOpts.add("-consolemsg", true);

  // Retain terminal output only when running batch on one processor
  if (!FFaAppInfo::isConsole() ||
      (FmDB::getActiveAnalysis()->maxConcurrentProcesses.getValue() > 1 && myWorkEvent))
    if (addOptions.find("-terminal") == std::string::npos)
      processOpts.add("-terminal", -1); // Redirect to /dev/null

  // Set up the actual process options
  FpProcessOptions options;
  options.name = mySolverName;
  options.args = processOpts.getOptVector();
  if (FapSolverBase::doRemoteSolve())
    options.prefix = FmDB::getActiveAnalysis()->processPrefix.getValue();
  else
    options.workingDir = rdbPath.front();
  options.deathHandler = FFaDynCB1M(FapDynamicSolver, this, onActualProcessDeath, int);

  const time_t currentTime = time(NULL);
  const std::string& rdb = myWorkMech->getAbsModelFilePath();
  ListUI <<"\n===> Dynamics Solver started: "<< ctime(&currentTime);
  if (rdbPath.size() > 1)
  {
    ListUI <<"  -> Results in "<< FFaFilePath::getRelativeFilename(rdb,rdbPath[1]);
    for (size_t i = 2; i < rdbPath.size(); i++)
      ListUI <<"\n                "<< FFaFilePath::getRelativeFilename(rdb,rdbPath[i]);
    ListUI <<"\n";
  }
  if (this->run(options) < 0)
    return FAP_NOT_EXECUTABLE;

  // If we are solving an event which has not been opened in current session,
  // it is now time to record a copy of the result file set before the RDB of
  // current event is populated with new result files form the running solver.
  // To ensure proper cleanup later if the session is closed without saving.
  // Note that the event RSD's are not syncronized against the contents on
  // disk while the solver process is running or when it finishes,
  // only on explicit model Save, Close, or on Active Event switching.
  if (myWorkEvent && !myWorkEvent->isTouched())
    myWorkEvent->getResultStatusData(false)->copy(myWorkEvent->getResultStatusData());

  FFaMsg::pushStatus("Solving");

  return FAP_STARTED;
}


std::string FapDynamicSolver::getProcessSignature() const
{
  if (myProcessSignature.empty())
  {
    myProcessSignature = mySolverName + "@"
      + this->getTopLevelRSD()->getCurrentTaskDirName(true);
#if FAP_DEBUG > 3
    std::cout <<"Process sig: "<< myProcessSignature << std::endl;
#endif
  }
  return myProcessSignature;
}


void FapDynamicSolver::onActualProcessDeath(int exitValue)
{
  const time_t currentTime = time(NULL);
  ListUI <<"===> Dynamics Solver ";
  if (IWasKilled)
    ListUI <<"terminated by user: ";
  else if (exitValue)
    ListUI <<"failed: ";
  else
    ListUI <<"done: ";
  ListUI << ctime(&currentTime);

  if (exitValue)
  {
    if (!IWasKilled)
    {
      std::string resFile = this->getTopLevelRSD()->getCurrentTaskDirName(true)
	+ myCurrentSolve + ".res";
      if (FmFileSys::isReadable(resFile))
	ListUI <<"     See "<< resFile <<" for further details.\n";
    }

    // Remove created frs-files containing no results
    FpModelRDBHandler::purgeTruncatedResultFiles(this->getTopLevelRSD());
  }

  FFaMsg::list("\n",exitValue);
  FFaMsg::popStatus();

  std::string sign = this->getProcessSignature();
  FapSolutionProcessManager::instance()->onSolverProcessDeath(sign,exitValue);
}
