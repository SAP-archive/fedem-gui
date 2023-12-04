// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_ANIMATION_CREATOR_H
#define FAP_ANIMATION_CREATOR_H

#include "vpmDB/FmVTFType.H"

#include <vector>
#include <set>

class FmModelMemberBase;
class FmLink;
class FmPart;
class FmTriad;
class FdTriad;
class FmAnimation;
class FdAnimateModel;
class FFlLinkHandler;
class FFrExtractor;
class FFrEntryBase;
class FFaLegendMapper;
class FFaProfiler;
class FaMat34;
class FaVec3;


class FapAnimationCreator
{
  typedef std::vector<FaVec3> FaVec3Vec;
  typedef std::vector<double> DoubleVec;
  typedef std::set<double>    DoubleSet;

public:
  FapAnimationCreator();
  ~FapAnimationCreator();

  // Load an animation into the 3D viewer

  bool loadAnimation(FmAnimation* animation, FdAnimateModel* animator,
		     bool& userCancelled);

  // Load an animation and export to VTF file

  bool exportToVTF(FmAnimation* animation,
		   const std::string& vtfFile, VTFFileType type,
		   bool convTo1stOrder = false, double timeInc = 0.0);

  // Position matrix progress animation. Used as CBs on signals from RDB.

  void initAllPosMxReading(FmAnimation* animation, FdAnimateModel* animator);
  void readAllNewPosMx(FmAnimation* animation);
  void finishAllPosMxReading();

  // Methods to control the loading process

  double getMaxFringeVal() const { return myMaxFringeValue; }
  double getMinFringeVal() const { return myMinFringeValue; }

private:

  // Convenience methods :

  bool initReading(FmAnimation* animation);
  double initRDB(DoubleSet& timeSteps, DoubleSet::const_iterator& startTimeIt);
  double incrementRDB(const DoubleSet& timeSteps, DoubleSet::const_iterator& it);

  // Position matrices :

  void initPosMxReading(FmLink* link, FFrExtractor* extr);
  void initPosMxReading(FmTriad* link, FFrExtractor* extr);
  bool readPosMx(int frameIdx, FmLink* link);
  bool readPosMx(int frameIdx, FmTriad* triad);
  void finishPosMxReading(FmLink* link);
  void finishPosMxReading(FmTriad* triad);

  // Deformations :

  void initDeformationReading(FmPart* part, FFrExtractor* extr,
			      const std::vector<int>* nodeFilter = NULL);
  void readDeformations(int frameIdx, FmPart* part);
  bool readDeformations(FaVec3Vec& def, FmPart* part);
  void finishDeformationReading(FmPart* part);

  // Fringes :

  int initFringeReading(FmPart* part, FFrExtractor* extr,
			FmAnimation* animation,
			const std::vector<int>* nodeFilter = NULL);
  void readFringeData(int frameIdx, FmPart* part,
		      const FFaLegendMapper& legendMapping);
  bool readFringeData(DoubleVec& values, FmPart* part);
  bool readFringeData(std::vector<DoubleVec>& values, FmPart* part);
  void finishFringeReading(FmPart* part);


  // Modes animation methods (implemented in FapModesAnimation.C) :

  static bool modesAnimation(FmAnimation* animation, FdAnimateModel* animator,
                             bool& userCancelled);

  static int modesInitAnim(FmAnimation* animation, FdAnimateModel* animator,
                           FFrExtractor* rdb,
                           const std::vector<FmModelMemberBase*>& objs,
                           double& ksi, double& omega,
                           double& Tmax, double& Tinc);

  static int getEigenValue(FFrExtractor* rdb, FmLink*& foundLink,
                           const std::vector<FmModelMemberBase*>& objs,
                           int modeNr, int modeType,
                           double& Re, double& Im);

  static bool getPosition(FFrExtractor* rdb,
                          const char* objType, int baseId,
                          FaMat34& posMat);

  static bool getEigenVector(FFrExtractor* rdb,
                             const char* objType, int baseId, int modeNr,
                             FaVec3Vec& translation, FaVec3Vec& rotation);

  static bool getEigenVector(FFrExtractor* rdb, FmPart* part,
                             int modeNr, int modeType,
                             std::vector<FaVec3Vec>& eigenVector);

  static bool getDeformation(const FFrEntryBase* itemGroup,
                             FaVec3& translation, FaVec3& rotation);

  static bool getDeformation(const FFrEntryBase* itemGroup,
                             FaVec3& deformation, bool rotation = false);

  static bool readMatrix(FFrEntryBase* entry, FaMat34& mat);


  // Attributes used by time history and time summary animations

  FFrExtractor*   myExtractor;
  FdAnimateModel* myAnimator;

  std::vector<FmLink*>  myLinks;
  std::vector<FmPart*>  myParts;
  std::vector<FmTriad*> myTriads;

  bool IAmUsingMostFrames;
  bool IAmLoadingDeformData;
  char IAmLoadingFringeData; // 1=face fringe, 2=line fringes, 3=both
  bool IHaveOneColorPrFace;
  bool IAmSummaryAnimation;

  double myStartTime;
  double myStopTime;
  double myMinDeltaT;
  double myLastReadTime;

  double myMaxFringeValue;
  double myMinFringeValue;

  double mySpecialValue;
  double mySpValConvertValue;

  bool IHaveInitedAllPosMxReading;

#ifdef FT_USE_PROFILER
  FFaProfiler* myProfiler;
#endif
};

#endif
