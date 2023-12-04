// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuBase/FFuMultUIComponent.H"


Fmd_SOURCE_INIT(FUI_MULTUICOMPONENT, FFuMultUIComponent, FFuMultUIComponent);

//----------------------------------------------------------------------------

FFuMultUIComponent::FFuMultUIComponent()
{
  Fmd_CONSTRUCTOR_INIT(FFuMultUIComponent);
}

//----------------------------------------------------------------------------

int FFuMultUIComponent::getGridLinePos(int size, int offset, int offsetType, int relativeOffsetBase)
{
  switch (offsetType)
    {
    case REL_OFFSET:     // Relative position (stretches with size)
      if (relativeOffsetBase)
	return (int)(((float)size/relativeOffsetBase) * offset);
      else
	return (size/10)*offset;

    case FROM_START:   // Fixed pos relative Left or upper edge of parent
      return offset;

    case FROM_END:     // Fixed pos relative Right or lover edge of parent
      return size > offset ? size-offset : 0;

    default:
      return offset;
    }
} 


int FFuMultUIComponent::getBorder() 
{
  return 10;
}
