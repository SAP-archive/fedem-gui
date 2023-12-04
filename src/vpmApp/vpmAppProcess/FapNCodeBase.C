// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifdef FAP_DEBUG
#include <iostream>
#endif
#include <cstdlib>
#include <cstdio>
#include <cctype>

#include "FapNCodeBase.H"
#include "vpmPM/FpFileSys.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


FapNCodeBase::FapNCodeBase()
{
#ifdef win32
  char* tmp = tempnam("C:","fedem");
  tmpDir = std::string(tmp);
#else
  char* tmp = tempnam(NULL,"fedem");
  tmpDir = FFaLowerCaseString(tmp); // Only lower-case is allowed on UNIX
#endif
  free(tmp);

  if (!isValidPath(tmpDir))
  {
#ifdef FAP_DEBUG
    std::cout <<"Invalid temporary directory:\n"<< tmpDir << std::endl;
#endif
#ifdef win32
    tmpDir = "C:\\Temp\\";
#else
    tmpDir = "/tmp/";
#endif
    tmpDir += FFaNumStr("fedem%zu",(size_t)this);
  }
  tmpDir += FFaFilePath::getPathSeparator();

  // Find the correct path of the nCode-executables
  char* np = getenv("npath");
  if (np)
  {
    npath = std::string(np);
    FFaFilePath::appendToPath(FFaFilePath::checkName(npath),"bin");
    if (!FpFileSys::isDirectory(npath))
      npath.replace(npath.length()-3,3,"nsoft");
    npath += FFaFilePath::getPathSeparator();
  }

#ifdef FAP_DEBUG
  std::cout <<"tmpDir: "<< tmpDir <<"\nnpath:  "<< npath << std::endl;
#endif
}


bool FapNCodeBase::isValidPath(const std::string& path)
{
  if (path.empty())      return false;
  if (path.size() > 120) return false;

  // Need all lowercase (on UNIX) and no spaces
  for (size_t i = 0; i < path.size(); i++)
    if (isspace((int)path[i]))
      return false;
#ifndef win32
    else if (isupper((int)path[i]))
      return false;
#endif

  return true;
}


bool FapNCodeBase::createTmpDir() const
{
  if (FpFileSys::verifyDirectory(this->tmpDir)) return true;

  ListUI <<"===> ERROR: Unable to create temporary directory "<< this->tmpDir <<"\n";
  return false;
}


bool FapNCodeBase::deleteTmpDir(bool) const
{
#ifdef FAP_DEBUG
  ListUI <<"===> DEBUG: Retaining temporary directory "<< this->tmpDir <<"\n";
#else
  if (FpFileSys::isDirectory(this->tmpDir) && FpFileSys::removeDir(this->tmpDir))
    return true;

  ListUI <<"===> WARNING: Unable to delete temporary directory "<< this->tmpDir
         <<"\n     You should try to remove it manually instead.\n";
#endif
  return false;
}


bool FapNCodeBase::isExecutable(const std::string& solverName) const
{
  //TODO: if npath is empty, check if solverName is in $PATH (how?)
  if (FpFileSys::isFile(solverName)) return true;

  FFaMsg::list("===> ERROR: Can not run nCode Duty Cycle analysis.\n",true);

  if (this->npath.empty())
    ListUI <<"  -> You need to set the \"npath\" environment variable.\n";
  else if (!FpFileSys::isDirectory(this->npath))
    ListUI <<"  -> The \"npath\" environment variable is set,"
	   <<" but points to a non-existing directory.\n"
	   <<"     npath = \""<< FFaFilePath::getPath(this->npath) <<"\"\n";
  else
    ListUI <<"  -> Can not find program file "<< solverName
	   <<"\n     npath = \""<< FFaFilePath::getPath(this->npath)
	   <<"\"\n     You may need to upgrade your nSoft installation.\n";

  ListUI <<"     The \"npath\" environment variable should point to the\n"
	 <<"     installation directory of the nSoft/FE-Fatigue software.\n"
	 <<"     Please ask your system administrator for assistance.\n";

  return false;
}
