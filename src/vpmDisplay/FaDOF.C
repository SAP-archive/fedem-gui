// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FaDOF.H"
#include <iostream>


FaDOF::FaDOF(const FaVec3& c, const FaVec3& d, int t) : center(c), direction(d)
{
  type = t;
  direction.normalize();
}


FaDOF& FaDOF::copy(const FaDOF& dof, int t)
{
  center = dof.center;
  direction = dof.direction;
  type = t < 0 ? dof.type : t;
  return *this;
}


FaDOF FaDOF::compound(const FaDOF& dof, double tolerance)
{
#ifdef FD_DEBUG
  std::cout <<"FaDOF::compound()\n"<< *this << dof;
#endif
  switch (type)
    {
    case FREE:
      this->copy(dof);
      break;

    case RIGID:
      break;

    case REV:
      switch (dof.type)
	{
	case FREE:
	  break;

	case REV:
	case CYL:
	  if (!dof.direction.isParallell(direction,tolerance) ||
	      !dof.direction.isParallell(center-dof.center,tolerance))
	    this->copy(dof,RIGID);
	  break;

	case BALL:
	  if (!direction.isParallell(center-dof.center,tolerance))
	    this->copy(dof,RIGID);
	  break;

	default:
	  type = RIGID;
	  break;
	}
      break;

    case BALL:
      switch (dof.type)
	{
	case FREE:
	  break;

	case BALL:
	  if (!dof.center.equals(center,tolerance))
	  {
	    // center = unchanged
	    direction = (center - dof.center).normalize();
	    type = REV;
	  }
	  break;

	case REV:
	case CYL:
	  if (dof.direction.isParallell(center-dof.center,tolerance))
	    this->copy(dof,REV);
	  else
	    this->copy(dof,RIGID);
	  break;

	default:
	  type = RIGID;
	  break;
	}
      break;

    case PRISM:
      switch (dof.type)
	{
	case FREE:
	  break;

	case RIGID:
	case BALL:
	case REV:
	  this->copy(dof,RIGID);
	  break;

	case CYL:
	case PRISM:
	  if (!dof.direction.isParallell(direction,tolerance))
	    this->copy(dof,RIGID);
	  break;

	default:
	  type = RIGID;
	  break;
	}
      break;

    case CYL:
      switch (dof.type)
	{
	case FREE:
	  break;

	case BALL:
	  if (direction.isParallell(center-dof.center,tolerance))
	    type = REV;
	  else
	    this->copy(dof,RIGID);
	  break;

	case REV:
	  if (!dof.direction.isParallell(direction,tolerance) ||
	      !dof.direction.isParallell(center-dof.center,tolerance))
	    this->copy(dof,RIGID);
	  break;

	case CYL:
	  if (!direction.isParallell(dof.direction,tolerance))
	    break;
	  else if (!direction.isParallell(center-dof.center,tolerance))
	    type = PRISM;
	  else
	    this->copy(dof,RIGID);
	  break;

	case PRISM:
	  if (direction.isParallell(dof.direction,tolerance))
	    type = PRISM;
	  else
	    this->copy(dof,RIGID);
	  break;

	default:
	  type = RIGID;
	  break;
	}
      break;

    default:
      type = RIGID;
      break;
    }

#ifdef FD_DEBUG
  std::cout <<"Resulting "<< *this;
#endif
  return *this;
}


FaVec3 FaDOF::normalVector(const FaVec3& v) const
{
  FaVec3 u = v - center;
  return u - (u*direction)*direction;
}


FaVec3 FaDOF::tangentVector(const FaVec3& p1, const FaVec3& p2) const
{
  return (direction*(p2-p1)) * direction;
}


double FaDOF::rotationAngle(const FaVec3& p1, const FaVec3& p2) const
{
  FaVec3 v1 = this->normalVector(p1);
  FaVec3 v2 = this->normalVector(p2);
  if (v1.isZero() || v2.isZero())
    return 0.0;

  double angle = v1.angle(v2);
  return (v1^v2)*direction < 0.0 ? -angle : angle;
}


std::ostream& operator<<(std::ostream& os, const FaDOF& dof)
{
  os <<"FaDOF::";
  switch (dof.type) {
  case FaDOF::RIGID: os <<"RIGID"; break;
  case FaDOF::REV:   os <<"REV"  ; break;
  case FaDOF::BALL:  os <<"BALL" ; break;
  case FaDOF::PRISM: os <<"PRISM"; break;
  case FaDOF::CYL:   os <<"CYL"  ; break;
  case FaDOF::FREE:  os <<"FREE" ; break;
  }
  os <<"\n  DOForigin : "<< dof.center
     <<"\n  direction : "<< dof.direction;
  return os << std::endl;
}
