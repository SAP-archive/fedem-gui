// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_DAMAGE_RECOVERY_H
#define FAP_DAMAGE_RECOVERY_H

#include "FapRecoveryBase.H"
#include <vector>


class FmElementGroupProxy;

class FapDamageRecovery : public FapRecoveryBase
{
public:
  FapDamageRecovery(FmPart* aPart, FmSimulationEvent* event = 0,
		    bool preBatch = false);
  FapDamageRecovery(FmPart* aPart,
                    const std::vector<FmElementGroupProxy*>& elemGroups);

  virtual int createInput(std::string& rdbPath);

protected:
  virtual int startProcess(const std::string& rdbPath);

private:
  bool                              autoCreateStrainCoat;
  std::vector<FmElementGroupProxy*> mySelectedGroups;
};

#endif
