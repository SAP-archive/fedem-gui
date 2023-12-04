// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoPickedPoint.h>
#include <Inventor/details/SoDetail.h>
#include <Inventor/details/SoLineDetail.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoIndexedLineSet.h>

#include "vpmDB/FmCtrlLine.H"
#include "vpmDisplay/FdCtrlKit.H"
#include "vpmDisplay/FdCtrlLineKit.H"
#include "vpmDisplay/FdCtrlElement.H"
#include "vpmDisplay/FdBackPointer.H"
#include "vpmDisplay/FdCtrlDB.H"
#include "vpmDisplay/FdCtrlLine.H"
#include "vpmDisplay/FdCtrlSymDef.H"


Fmd_SOURCE_INIT(FDCTRLLINE, FdCtrlLine, FdCtrlObject);

FdCtrlLine::FdCtrlLine(FmCtrlLine* ptr)
{
  Fmd_CONSTRUCTOR_INIT(FdCtrlLine);

  itsFmOwner = ptr;

  itsKit = new FdCtrlLineKit;
  itsKit->ref();

  // Set up the back pointer
  SO_GET_PART(itsKit,"backPt",FdBackPointer)->setPointer(this);
}

FdCtrlLine::~FdCtrlLine()
{
  this->fdDisconnect();
  itsKit->unref();
}


SoNodeKitListPart* FdCtrlLine::getListSw() const
{
  return SO_GET_PART(FdCtrlDB::getCtrlKit(),"lineList",SoNodeKitListPart);
}


bool FdCtrlLine::updateFdAll(bool updateChildrenDisplay)
{
  this->FdCtrlObject::updateFdAll(updateChildrenDisplay);
  this->drawLine();

  return true;
}


bool FdCtrlLine::updateFdDetails()
{
  // Set drawing style
  SoDrawStyle* drawStyle = SO_GET_PART(itsKit,"appearance.style",SoDrawStyle);
  drawStyle->lineWidth.setValue(2.0);
  drawStyle->pointSize.setValue(6.0);

  return true;
}


/*!
  Shows where on the line the user has hit.
  1 -> Point1, 2 -> Point2, ...., -1 -> Line1, -2 -> Line2, ......
*/

int FdCtrlLine::pickedLineDetail(const SbVec3f& pCoord, long partIndex)
{
  // Distance from the line corner, this is used to separate corners from lines
  const float length = 0.05f;

  SbVec3f coord1 = this->getCoordinate(partIndex);
  SbVec3f coord2 = this->getCoordinate(++partIndex);

  for (int i = 1; i >= 0; i--)
    if (coord1[1-i] == coord2[1-i])
    {
      if (fabsf(coord1[i] - pCoord[i]) < length)
        return partIndex;
      else if (fabsf(pCoord[i] - coord2[i]) < length)
        return partIndex+1;
      else
        return -partIndex;
    }

  return 0;
}


void FdCtrlLine::drawLine()
{
  std::vector<Vec2> coordMatrix;
  ((FmCtrlLine*)itsFmOwner)->getCoordMatrix(coordMatrix);

  SoIndexedLineSet* line = SO_GET_PART(itsKit,"symbol.nonAxis",SoIndexedLineSet);
  SoCoordinate3*   coord = SO_GET_PART(itsKit,"symbol.coords",SoCoordinate3);

  line->setToDefaults();
  coord->setToDefaults();

  int idx = 0;
  for (const Vec2& point : coordMatrix)
  {
    line->coordIndex.set1Value(idx,idx);
    coord->point.set1Value(idx++,point.x,point.y,0.0f);
  }
}


SbVec3f FdCtrlLine::getCoordinate(int coordIndex)
{
  SoCoordinate3* coord = SO_GET_PART(itsKit,"symbol.coords",SoCoordinate3);
  return *(coord->point.getValues(coordIndex));
}


int FdCtrlLine::getNumberOfSegments() const
{
  return (((FmCtrlLine*)itsFmOwner)->FmCtrlLine::getNumberOfSegments());
}


bool FdCtrlLine::manipLine(int detailNr, const SbVec3f& transVec)
{
  int numLines = this->getNumberOfSegments();
  bool isLine = detailNr < -1 && -detailNr < numLines;
  if (isLine)
    detailNr = -detailNr;
  else if (detailNr < 3 || detailNr >= numLines)
    return false; // Invalid detailNr

  // Orientation of first line
  bool firstLineVertical = ((FmCtrlLine*)itsFmOwner)->isFirstLineVertical();
  // Orientation of next line            detailNr is odd     detailNr is even
  bool nextLineVertical  = detailNr%2 ? firstLineVertical : !firstLineVertical;

  std::vector<double> totLengthArray = ((FmCtrlLine*)itsFmOwner)->getTotLengthArray();
  std::vector<double> lenArray = ((FmCtrlLine*)itsFmOwner)->getLengthArray();

  // Lines in front of 3 undefined lines
  for (int i = 0; i < detailNr-3; i++)
    lenArray[i] = totLengthArray[i];
  if (isLine) // Line in front of 4th undefined line
    lenArray[detailNr-2] = totLengthArray[detailNr-2];

  // Lines behind undefined lines
  for (int i = numLines-1; i > detailNr; i--)
    lenArray[i-2] = totLengthArray[i];

  // Define line in front of picked line,
  // this length is calculated from mouse movement
  SbVec3f coord = this->getCoordinate(detailNr - (isLine ? 2 : 3)); // Coordinates of point on picked line
  lenArray[detailNr-2] = nextLineVertical ? transVec[0] - coord[0] : transVec[1] - coord[1];
  if (!isLine)
    lenArray[detailNr-3] = nextLineVertical ? transVec[1] - coord[1] : transVec[0] - coord[0];

  ((FmCtrlLine*)itsFmOwner)->setLengthArray(lenArray);
  ((FmCtrlLine*)itsFmOwner)->setFirstUndefSegment(detailNr);

  this->drawLine();
  return true;
}


/*!
  This method adds a new break point to the picked line.
  Each new break point gives two new lines to the line set.
  This function builds up the new length array, but one length must be calculated
  from mouse position (this is done in the method addLinePoint2()).
  The method is splitted in two because the first method only needs to be invoked once,
  whereas the second is dependent on the mouse movement.
*/

void FdCtrlLine::addLinePoint1(const SoPickedPoint* pickedPoint)
{
  const SoDetail* lineDetail = pickedPoint->getDetail();
  long int partIndex = ((SoLineDetail*)lineDetail)->getPartIndex();
  long int lineNr = partIndex+1; // Picked line number, 1 -> firstline
  int numLines = this->getNumberOfSegments(); // Size of old line set

  // Global coordinates to the picked point and the line end points
  SbVec3f coordP = pickedPoint->getObjectPoint();
  SbVec3f coord1 = this->getCoordinate(partIndex);
  SbVec3f coord2 = this->getCoordinate(partIndex+1);

  float newLengthOfPickedLine, middelPoint;
  if (coord1[0] == coord2[0]) // Vertical line
  {
    pickedLineVertical = true;
    newLengthOfPickedLine = coordP[1] - coord1[1];
    middelPoint = 0.5f*(coord2[1] + coord1[1]);
  }
  else if (coord1[1] == coord2[1]) // Horizontal line
  {
    pickedLineVertical = false;
    newLengthOfPickedLine = coordP[0] - coord1[0];
    middelPoint = 0.5f*(coord2[0] + coord1[0]);
  }
  else
    newLengthOfPickedLine = middelPoint = 0.0f;

  int rule = 0;
  if (lineNr == 1)
    rule = 2;
  else if (lineNr == numLines || lineNr == numLines-1)
    rule = 1;
  else if (coord1[pickedLineVertical] > coord2[pickedLineVertical])
    rule = coordP[pickedLineVertical] > middelPoint ? 1 : 2;
  else
    rule = coordP[pickedLineVertical] > middelPoint ? 2 : 1;

  if (rule == 1)
  {
    calcLineNr = lineNr-1; // One line before the picked line
    direction = 1;
    coordVec = this->getCoordinate(partIndex-1);
  }
  else if (rule == 2)
  {
    calcLineNr = lineNr+1; // One line after undefined line
    direction = -1;
    coordVec = getCoordinate(partIndex + 3);
  }

  lengthArray = ((FmCtrlLine*)itsFmOwner)->getTotLengthArray();
  lengthArray[lineNr-1] = newLengthOfPickedLine;
  unDefLine = lineNr+1;
}


void FdCtrlLine::addLinePoint2(const SbVec3f& transVec)
{
  int idx = pickedLineVertical ? 0 : 1;
  lengthArray[calcLineNr-1] = direction*(transVec[idx]-coordVec[idx]);

  ((FmCtrlLine*)itsFmOwner)->setLengthArray(lengthArray);
  ((FmCtrlLine*)itsFmOwner)->setFirstUndefSegment(unDefLine);

  this->drawLine();
}


void FdCtrlLine::removeLinePoint(int pointNr)
{
  if (pointNr < 3) return; // Can't remove first break point

  std::vector<double> lengthVec = ((FmCtrlLine*)itsFmOwner)->getTotLengthArray();
  if (pointNr+1 > (int)lengthVec.size()) return; //Can't remove last break point

  // Remove the two lines defined by the points [pointNr-3,pointNr]
  lengthVec.erase(lengthVec.begin()+pointNr-3, lengthVec.begin()+pointNr+1);

  ((FmCtrlLine*)itsFmOwner)->setLengthArray(lengthVec);
  ((FmCtrlLine*)itsFmOwner)->setFirstUndefSegment(pointNr-2);

  this->drawLine();
}
