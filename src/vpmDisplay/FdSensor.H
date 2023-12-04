// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FDSENSOR_H
#define FDSENSOR_H

#include "vpmDisplay/FdBase.H"

class FmSensorBase;


class FdSensor : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdSensor(FmSensorBase* pt);

  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

  virtual SbVec3f findSnapPoint(const SbVec3f& pointOnObject,
				const SbMatrix& objToWorld,
				SoDetail* pickDetail = 0,
				SoPickedPoint* pPoint = 0);

protected:
  virtual ~FdSensor();

  virtual SoNodeKitListPart* getListSw() const;
};

#endif
