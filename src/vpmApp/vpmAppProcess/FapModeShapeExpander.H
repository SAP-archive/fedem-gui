// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_MODESHAPE_EXPANDER_H
#define FAP_MODESHAPE_EXPANDER_H

#include "FapRecoveryBase.H"
#include <vector>


class FapModeShapeExpander : public FapRecoveryBase
{
public:
  FapModeShapeExpander(FmPart* aPart, FmSimulationEvent* event = 0,
		       bool preBatch = false, bool ImSolvingLastPart = false);

  virtual int createInput(std::string& rdbPath);

  static bool writeVTFHeader(std::vector<FmPart*>& feParts,
			     const std::string& fileName);

protected:
  virtual int startProcess(const std::string& rdbPath);

  static size_t startVTFblock;
  static size_t nPartsVTF;

  bool iAmLast;
};

#endif
