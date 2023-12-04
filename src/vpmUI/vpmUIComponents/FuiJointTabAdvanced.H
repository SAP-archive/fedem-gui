// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIJOINTTABADVANCED_H
#define FUIJOINTTABADVANCED_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"

class FFuLabelFrame;
class FFuOptionMenu;
class FFuLabel;


class FuiJointTabAdvanced : public virtual FFuMultUIComponent
{
public:
  FuiJointTabAdvanced() {}
  virtual ~FuiJointTabAdvanced() {}

  void showRotFormulation(bool yesOrNo);
  void showSpringCpl(bool yesOrNo);
  void showRotSpringCpl();

  FFuLabelFrame      * myRotFormulationFrame;
  FFuOptionMenu      * myRotFormulationMenu;
  FFuOptionMenu      * myRotSequenceMenu;
  FFuLabel           * myRotFormulationLabel;
  FFuLabel           * myRotSequenceLabel;
  FFuLabel           * myRotExplainLabel;

  FFuLabelFrame      * mySpringCplFrame;
  FFuOptionMenu      * myTranSpringCplMenu;
  FFuOptionMenu      * myRotSpringCplMenu;
  FFuLabel           * myRotSpringCplLabel;
  FFuLabel           * myTranSpringCplLabel;

protected:
  virtual void placeWidgets(int width, int height);
  void initWidgets();

  bool IAmShowingRotFormulation;
  char IAmShowingSpringCpl;
};

#endif
