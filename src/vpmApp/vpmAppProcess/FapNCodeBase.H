// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef _FAP_NCODE_BASE_H_
#define _FAP_NCODE_BASE_H_

#include <string>


class FapNCodeBase
{
public:
  FapNCodeBase();
  virtual ~FapNCodeBase() {}

private:
  static bool isValidPath(const std::string& path);

protected:
  bool createTmpDir() const;
  bool deleteTmpDir(bool recursive = false) const;
  bool isExecutable(const std::string& solverName) const;

  std::string tmpDir;
  std::string npath;
  mutable std::string myProcessSignature;
};

#endif
