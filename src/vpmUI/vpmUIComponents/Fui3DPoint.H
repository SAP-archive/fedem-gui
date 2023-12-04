// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_3D_POINT_H
#define FUI_3D_POINT_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFaLib/FFaAlgebra/FFaVec3.H"

class FFuIOField;
class FFuLabel;
class FFuOptionMenu;
class FFuFrame;


/*!
  UIComponent to edit a 3D point relative to a local or global reference.
*/

class Fui3DPoint : public virtual FFuMultUIComponent
{
public:
  Fui3DPoint() {}
  virtual ~Fui3DPoint() {}

  virtual void setSensitivity(bool sensitive);

  void setLook(int look); // use FFuFrame enums
  void setBorderWidth(int width);

  // Setting and getting coordinate values

  void setXvalue(double value);
  void setYvalue(double value);
  void setZvalue(double value);
  void setValue(double x, double y, double z);
  void setValue(const FaVec3& point);

  double getXvalue() const;
  double getYvalue() const;
  double getZvalue() const;
  FaVec3 getValue () const;

  // Setting and getting coordinate references

  void setGlobal();
  void setGlobalOnly();
  void setLocal();
  void enableLocal();
  bool isGlobal() const;

  // Adding callbacks

  void setPointChangedCB(const FFaDynCB2<const FaVec3&,bool>& aDynCB);
  void setRefChangedCB  (const FFaDynCB1<bool>&               aDynCB);

protected:
  virtual void placeWidgets(int width, int height);

  // Initialisation to be called by UILib dep. subclass

  void init();

  // Internal Callbacks :

  void callPointChangedCB(double d);
  void callRefChangedCB(int choice);

  // Shadow Pt's from Subclass,
  // Subclass is responsible to set them up:

  FFuFrame*   myFrame;
  FFuIOField* myZField;
  FFuIOField* myYField;
  FFuIOField* myXField;
  FFuLabel*   myZLabel;
  FFuLabel*   myYLabel;
  FFuLabel*   myXLabel;
  FFuLabel*   myRefLabel;
  FFuOptionMenu* myRefMenu;

private:
  FFaDynCB2<const FaVec3&,bool> myPointChangedCB;
  FFaDynCB1<bool>               myRefChangedCB;
};

#endif
