// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_DB_POINT_SELECTION_DATA_H
#define FD_DB_POINT_SELECTION_DATA_H

#include "FFaLib/FFaAlgebra/FFaVec3.H"

class FFuQtPushButton;
class QWidget;
class QLabel;


class FdDBPointSelectionData
{
public:
  FdDBPointSelectionData();

  void createAndUpdateUI();
  void hideUI();

private:
  void createUI();
  void updateUI();
  void onButtonToggled(bool);

public:
  bool   isDirOnly;
  int    pPointIdx;
  bool   isEdge;
  FaVec3 pickedPoint;
  FaVec3 vxSnappedPPoint;
  FaVec3 ppNormal;
  FaVec3 axis;
  bool   isAxisDefined;
  FaVec3 origin;
  bool   showDirection;
  bool   isUnknownShape;

private:
  FFuQtPushButton* myOnCenterButton;
  FFuQtPushButton* myOnCircumfButton;
  FFuQtPushButton* mySnapOnButton;
  FFuQtPushButton* myFlipDirectionButton;
  QWidget* centerBox;
  QWidget* circumfBox;
  QWidget* flipDirBox;
  QWidget* snapOnBox;
  QLabel*  snapLabel;
  QWidget* myGroupBox;
};

#endif
