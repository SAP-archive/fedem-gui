// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_CAM_JOINT_H
#define FD_CAM_JOINT_H

#include "vpmDisplay/FdBase.H"
#include <vector>

class FmCamJoint;


class FdCamJoint : public FdObject
{
  Fmd_HEADER_INIT();

public:
  FdCamJoint(FmCamJoint* pt);

  virtual void hide();
  virtual bool updateFdTopology(bool updateChildrenDisplay = true);
  virtual bool updateFdDetails();
  virtual bool updateFdApperance();

  virtual void smartMove(const FaVec3& firstPoint, const FaVec3& secondPoint,
			 const FaDOF& dof);

protected:
  virtual ~FdCamJoint();

  virtual SoNodeKitListPart* getListSw() const;

  virtual void showHighlight();
  virtual void hideHighlight();

private:
  static void arcToNURBS(const FaVec3& p1, const FaVec3& p2, const FaVec3& p3,
			 std::vector<double>& xi,
			 std::vector<FaVec3>& P, std::vector<double>& w);
};

#endif
