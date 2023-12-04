// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUITOPOLOGYVIEW_H
#define FUITOPOLOGYVIEW_H

#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFuLib/FFuBase/FFuUAExistenceHandler.H"
#include "FFuLib/FFuBase/FFuUADataHandler.H"

#include <vector>
#include <string>

class FFuListView;
class FFuListViewItem;
class FFuFrame;

class FuiTopologyItem
{
public :
  FuiTopologyItem(const std::string &aType, const std::string &anId,
                  const std::string &aDescription,int   aDepth)
    {
      type = aType; id   = anId; description = aDescription; 
      depth = aDepth;
    }

  // Data :

  std::string type;
  std::string id;
  std::string description;
  int    depth;

};

class FFuaCmdItem;
class FFuPopUpMenu;

class FuiTopologyView : public virtual FFuMultUIComponent, 
                        public FFuUAExistenceHandler,
                        public FFuUADataHandler
{
public:
  FuiTopologyView();
  virtual ~FuiTopologyView();

  // Setting up 
  
  virtual void setUIValues(const FFuaUIValues* values);

  void setTree(const std::vector<FuiTopologyItem> &topology);

  void setAutoUnHighlight(bool doAutoUnHighlight)
    {IAmAutoUnHighlighting = doAutoUnHighlight; }

  static FuiTopologyView* getTopologyView();
  FFuListView* getListView();
 
  // Adding callbacks

  //void setOnPoppedUpCB   (const FFaDynCB0            &aDynCB);
  void setHighlightedCB  (const FFaDynCB2<int, bool> &aDynCB);
  void setActivatedCB    (const FFaDynCB1<int>       &aDynCB);
  void setBuildPopUpCB   (const FFaDynCB2
                          <const std::vector<int> &,                // Selection.
                          std::vector<FFuaCmdItem*> &>  &aDynCB); // Commands to popUp
  void setPopUpSelectedCB(const FFaDynCB2
                          <const std::vector<int> &,                // Selection.   
                          FFuaCmdItem*>    &aDynCB); // PopUp entry.

protected:
  virtual void placeWidgets(int width, int height);

  // Initialisation to be called by UILib dep. subclass
  
  void initWidgets();

  // Reimplementation :
 
  void onPoppedUp();

  // Shadow Pt's from Subclass
 
  FFuListView  * myView;
  FFuFrame     * myFrame;
 

private: 
  // Methods used by myView :

  void onMyViewSelectionChanged();
  void onMyViewMouseReleased();
  void onMyViewActivated(FFuListViewItem * item);
  void onMyViewRMBPressed(FFuListViewItem * item);
  void onMyViewPopUpSelected(const std::vector<FFuListViewItem*>&,FFuaCmdItem*);

  // Control vars :

  bool IAmAutoUnHighlighting;

  static FuiTopologyView* topologyView;

  // Callback Objects :
  
  // FFaDynCB0                            myOnPoppedUpCB;
  FFaDynCB2<int, bool>                 myHighlightedCB;
  FFaDynCB1<int>                       myActivatedCB;
  FFaDynCB2<const std::vector<int> &,      
            std::vector<FFuaCmdItem*> & > myBuildPopUpCB;
  FFaDynCB2<const std::vector<int> &,      
            FFuaCmdItem*>    myPopUpSelectedCB;

};

class FuaTopologyValues : public FFuaUIValues
{
public:
  std::vector<FuiTopologyItem> topology;
};


#endif
