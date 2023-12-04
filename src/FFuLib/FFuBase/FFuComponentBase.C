// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuComponentBase.H"


/*!
  \brief Sets the geometry for the component.
  \param left left edge for the rectangle
  \param right right edge for the rectangle
  \param top top edge for the rectangle
  \param bottom bottom endge for the rectangle
  \sa setSizeGeometry setCenterGeometry setCenterYGeometry
*/

void FFuComponentBase::setEdgeGeometry  (int left, int right, int top, int bottom)
{
  int width = right-left;
  int height = bottom-top;

  if (width  < 0 ) { width  = 0;}
  if (height < 0 ) { height = 0;}

  this->setSizeGeometry(left,top, width , height );
}


/*!
  \brief Sets the geometry for the component.
  \param centerX vertical center location for the rectangle
  \param centerY horizontal center location for the rectangle
  \param width widht for the rectangle
  \param height height for the rectangle
  \sa setSizeGeometry setEdgeGeometry setCenterYGeometry
*/

void FFuComponentBase::setCenterGeometry(int centerX, int centerY, int width, int height)
{
  if (width  < 0 ) { width  = 0;}
  if (height < 0 ) { height = 0;}

  int left = centerX - width/2;
  int top  = centerY - height/2;

  this->setSizeGeometry(left,top, width , height );
}


/*!
  \brief Sets the geometry for the component.
  \param leftX vertical left location for the rectangle
  \param centerY horizontal center location for the rectangle
  \param width widht for the rectangle
  \param height height for the rectangle
  \sa setSizeGeometry setEdgeGeometry setCenterYGeometry
*/

void FFuComponentBase::setCenterYGeometry(int leftX, int centerY, int width, int height)
{
  if (width  < 0 ) { width  = 0;}
  if (height < 0 ) { height = 0;}

  int top  = centerY - height/2;

  this->setSizeGeometry(leftX,top, width , height );
}
