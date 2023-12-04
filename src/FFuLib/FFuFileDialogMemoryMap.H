// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_FILE_DIALOG_MEMORY_MAP_H
#define FFU_FILE_DIALOG_MEMORY_MAP_H

#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include <string>
#include <map>


class FFuFileDialogMemoryMap : public FFaSingelton<FFuFileDialogMemoryMap>
{
  struct FDMemory
  {
    std::string currentDir;
    std::string currentFilter;
    std::map<std::string,std::string> userOpts;
  };

public:
  FFuFileDialogMemoryMap() {}
  virtual ~FFuFileDialogMemoryMap() {}

  void resetDir(const std::string& newDir, const std::string& oldDir = "")
  {
    for (std::pair<const std::string,FDMemory>& mem : fileDialogMemory)
      if (oldDir.empty() || mem.second.currentDir == oldDir)
        mem.second.currentDir = newDir;
  }

  std::map<std::string,FDMemory> fileDialogMemory;
};

#endif
