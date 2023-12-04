// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_FE_VIS_CONTROL_H
#define FD_FE_VIS_CONTROL_H

#include <vector>
#include <array>
#include <set>

class FdFEGroupPart;
class FFdLook;


namespace FdFEGroupPartSet
{
  enum GroupPartType { RED_OUTLINE_LINES,  OUTLINE_LINES,
                       RED_SURFACE_LINES,  SURFACE_LINES,
                       RED_SURFACE_FACES,  SURFACE_FACES,
                       RED_INTERNAL_LINES, INTERNAL_LINES,
                       RED_INTERNAL_FACES, INTERNAL_FACES,
                       RED_SPECIAL_LINES,  SPECIAL_LINES,
                       BBOX_LINES, BBOX_FACES,
                       TYPE_COUNT
  };
}


class FdFEVisControl
{
  using GroupPartType = FdFEGroupPartSet::GroupPartType;
  using GroupPartVec  = std::vector<FdFEGroupPart*>;
  using GroupPartSet  = std::array<GroupPartVec,FdFEGroupPartSet::TYPE_COUNT>;
  using FdColor       = std::array<float,3>;

public:
  FdFEVisControl();

  void setGroupPartList(GroupPartType type, const GroupPartVec& gpl);
  void addGroupPart(GroupPartType type, FdFEGroupPart* gp);
  void clearGroupParts();

  void setLineWidth(GroupPartType lineType, double newWidth);

  void update();
  void show(bool doShow) { IAmHidden = !doShow; this->update(); }

  enum DetailType {FULL, RED_FULL, SURFACE, OUTLINE, OUTLINE_NO1D, BBOX, OFF};
  void setDrawDetail(DetailType level) { myDetailLevel = level; this->update(); }
  void setLineDetail(DetailType level) { myLineDetailLevel = level; this->update(); }

  enum DrawStyleType {SOLID_LINES, SOLID,LINES, HIDDEN_LINES};
  void setDrawStyle(DrawStyleType style) { myDrawStyle = style; this->update(); }

  void highlight(bool isToHighlight, DetailType type = OUTLINE,
                 const FdColor& color = {1.0f,0.0f,0.0f});

  void setLook(const FFdLook& aLook);
  void setOverrideLook(const FFdLook& aLook);
  void unsetOverrideLook();

  static void setViewerBackgroundColor(const FdColor& c) { ourBackgroundColor = c; }

  void showResults(bool doShow);
  void showColorResults(bool doShow);
  void showVertexResults(bool doShow) { IAmShowingVertexResults = doShow; this->update(); }

  GroupPartSet::iterator begin() { return myLists.begin(); }
  GroupPartSet::iterator end() { return myLists.end(); }
  GroupPartVec& operator[](int i) { return myLists[i]; }

private:

  // Results on off control var;
  bool IAmShowingResults;
  bool IAmShowingVertexResults;
  bool IAmShowingColorResults;

  // Control vars :
  bool          IAmHidden;
  DetailType    myLineDetailLevel;
  DetailType    myDetailLevel;
  DrawStyleType myDrawStyle;

  bool           IAmHighlighted;
  DetailType     myHighlightType;
  FdColor        myHighlightColor;
  FdColor        myDiffuseColor;
  static FdColor ourBackgroundColor;

  bool IHaveOverrideLook;

  // Convenience method :

  void updateGroupPartsShown();
  void updateContrast();

  void getLooks(FFdLook& meshLook, FFdLook& specLinesLook, FFdLook& backgroundLook);

  void pushContrastGPTOverrideLook(const FFdLook& aLook, GroupPartType type);
  void popContrastGPTOverrideLook(GroupPartType type);

  void pushHighlightGPTOverrideLook(const FFdLook& aLook, GroupPartType type);
  void popHighlightGPTOverrideLook(GroupPartType type);

  void getWhatShouldBeOn(std::set<GroupPartType>& result,
                         DetailType detailLevel, DetailType lineDetailLevel,
                         DrawStyleType drawStyle,
                         bool isResultsVisible, bool isColorResultsVisible,
                         bool isVxResultsVisible);

  void getWhatShouldBeHighlighted(std::set<GroupPartType>& result,
                                  DetailType highlightLevel,
                                  bool isVxResultsVisible, bool isResultsVisible);

  // Group part lists

  GroupPartSet myLists;

  std::set<GroupPartType> myReffedGroupPartTypes;
  std::set<GroupPartType> myHighlightedGroupPartTypes;

  std::set<GroupPartType> myHighlightOverriddenGPTypes;
  std::set<GroupPartType> myContrastOverriddenGPTypes;
};

#endif
