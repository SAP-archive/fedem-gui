// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_LICENSE_MANAGER_H
#define FAP_LICENSE_MANAGER_H

#include <string>


namespace FapLicenseManager
{
  enum MsgType { NO_MSG, LIST_MSG, DIALOG_MSG };

  bool hasCtrlLicense(int creating = 0, int msgType = DIALOG_MSG);
  inline bool hasExtCtrlLicense(int = NO_MSG) { return false; }
  bool hasTireLicense(int msgType = DIALOG_MSG);
  bool hasDurabilityLicense(int msgType = DIALOG_MSG);
  inline bool hasNCodeInterfaceLicense() { return false; }
  bool hasVTFExportLicense(int msgType = DIALOG_MSG);

  bool checkCtrlLicense(bool checkOut = true, int creating = -1);
  bool checkExtCtrlLicense(bool checkOut = true);
  bool checkTireLicense(bool checkOut = true);
  bool checkVTFExportLicense(bool checkOut = true);
  bool checkWindpowerLicense(bool checkOut = true);
  bool checkOffshoreLicense(bool checkOut = true);
  bool checkSimEventLicense(bool checkOut = true);
  bool checkLicense(const char* feature, bool checkOut = true);

  inline bool hasFeature(const char* feat) { return checkLicense(feat,false); }

  inline bool isFreeEdition() { return false; }
  inline bool isDemoEdition() { return false; }
  inline bool isLimEdition()  { return false; }
  inline bool isProEdition()  { return true; }

  bool hasUserGuide();
  bool hasTheoryGuide();
  bool hasReferenceGuide();
  bool hasComAPIGuide();
}

#endif
