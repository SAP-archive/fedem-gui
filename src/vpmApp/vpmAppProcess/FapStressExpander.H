// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_STRESS_EXPANDER_H
#define FAP_STRESS_EXPANDER_H

#include "FapRecoveryBase.H"

class FmElementGroupProxy;


class FapStressExpander : public FapRecoveryBase
{
public:
  FapStressExpander(FmPart* aPart, FmSimulationEvent* event = NULL,
		    bool preBatch = false, bool ImSolvingLastPart = false);
  FapStressExpander(FmPart* aPart, const std::vector<FmElementGroupProxy*>& groups,
		    bool ImSolvingLastPart = false);

  virtual int checkDependencies() const;
  virtual int createInput(std::string& rdbPath);

  static bool writeVTFHeader(std::vector<FmPart*>& feParts,
			     const std::string& fileName);

protected:
  virtual int startProcess(const std::string& rdbPath);

  //! \brief Checks if a direct solution is available for this part.
  bool getDirectSolveResults(std::string& samFile, std::string& frsFile) const;

private:
  static bool   initStateOnVTF;
  static size_t startVTFblock;
  static size_t nPartsVTF;

  bool iAmLast;

  std::vector<FmElementGroupProxy*> mySelectedGroups;

  mutable std::string mySamFile; //!< SAM-file from direct solution
  mutable std::string myFrsFile; //!< FRS-file from direct solution
};

#endif
