// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_NCODE_PROCESSES_H
#define FAP_NCODE_PROCESSES_H

#include "FapSolverBase.H"
#include "FapNCodeBase.H"
#include "vpmDB/FmDutyCycleOptions.H"


class FapFPPHCOPY : public FapSolverBase, private FapNCodeBase
{
public:
  FapFPPHCOPY(const std::string& masterFpp, const std::string& currentFpp);

  virtual int checkDependencies() const { return ((FapFPPHCOPY*)this)->checkDependencies(); }
  virtual int execute();
  virtual std::string getProcessSignature() const;

  void setFinishedCB(const FFaDynCB1<int>& dynCB);

protected:
  void onActualProcessDeath(int exitValue);
  int checkDependencies();

private:
  std::string masterFpp;
  std::string currentFpp;
  std::string tmpCurrent;
  std::string tmpMaster;

  FFaDynCB1<int> myFinishedCB;
};


class FapFATFE : public FapSolverBase, private FapNCodeBase
{
public:
  FapFATFE(const std::string& fpp, FmPart* part);

  virtual int checkDependencies() const { return ((FapFATFE*)this)->checkDependencies(); }
  virtual int execute();
  virtual std::string getProcessSignature() const;

protected:
  void onActualProcessDeath(int exitValue);
  void onHeaderCopyFinished(int exitValue);
  int checkDependencies();

private:
  std::string currentFpp;
  FmPart* myPart;
  bool hcopyFinished;
  bool hcopyStarted;
  std::string tmpFile;
};


class FapFEFCOM : public FapSolverBase, private FapNCodeBase
{
public:
  FapFEFCOM(FmPart* part, bool shellBottom = false);

  virtual int checkDependencies() const { return ((FapFEFCOM*)this)->checkDependencies(); }
  virtual int execute();
  virtual std::string getProcessSignature() const;

  bool areAllFilesOk(std::vector<std::string>& nonExistingFmm, // event with missing fpp
		     std::vector<std::string>& noFpp,
		     std::vector<std::string>& noPart, // event with missing part
		     std::vector<std::string>& multiFpp); // event with multiple fpp files

protected:
  void onActualProcessDeath(int exitValue);
  int checkDependencies();

  std::set<std::string> getFppFiles(const std::string& event, bool& partExists);

private:
  //   fmm
  std::map<std::string, EventData> myEvents;
  FmPart* myPart;

  //   fpp     fef
  std::map<std::string, std::string> myFefMap;

  //   fef    repeats
  std::map<std::string, double> dataMap;

  //   fef    tmpFef
  std::map<std::string, std::string> tmpFiles;
  std::string targetDir;
  std::string resultFile;

  std::string inpFile;
  //   fpp
  std::set<std::string> startedFatFe;

  bool IAmRunningBottom;
};


class FapFEF2FRS : public FapSolverBase, private FapNCodeBase
{
public:
  FapFEF2FRS(FmPart* part);

  virtual int checkDependencies() const { return ((FapFEF2FRS*)this)->checkDependencies(); }
  virtual int execute();
  virtual std::string getProcessSignature() const;

protected:
  void onActualProcessDeath(int exitValue);
  int checkDependencies();

private:
  FmPart* myPart;
  std::string fefFile; // top shell + worst
  std::string fef1File; // bottom shell
  std::string frsFile;
  std::string tmpFrs;
  std::string tmpFef;
  std::string tmpFef1;
};

#endif
