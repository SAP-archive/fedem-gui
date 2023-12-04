// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSPRDATRANSFORMKIT_H
#define FDSPRDATRANSFORMKIT_H

#include <Inventor/nodes/SoTransform.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoConcatenate.h>

#include "vpmDisplay/FdSprDaPlacer.H"
#include "vpmDisplay/FdTransformKit.H"

#ifdef win32
#include <SoWinLeaveScope.h>
#endif


class FdSprDaTransformKit : public FdTransformKit
{
  SO_KIT_HEADER(FdSprDaTransformKit);

public:

  // Constructor
  FdSprDaTransformKit();

  void connectFirstSpace(SoTransform* global, SoTransform* local);
  void connectSecondSpace(SoTransform* global, SoTransform* local);

  SoINTERNAL public:
  static void init();

protected:

  FdSprDaPlacer* placerEngine;

  SoComposeMatrix* matrixMaker1;
  SoComposeMatrix* matrixMaker2;

  SoConcatenate* transCat1;
  SoConcatenate* rotCat1;
  SoConcatenate* scaleCat1;
  SoConcatenate* scaleOriCat1;
  SoConcatenate* centerCat1;

  SoConcatenate* transCat2;
  SoConcatenate* rotCat2;
  SoConcatenate* scaleCat2;
  SoConcatenate* scaleOriCat2;
  SoConcatenate* centerCat2;

  // Destructor
  virtual ~FdSprDaTransformKit();

  void setUp();
};

#ifdef win32
#include <SoWinEnterScope.h>
#endif

#endif
