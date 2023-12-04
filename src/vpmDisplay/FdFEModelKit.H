// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_FE_MODEL_KIT_H
#define FD_FE_MODEL_KIT_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoVertexProperty.h>

#include "vpmDisplay/FdFEModel.H"
#include "vpmDisplay/FdFEGroupPart.H"

#ifdef win32
#include <SoWinLeaveScope.h>
#endif

class SoSeparator;


class FdFEModelKit : public SoBaseKit, public FdFEModel
{
public:
  FdFEModelKit();
  static void init();

  virtual void setFdPointer(FdObject*);

  void addGroupPart(FdFEGroupPartSet::GroupPartType type,
                    SoSeparator* specialGraphics);
  void deleteGroupParts(FdFEGroupPartSet::GroupPartType type);

  virtual void selectResultFrame(int frameIdx);
  virtual void freezeResultFrame(int frameIdx);
  virtual void unFreezeResultFrame(int frameIdx = -1);

  // Labels

  virtual void* addLabel(const std::string& text, const FaVec3& position);
  virtual void removeLabels(void* id = 0);
  virtual void setLabelColor(const FdColor& rgbColor);

  // Vertexes :

  virtual void setVertexes(const std::vector<FaVec3*>& vertexes);
  virtual void setVertexes(const VertexVec& vertexes);
  FaVec3  getVertex(int idx);
  bool    hasVertexes() const { return myVertexes && myVertexes->vertex.getNum() > 0; }

  // Transformation :

  virtual void setTransform    ( const FaMat34 & pos  );
  virtual void setTempTransform( const FaMat34 & pos  );
  virtual void setTempTransform( float trans[3], float rot[4]);
  virtual void resetTempTransform();
  virtual FaMat34 getActiveTransform();

  // Link coordinate systems Visual control
  virtual void setLinkCSToggle(bool doShow);
  virtual void setInternalCSToggle(bool doShow);
  virtual void addInternalCS(const FaMat34 & localMx);

  // Beam coordinate systems visual control
  virtual void setBeamCSToggle(bool doShow);

  virtual void setCorotCSToggle(bool doShow);
  virtual void setCorotCS(const FaMat34 & localMx);
  virtual void setCoGCSToggle(bool doShow);

  virtual FaMat34 getTransform();

  //  results :

  virtual void addResultFrame     ( int beforeFrame = -1 ); // frame = -1 => at end
  virtual void deleteResultFrame  ( int frameIdx = -1  ); // frameidx = -1 => ALL
  virtual int  getResultFrameCount();

  virtual bool hasResultTransform    ( unsigned int frameIdx );
  virtual void setResultTransform    ( unsigned int frameIdx, const FaMat34& pos );
  virtual void setResultTransforms   ( const std::vector<FaMat34>& posFrames );
  virtual void deleteResultTransforms( int frameIdx = -1); // frameIdx = -1 => all

  virtual void setPrVertexResultLook ( unsigned int frameIdx, const IndexVec& packedLooks);
  virtual void setPrVertexResultLooks( const std::vector<IndexVec>& packedLookFrames);
  virtual void deleteResultLook      ( int frameIdx = -1); // frameIdx = -1 => all

  virtual bool hasResultDeformation( unsigned int frameIdx );
  virtual void setDeformationScale ( float scale);
  virtual void setResultDeformation( unsigned int frameIdx, const VertexVec& defs);
  virtual void setResultVertexes   ( unsigned int frameIdx, const VertexVec& vertexes);
  virtual void setResultVertexes   ( const std::vector<VertexVec>& vertexFrames);
  virtual void deleteResultVertexes( int frameIdx = -1); // frameIdx = -1 => all
  virtual void deletePrVertexResults( int frameIdx = -1); // frameIdx = -1 => all

protected:
  virtual ~FdFEModelKit();

  virtual FdFEGroupPart* createGroupPart(SoSeparator* specialGraphics,
                                         bool isLineShape);
  virtual void show(bool doShow);
  virtual void deleteVisualization(bool keepSpecialGraphics = false);
  virtual void showTransformResults(bool doShow) ;
  virtual void showVertexResults(bool doShow);
  virtual void resetTempVxes();

  virtual void expandFrameArrayIfNeccesary(int frameIdx);

private:
  SoVertexProperty* myVertexes;
  FaMat34 myTransformMx;
  float myDeformationScale;

  // Result frame management :

  typedef std::array<float,3> Vec3f;

  struct ResultsFrame
  {
    ResultsFrame() { vxProp = NULL; mx = NULL; }
    ~ResultsFrame() {}
    void eraseAll()   { eraseMx(); eraseVxProp(); eraseDef(); }
    void eraseVxRes() { eraseVxProp(); eraseDef(); }
    void eraseMx()    { if(mx){ delete(mx); mx = NULL; } }
    void eraseColor() { if(vxProp) vxProp->orderedRGBA.deleteValues(0,-1); }
    void eraseVx()    { if(vxProp) vxProp->vertex.deleteValues(0,-1); }
    void eraseVxProp(){ if(vxProp){ eraseVx(); eraseColor(); vxProp->unref(); vxProp = NULL; } }
    void eraseDef()   { std::vector<Vec3f> empty; deformation.swap(empty); }

    std::vector<Vec3f> deformation;
    SoVertexProperty * vxProp;
    FaMat34          * mx;
  };

  std::vector<ResultsFrame> myResultsFrames;

  // Results Vertexes and look handling :

  SoVertexProperty* findOrCreateVxProp(unsigned int frameIdx);
  void updateResultVertexes(const ResultsFrame& frame);

  void setTempVxes(SoVertexProperty* vxes);
  void setVxFrame(unsigned int frameIdx);

  bool IAmUsingMyVertexes;

  // Results Transformation handling

  FaMat34* findOrCreateXfMx(unsigned int frameIdx);
  void setTransformFrame(unsigned int frameIdx);

  bool IAmUsingMyTransform;

  // Node kit definitions :

  SO_KIT_HEADER(FdFEModelKit);

public:
  SO_KIT_CATALOG_ENTRY_HEADER(toggle);
  SO_KIT_CATALOG_ENTRY_HEADER(linkSep);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(transform2);
  SO_KIT_CATALOG_ENTRY_HEADER(coords);
  SO_KIT_CATALOG_ENTRY_HEADER(groupParts);
  SO_KIT_CATALOG_ENTRY_HEADER(vrmlGraphics);
  SO_KIT_CATALOG_ENTRY_HEADER(backPt);

  SO_KIT_CATALOG_ENTRY_HEADER(labelMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(labels);

  SO_KIT_CATALOG_ENTRY_HEADER(symbolMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(spiderSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(cgSymbolSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(symbolSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(beamCSSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(symbolSep);
  SO_KIT_CATALOG_ENTRY_HEADER(symbol);

  SO_KIT_CATALOG_ENTRY_HEADER(corotCSSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(corotCSSep);
  SO_KIT_CATALOG_ENTRY_HEADER(corotCSSymbol);

  SO_KIT_CATALOG_ENTRY_HEADER(internalCSSwitch);
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
