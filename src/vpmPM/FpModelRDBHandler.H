// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FP_MODEL_RDB_HANDLER_H
#define FP_MODEL_RDB_HANDLER_H

#include <string>
#include <vector>
#include <set>
#include <map>

class FmPart;
class FmMechanism;
class FmResultStatusData;


class FpModelRDBHandler
{
  // Some convenience type definitions
  typedef std::set<std::string>   Strings;
  typedef Strings::const_iterator StringsIter;

public:

  // Scans RDB sub-directories and compares with stored RDB data.
  // Option on what to do with non-stored files.
  // Warning for missing files.
  static void RDBOpen(FmResultStatusData* rsd, FmMechanism* mechData,
		      bool includeReducerFiles = false,
		      bool askForMissingInRSD = false);

  // Closes the active model.
  static void RDBClose(FmResultStatusData* currentRSD,
		       FmResultStatusData* initialRSD,
		       bool deleteFilesNotInRSD = true,
		       bool clearExtractor = true);

  // Removes non-current result directories.
  // Syncronizes current directories (look for not-know-files).
  static void RDBSave(FmResultStatusData* currentRSD,
		      FmResultStatusData* initialRSD,
		      bool pruneEmptyDirs = true);

  // Saves data in current RDB to a new location.
  // Resets the RDB counters and copies the data.
  static void RDBSaveAs(const std::string& RDBPath,
			FmResultStatusData* currentRSD,
			FmResultStatusData* initialRSD,
			FmMechanism* mech, const std::string& subPath = "");

  // Used by SaveAs to update the model with positions at specified time.
  static double updateModel(double atTime);

  // Syncronizes the RDB and extractor with data found on disk.
  static void RDBSync(FmResultStatusData* currentRSD, FmMechanism* mech,
		      bool updateExtractor = false, bool addResFiles = false);
  static void RDBSync(FmResultStatusData* currentRSD, FmMechanism* mech,
		      std::vector<std::string>& newFrsFiles,
		      bool updateExtractor = true, bool addResFiles = false,
		      bool checkExistingRSD = false);
  static void RDBSync(FmPart* part, FmMechanism* mech, bool addResFiles = false,
		      const std::string& RDBPath = "");
  static void RDBSyncOnParts(FmResultStatusData* rsd, FmMechanism* mech);

  static void RDBIncrement(FmResultStatusData* currentRSD,
			   FmMechanism* mech,
			   bool updateExtractor = true);
  static void RDBRelease(bool reducerFilesToo = false, bool noRenewal = false);

  static void getKeys(FmResultStatusData* currentRSD,
		      std::set<double>& validRdbTimes,
		      const std::string& rdbResultGroup);
  static bool hasResults(FmResultStatusData* currentRSD,
			 const std::string& rdbResultGroup = "");

  // Does the same as RDBIncrement, but only for the selected result group.
  static void removeResults(const std::string& rdbResultGroup,
			    FmResultStatusData* currentRSD,
			    FmPart* filterOnPart = NULL);

  // Removes all existing result files.
  static bool removeAllFiles(FmResultStatusData* rsd);

  // Removes all frs-files that have been truncated by a solver process.
  static void purgeTruncatedResultFiles(FmResultStatusData* rsd);

  static void removeResultFiles(const Strings& files, FmPart* part);
  static void removeResultFiles(const Strings& files, FmResultStatusData* rsd);

  static void removeResFiles();

  // Enables/disables result files.
  static void changeResultFilesState(FmMechanism* mech, const Strings& files,
				     bool enable = true);

  static void removeDisabledFiles(FmMechanism* mech,
				  const Strings& files = Strings());

  // Caching of time step data.
  static void enableTimeStepPreRead(FmResultStatusData* currentRSD,
				    const std::string& rdbResultGroup);
  static void disableTimeStepPreRead();
  static void clearPreReadTimeStep();

  static void clearPartIdMap() { ourPartIdMap.clear(); }

protected:
  static FmPart* getPartRelatedToResFile(const std::string& resultFileName);

private:
  static std::map<std::string,FmPart*> ourPartIdMap;

  static Strings ourReducerFRSs;
  static Strings ourAddedRESs;
};

#endif
