// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_SOLVER_BASE_H
#define FAP_SOLVER_BASE_H

#include <string>
#include <vector>

#include "vpmPM/FpProcessBase.H"

class FmSimulationEvent;
class FmMechanism;
class FmLink;
class FmPart;
struct FapExpProp;


class FapSolverBase : public FpProcessBase
{
public:
  FapSolverBase();
  virtual ~FapSolverBase() {}

  // Builds a dependency tree from this process. Returns
  // FAP_READY_TO_RUN    - everything set to run, new dependencies created
  // FAP_RESULTS_OK      - the results are already calculated
  // FAP_NOT_EXECUTABLE  - cannot resolve needed dependencies
  virtual int checkDependencies() const = 0;

  // Creates all neccesary input files needed to execute the process. Returns
  // FAP_PENDING_DEPENDENCIES  - need to run depending processes
  // FAP_NOT_EXECUTABLE        - cannot resolve needed dependencies
  // FAP_RESULTS_OK            - input files hase been successfully created
  virtual int createInput(std::string&) { return FAP_NOT_EXECUTABLE; }

  // Tries to run the process. Returns
  // FAP_PENDING_DEPENDENCIES  - need to run depending processes
  // FAP_NOT_EXECUTABLE        - cannot resolve needed dependencies
  // FAP_STARTED               - process started
  // FAP_RESULTS_OK            - results are already present
  virtual int execute() = 0;

  // Invoked repeatedly while the process is running to perform syncronisations
  // against new data on disk created by this process
  virtual void syncRDB() {}

  enum {
    FAP_READY_TO_RUN,
    FAP_RESULTS_OK,
    FAP_NOT_EXECUTABLE,
    FAP_PENDING_DEPENDENCIES,
    FAP_PENDING_DEPENDENCIES_BUT_WAIT,
    FAP_STARTED
  };

  virtual std::string getProcessSignature() const = 0;

  virtual FmSimulationEvent* getEvent() const { return NULL; }
  virtual FmPart* getWorkPart() const { return NULL; }
  int getGroupID() const { return myGroupID; }

  // Modify given file name to account for current simulation event.
  std::string eventName(const std::string& fileName) const;

  // Creates a VTF file with header info (and optionally FE geometry)
  // that the solver process might append results to
  static bool writeVTFHeader(std::vector<FmLink*>& links,
			     const std::string& fileName, int type);
  static bool writeVTFHeader(std::vector<FmLink*>& links,
			     const std::string& fileName, int type,
			     const FapExpProp& prop);
  static bool writeVTFHeader(std::vector<FmLink*>& links,
			     const std::vector<std::string>& fileNames, int type,
			     const FapExpProp& prop, bool writeFEdata = true);

protected:
  // Checks whether a solver process is to be executed remotely or not
  static bool doRemoteSolve();

  // Returns the cwd-path of the solver process on the remote computer,
  // given the equivalent path on the local computer
  std::string findRemotePath(const std::string& localPath) const;

  // Executes the process with the specified options
  int run(const FpProcessOptions& options, const char* name = NULL);

protected:
  FmMechanism* myWorkMech;
  std::string  mySolverName;
  int          myGroupID;
};

#endif
