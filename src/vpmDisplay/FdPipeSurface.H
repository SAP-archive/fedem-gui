// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDPIPESURFACE_H
#define FDPIPESURFACE_H

#include "vpmDisplay/FdBase.H"

class FmPipeSurface;
class SoMaterial;


class FdPipeSurface : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdPipeSurface(FmPipeSurface* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

protected:
  virtual ~FdPipeSurface();

  virtual SoNodeKitListPart* getListSw() const;

  virtual void showHighlight();
  virtual void hideHighlight();

  SoMaterial* myLineMaterial;
  SoMaterial* myFaceMaterial;
};

#endif
