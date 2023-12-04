// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_BEAM_H
#define FD_BEAM_H

#include "vpmDisplay/FdLink.H"

class FmBeam;


class FdBeam : public FdLink
{
  Fmd_HEADER_INIT();

public:
  FdBeam(FmBeam* beam);

  virtual bool updateFdDetails();
  virtual void updateSimplifiedViz();
  virtual void showCS(bool doShow);

private:
  bool updateBeamDetails(FmBeam* beam, FdCadHandler* cadHandler);

protected:
  virtual void showHighlight();
  virtual void hideHighlight();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
