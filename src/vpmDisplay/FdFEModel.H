// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_FE_MODEL_H
#define FD_FE_MODEL_H

#include <vector>
#include <string>

#include "vpmDisplay/FdFEVisControl.H"
#include "vpmDisplay/FdFEGroupPart.H"
#include "FFaLib/FFaOperation/FFaOperation.H"
#include "FFaLib/FFaAlgebra/FFaMat34.H"

class  FFlLinkHandler;
class  FFlGroupPartCreator;
struct FFlGroupPartData;
class  SoSeparator;

class FdFEModel
{
protected:
  typedef FdFEVisControl::DetailType    DetailType;
  typedef FdFEVisControl::DrawStyleType DrawStyleType;
  typedef std::vector<FaVec3>           VertexVec;
  typedef std::vector<unsigned int>     IndexVec;

  struct VisParams
  {
    VisParams() {
       overrideShow              = true; doShow            = false;
       overrideDetail            = true; detailLevel       = FdFEVisControl::OFF;
       overrideLineDetail        = true; lineDetailLevel   = FdFEVisControl::OFF;
       overrideDrawStyle         = true; drawStyle         = FdFEVisControl::SOLID_LINES;
       overrideLook              = true;
       overrideShowResults       = true; showResults       = false;
       overrideShowColorResults  = true; showColorResults  = false;
       overrideShowVertexResults = true; showVertexResults = false;
       showTransformResults = false;
    }

    bool overrideShow;      bool          doShow;
    bool overrideDetail;    DetailType    detailLevel;
    bool overrideLineDetail;DetailType    lineDetailLevel;
    bool overrideDrawStyle; DrawStyleType drawStyle;
    bool overrideLook;      FFdLook       look;
    bool overrideShowResults;       bool  showResults;
    bool overrideShowColorResults;  bool  showColorResults;
    bool overrideShowVertexResults; bool  showVertexResults;
    bool showTransformResults;
  };

public:
  FdFEModel();
  virtual ~FdFEModel();

  void updateVertexes(FFlLinkHandler* FEModel);
  void updateGroupParts(FFlGroupPartCreator* FEModel);
  void updateElementVisibility();
  void addGroupPart(FdFEGroupPartSet::GroupPartType type,
                    FFlGroupPartData* groupPartData);
  void addLineShape(const std::vector< std::vector<int> >& indices,
                    unsigned short int pattern = 0xffff);
  virtual void deleteGroupParts(FdFEGroupPartSet::GroupPartType type)= 0;

  void updateVisControl();

  // Results : Transforms/Vertex/Scalars/FrameManeagement
  // Result Types :

  //   void updateColorResults(??);
  //   void updateVertexResults(??);
  //   void updateTransformationResults(??);

  // Visual parameters interface. Reimplemented to handle the
  // Group-GroupParts according to override status.

  virtual void deleteVisualization(bool = false) {}

  virtual void show(bool doShow);
  void setVizMode(FdFEGroupPart::FdGpVizModeEnum type);

  virtual void setDrawDetail(DetailType detailLevel);
  virtual void setLineDetail(DetailType detailLevel);

  virtual void setDrawStyle(DrawStyleType drawStyle);
  virtual void setLook(const FFdLook& aLook);

  virtual void highlight(bool isToHighlight,
                         DetailType type = FdFEVisControl::OUTLINE,
                         const FdColor& color = {1,0,0});

  virtual void showResults(bool doShow);
  virtual void showColorResults(bool doShow);
  virtual void showVertexResults(bool doShow);
  virtual void showTransformResults(bool doShow) = 0;

  // 3D Lib dep. Methods :

  virtual void setFdPointer(FdObject*) = 0;

  // Transformation :

  virtual void setTransform(const FaMat34& pos) = 0;
  virtual void setTempTransform(const FaMat34& pos) = 0;
  virtual void setTempTransform(float trans[3], float rot[4]) = 0;
  virtual void resetTempTransform() = 0;
  virtual FaMat34 getActiveTransform()  = 0;

  // Link coordinate system
  virtual void setLinkCSToggle(bool doShow) = 0;
  virtual void setInternalCSToggle(bool doShow) = 0;
  virtual void addInternalCS(const FaMat34& localMx) = 0;

  // Beam coordinate system
  virtual void setBeamCSToggle(bool doShow) = 0;

  virtual void setCorotCSToggle(bool doShow) = 0;
  virtual void setCorotCS(const FaMat34& localMx) = 0;
  virtual void setCoGCSToggle(bool doShow) = 0;

  virtual FaMat34 getTransform() = 0;

  FFaOperation<FaMat34>* getPosMxReadOp() { return myPosMxReadOp; }

  void setPosMxReadOp(FFaOperation<FaMat34>* readOp)
  {
    if (readOp == myPosMxReadOp) return;
    if (readOp)        readOp->ref();
    if (myPosMxReadOp) myPosMxReadOp->unref();
    myPosMxReadOp = readOp;
  }

  // Result Frames :

  virtual void selectResultFrame(int frameIdx);
  virtual void freezeResultFrame(int frameIdx) = 0;
  virtual void unFreezeResultFrame(int frameIdx = -1) = 0;

  // Labels

  virtual void* addLabel(const std::string& text, const FaVec3& position) = 0;
  virtual void removeLabels(void* id = NULL) = 0;
  virtual void setLabelColor(const FdColor& rgbColor) = 0;

  // Vertexes :

  virtual void setVertexes(const std::vector<FaVec3*>& vertexes) = 0;
  virtual void setVertexes(const VertexVec& vertexes) = 0;

  virtual void resetTempVxes() = 0;

  //  Shared results :

  virtual void addResultFrame(int beforeFrame = -1); // frame = -1 => at end
  virtual void deleteResultFrame(int frameIdx = -1); // frameidx = -1 => ALL
  virtual int  getResultFrameCount() = 0;

  virtual bool hasResultTransform(unsigned int frameIdx) = 0;
  virtual void setResultTransform(unsigned int frameIdx, const FaMat34& pos) = 0;
  virtual void setResultTransforms(const std::vector<FaMat34>& posFrames) = 0;
  virtual void deleteResultTransforms(int frameIdx = -1) = 0;

  void setFringeLegendMapping(const FFaLegendMapper& mapping);
  virtual void setPrVertexResultLook(unsigned int frameIdx, const IndexVec& packedLooks) = 0;
  virtual void setPrVertexResultLooks(const std::vector<IndexVec>& packedLookFrames) = 0;
  virtual void deleteResultLook(int frameIdx = -1) = 0;

  virtual bool hasResultDeformation(unsigned int frameIdx) = 0;
  virtual void setDeformationScale(float scale) = 0;
  virtual void setResultDeformation(unsigned int frameIdx, const VertexVec& defs) = 0;
  virtual void setResultVertexes(unsigned int frameIdx, const VertexVec& vertexes) = 0;
  virtual void setResultVertexes(const std::vector<VertexVec>& vertexFrames) = 0;
  virtual void deleteResultVertexes(int frameIdx = -1) = 0;
  virtual void deletePrVertexResults(int frameIdx = -1) = 0;

  virtual FdFEGroupPart* createGroupPart(SoSeparator* = NULL, bool = false) = 0;

  bool isHighlighted() const { return IAmHighlighted; }

protected:
  void updateLook();

  virtual void expandFrameArrayIfNeccesary(int frameIdx);

  typedef void (FdFEGroupPart::*shapeRefMethodType)(int);
  typedef void (FdFEGroupPart::*shapeRefVoidMethod)();
  void forEachGroupPart(shapeRefMethodType shapeRefMethod, int frameidx);
  void forEachGroupPart(shapeRefVoidMethod shapeRefMethod);

  template<class T> void setVisParam(T& onePieceParam,
                                     void (FdFEVisControl::*setMethod)(T),
                                     T param);

public:
  //! The group parts used for the one-piece representation
  FdFEVisControl myGroupParts;

protected:
  VisParams myGroupWiseVisParams;
  VisParams myVisParams;

  bool IAmHighlighted;
  DetailType myDetailHighlighted;
  FdColor myHighlightColor;
  int myCurrentResultsFrame;

  FFaOperation<FaMat34>* myPosMxReadOp;
};

#endif
